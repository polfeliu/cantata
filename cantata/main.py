import os
import copy
import cogapp
import cantools
import shutil
import re
import sys

from cantools.database.can.attribute import Attribute

codegen = cogapp.Cog();
codegen.options.bDeleteCode = True;


def bit_not(n, numbits=32):
    return (1 << numbits) - 1 - n


class cantata:

    PathTemplates = "./"

    settings = {
        "getsetValue_type": "double",  # choose double or single for the get and set values
        "getsetValueOptimizeIdentity": True,  # if Scaling is set to 1 and Offset to 0 return the same value type of the raw and do not perform any unuseful operations
        "prefix": None, #all variables related to the library will have this prefix
        "setValueminmax": True, #SetValue function will check that it does not exceed the limits set by the properties
        "checkminmax": True, #checks if the min and max are correct according to the factors and offset. If they are not correct it will stop the program
        "CallbackLib": "STM32CANCallbacks", #name of the library that implementes the Callback functions for this bus
        "FreeRTOSInteractionLayer": True, #generates Interaction Layer with FreeRTOS according to the parameters set on the messages #TODO
        "calculateCANFilter": True, #Calculates a can Filter for the RX messages
    }

    # TODO Make Units optional
    # TODO Make Comment optional
    # TODO Option to make functions thread safe in FreeRTOS (portEnterCritical and portExitCritical)
    # TODO InteractionLayer Bind to Message Received events to Messages received
    # TODO FreeRtos Initialization of signals and messages, how is this handled?
    # TODO Raw messages with variable length according to DLC. Would reduce memory footprint and it would be easy to use this lib with CANFD (64 bytes per message)

    def __init__(self, name):
        self.settings['prefix'] = name
        self.reset()

        import pkg_resources
        self.PathTemplates = pkg_resources.resource_filename('cantata', 'templates/')

    def reset(self):
        self.frames = {}
        self.signals = {}
        self.signalparents = {}
        self.valuetables = {}
        self.InteractionLayerFrames = {}
        self.InteractionLayer = {}
        self.filter = {}

    def calculateCANFilter(self):
        allIDs = {} #All ID's in the Database except the ones that are sent by the database
        passIDs = {}

        for frame in self.db.messages:
            allIDs[frame.frame_id] = frame.is_extended_frame

        for framename, frame in self.frames.items():
            frameid = int(frame['ID'], 16)
            if frame['RX']:
                passIDs[frameid] = frame['is_extended']
            if frame['TX']:# the ID's TXed by this ECU will never be received
                del allIDs[frameid]

        # We will work with 32 bits and then truncate
        StandardFilter = None;
        StandardMask = None
        ExtendedFilter = None
        ExtendedMask = None

        StandardFilter = 0
        ExtendedFilter = 0
        ExtendedMask = 0xFFFFFFFF
        StandardMask = 0xFFFFFFFF

        for id, is_extended in passIDs.items():

            if is_extended == True:
                if not ExtendedFilter:
                    ExtendedFilter = id;
                else:
                    ExtendedMask = ExtendedMask & bit_not(ExtendedFilter ^ id)
            else:
                if not StandardFilter:
                    StandardFilter = id;
                else:
                    StandardMask = StandardMask & bit_not(StandardFilter ^ id)

        # mask Standard by 11 bits
        StandardFilter = StandardFilter & 0x7FF;
        StandardMask = StandardMask & 0x7FF;

        # mask Extended by 11 bits
        ExtendedFilter = ExtendedFilter & 0x1FFFFFFF;
        ExtendedMask = ExtendedMask & 0x1FFFFFFF;


        filterobject = {
            'StandardFilter': StandardFilter,
            'StandardMask': StandardMask,
            'ExtendedFilter': ExtendedFilter,
            'ExtendedMask': ExtendedMask
        }

        idsmatched = []
        idsnotmatched = []
        #Evaluate filter over all IDs
        for id, is_extended in allIDs.items():
            if is_extended == True:
                result = bit_not(ExtendedMask) | bit_not(ExtendedFilter ^ id)
                if result == 0xFFFFFFFF:
                    idsmatched.append(id);
                else:
                    idsnotmatched.append(id);

            else:
                result = bit_not(StandardMask) | bit_not(StandardFilter ^ id)
                if result == 0xFFFFFFFF:
                    idsmatched.append(id);
                else:
                    idsnotmatched.append(id);

        Nidsmatched = len(idsmatched)
        Nidsnotmatched = len(idsnotmatched)
        Nidsall = Nidsmatched + Nidsnotmatched;

        NpassIDs = len(passIDs)
        try:
            passRatio = NpassIDs / Nidsall #wanted ratio of messages passing
            matchedratio = Nidsmatched/Nidsall # obtained ratio of messages passing
            efficiency = passRatio/matchedratio

            passRatio = "%s %%" %(passRatio*100)
            matchedratio = "%s %%" % (matchedratio * 100)
            efficiency = "%s %%" % (efficiency * 100)
        except:
            passRatio = "NULL"
            matchedratio = "NULL"
            efficiency = "NULL"

        filterobject['evaluation'] = ("""
// PassRatio: %s  // Messages that this ECU Reads
// MatchedRatio: %s  // Messages that the Filters lets pass
// Efficiency: %s  // Effiency of the filter (passRation/matchedRatio)
""" % (passRatio, matchedratio, efficiency))

        self.filter = filterobject;

        return filterobject


    def load(self, file):
        self.reset()
        self.db = cantools.database.load_file(file)

    def save(self, file):
        cantools.database.dump_file(self.db, file)

    def processFreeRTOSInteractionLayer(self):
        #For Now we consider all messages as cyclic
        CycleTimeGroups = {};
        CycleTimeFastMsg = {};
        OnWriteOnChange = {}; #If it is with repetition it will resumes the fast group

        for framename, fr in self.InteractionLayerFrames.items():
            if fr['send_type'] == "Cyclic":
                time = str(fr["cycle_time"])
                if not time in CycleTimeGroups:
                    CycleTimeGroups[time] = []
                CycleTimeGroups[time].append(framename)

            def CycleTimeFastAddMsg(framename):
                if "GenMsgCycleTimeFast" in self.frames[framename]['attributes']:
                    time = self.frames[framename]['attributes']['GenMsgCycleTimeFast'].value
                    if framename not in CycleTimeFastMsg:
                        CycleTimeFastMsg[framename] = {
                            "time": time,
                            "ActiveCheckSignals": [],
                            "ActiveRepetitionsResetSignals" : [],
                            "FastDelayedResumeTask": False
                        }

            def safeOnWriteOnChangeAppend(framename, signalname):
                if not framename in OnWriteOnChange:
                    OnWriteOnChange[framename] = [signalname];
                else:
                    OnWriteOnChange[framename].append(signalname)

            def checkIfParentHasRepetitions(framename, signalname):
                if "GenMsgNrOfRepetition" not in self.frames[framename]['attributes']:
                    definition = self.frames[framename]['attribute_definitions']['GenMsgNrOfRepetition']
                    self.frames[framename]['attributes']['GenMsgNrOfRepetition'] = Attribute(definition.default_value, definition)

            def checkIfParentHasFastTime(framename,signalname):
                if "GenMsgCycleTimeFast" not in self.frames[framename]['attributes']:
                    definition = self.frames[framename]['attribute_definitions']['GenMsgCycleTimeFast']
                    self.frames[framename]['attributes']['GenMsgCycleTimeFast'] = Attribute(definition.default_value, definition)

            def CycleTimeFastMsgAddActiveCheck(framename, signalname):
                CycleTimeFastMsg[framename]["ActiveCheckSignals"].append(signalname)

            def CycleTimeFastMsgAddActiveRepetitionsReset(framename, signalname):
                CycleTimeFastMsg[framename]["ActiveRepetitionsResetSignals"].append(signalname)

            def activateFastDelayedResumeTask(framename):
                CycleTimeFastMsg[framename]["FastDelayedResumeTask"] = True

            for signalname, signal in fr['signals'].items():
                if 'GenSigSendType' in signal['attributes']:
                    GenSigSendType = signal['attributes']['GenSigSendType'].value
                    choices = signal['attribute_definitions']['GenSigSendType'].choices

                    if GenSigSendType == choices.index("Cyclic"):
                        #Do Nothing. Cyclics are typically defined in messages
                        pass
                    elif GenSigSendType == choices.index("OnWrite"):
                        safeOnWriteOnChangeAppend(framename, signalname);

                    elif GenSigSendType == choices.index("OnWriteWithRepetition"):
                        safeOnWriteOnChangeAppend(framename, signalname);
                        checkIfParentHasRepetitions(framename, signalname)
                        checkIfParentHasFastTime(framename, signalname)
                        CycleTimeFastAddMsg(framename)
                        activateFastDelayedResumeTask(framename)

                    elif GenSigSendType == choices.index("OnChange"):
                        safeOnWriteOnChangeAppend(framename, signalname);

                    elif GenSigSendType == choices.index("OnChangeWithRepetition"):
                        safeOnWriteOnChangeAppend(framename, signalname);
                        checkIfParentHasRepetitions(framename, signalname)
                        checkIfParentHasFastTime(framename, signalname)
                        CycleTimeFastAddMsg(framename)
                        activateFastDelayedResumeTask(framename)

                    elif GenSigSendType == choices.index("IfActive"):
                        checkIfParentHasFastTime(framename, signalname)
                        CycleTimeFastAddMsg(framename)
                        CycleTimeFastMsgAddActiveCheck(framename, signalname)

                    elif GenSigSendType == choices.index("IfActiveWithRepetition"):
                        checkIfParentHasRepetitions(framename, signalname)
                        checkIfParentHasFastTime(framename, signalname)
                        CycleTimeFastAddMsg(framename)
                        CycleTimeFastMsgAddActiveCheck(framename, signalname)
                        CycleTimeFastMsgAddActiveRepetitionsReset(framename, signalname)

        self.InteractionLayer['CycleTimeGroups'] = CycleTimeGroups
        self.InteractionLayer['OnWriteOnChange'] = OnWriteOnChange
        self.InteractionLayer['CycleTimeFastMsg'] = CycleTimeFastMsg


    def processNetwork(self):
        from pprint import pprint
        if 'BusType' in self.db.dbc.attributes:
            self.BusType = self.db.dbc.attributes['BusType'].value
        else:
            self.BusType = "CAN"

    def process(self, node = None):
        self.processNetwork()
        if node:
            found = False;
            for searchnode in self.db.nodes:
                if searchnode.name == node:
                    found = True;
                    break;

            if found == True:
                self.node = node;
                self.processFrames(filterbynode=True)
            else:
                sys.exit("Node doesn't exist in this Database")
        else:
            self.settings['calculateCANFilter'] = False #Will not calculate filters for all messages, it doens't make sense
            self.processFrames(filterbynode=False)

        if self.settings['FreeRTOSInteractionLayer']:
            self.processFreeRTOSInteractionLayer()

        if self.settings['calculateCANFilter']:
            self.calculateCANFilter()

    def correctMinsMax(self):
        for msgi in range(len(self.db.messages)):
            for sigi in range(len(self.db.messages[msgi].signals)):
                signal = self.db.messages[msgi].signals[sigi]
                result, min, max = self.checkMinMax(signal)
                if result == False:
                    self.db.messages[msgi].signals[sigi].maximum= max
                    self.db.messages[msgi].signals[sigi].minimum = min

    def checkMinMax(self, signal):
        #get rawvalue min and max
        if signal.is_float:
            if signal.length==64:
                #double
                rawmin = -1.7e+308
                rawmax = 1.7e+308
            elif signal.length==32:
                #single
                rawmin = -3.4e+38
                rawmax = 3.4e+38
        elif not signal.is_signed:
            #unsigned
            rawmin = 0
            rawmax = 2**signal.length -1
        else:
            #signed
            rawmin = -2 ** (signal.length - 1)
            rawmax = 2**(signal.length-1) -1

        phylim1 = rawmin * signal.scale + signal.offset
        phylim2 = rawmax * signal.scale + signal.offset
        phymin = min(phylim1, phylim2);
        phymax = max(phylim1, phylim2);

        error = 0;

        if signal.maximum:
            sigmax = float(signal.maximum);
        else:
            sigmax = 0;

        if signal.minimum:
            sigmin = float(signal.minimum);
        else:
            sigmin = 0;


        if sigmax == 0: #avoid divisions by 0 when calculating error
            if phymax == 0:
                error = error + 0
            else:
                error = error + 1
        else:
            error = error + abs((phymax - sigmax) / sigmax)

        if sigmin == 0: #avoid divisions by 0 when calculating error
            if phymin == 0:
                error = error + 0
            else:
                error = error + 1
        else:
            error = error + abs((phymin - sigmin) / sigmin)

        if error < 0.000001: #tolerance
            return True, phymin, phymax
        else:
            return False, phymin, phymax

    def processFrames(self, filterbynode=False):
        for frame in self.db.messages:
            self.processFrame(frame, filterbynode=filterbynode)

    def removeDeadSignalTreeSigs(self, tree):
        for item in tree:
            if type(item) == str: #is signal
                if item not in self.signals:
                    tree.remove(item)
            else:
                multiplexorname = list(item)[0]
                for multiplexedvalue, multiplexed in item[multiplexorname].items():
                    self.removeDeadSignalTreeSigs(multiplexed)
        return tree

    def processFrame(self, frame, filterbynode=False):
        if frame.is_multiplexed():
            #propagate RX signals up the tree (if filtering by node)
            if filterbynode:
                for signal in frame.signals:
                    if self.node in signal.receivers:
                        #if it is received parents also have to be received (to be able to unpack it)
                        multiplexer = signal.multiplexer_signal
                        # search signal and add this receiver so that is detected as RX
                        for i in range(len(frame.signals)):
                            if frame.signals[i].name == multiplexer:
                                frame.signals[i].receivers.append(self.node)

        fr = {}
        fr["ID"] = hex(frame.frame_id);
        fr["decID"] = frame.frame_id;
        fr["comment"] = frame.comment;
        if(frame.is_extended_frame):
            fr["is_extended"] = "true"
        else:
            fr["is_extended"] = "false"

        fr["DLC"] = frame.length;

        fr["signals"] = {}

        if filterbynode:
            frameTX = self.node in frame.senders
            frameRX = False;
        else:
            frameTX = True;
            frameRX = True

        for signal in frame.signals:
            sig = self.processSignal(signal, frameTX, filterbynode=filterbynode).copy() #copy structure instead of linking it. The Global signals should not have start bit, mask and multiplexing information

            if not signal.name in self.signalparents:
                self.signalparents[signal.name] = [frame.name]
            else:
                self.signalparents[signal.name].append(frame.name)

            sig["mask"] = "0b" + "1" * signal.length;

            sig["startbit"] = signal.start

            if signal.byte_order == "big_endian":

                if sig['value_type'] == "single":
                    sig["startbit"] = sig["startbit"] - 7
                elif sig['value_type'] == "double":
                    sig["startbit"] = sig["startbit"] - 7
                else:
                    sig["startbit"] = sig["startbit"] - signal.length + 1

            fr["signals"][signal.name] = sig

            if sig['RX']:
                frameRX = True



        fr["RX"] = frameRX
        fr["TX"] = frameTX

        fr['signal_tree'] = self.removeDeadSignalTreeSigs(frame.signal_tree);

        fr['attributes'] = frame.dbc.attributes
        fr['attribute_definitions'] = frame.dbc.attribute_definitions

        if frameTX and self.settings['FreeRTOSInteractionLayer']:
            fr["send_type"] = frame.send_type
            fr["cycle_time"] = frame.cycle_time

            '''
            if 'GenMsgNrOfRepetitions' in fr['attributes']:
                fr['NrOfRepetitions'] = fr['attributes']['GenMsgNrOfRepetitions'].value
            else:
                fr['NrOfRepetitions'] = 0
            '''
            self.InteractionLayerFrames[frame.name] = fr;


        if frameRX or frameTX:
            self.frames[frame.name] = fr;

    def processSignal(self, signal, frameTX, filterbynode=False):
        sig = {};
        sig['length'] = signal.length;
        sig['byte_order'] = signal.byte_order;

        if signal.unit is None:
            sig['unit'] = ""
            sig['unit_len'] = 0;
        else:
            sig['unit_len'] = len(signal.unit)
            sig['unit'] = signal.unit;

        #TODO: optimize factor, offset, min and max types Right now they are all doubles
        sig['factor'] = signal.scale;
        sig['offset'] = signal.offset;

        if signal.initial is None:
            sig['initial_value'] = 0;
            sig['initial_value_raw'] = 0;
        else:
            sig['initial_value'] = signal.initial;
            sig['initial_value_raw'] = int((signal.initial - sig['offset'])/sig['factor']);

        if self.settings['checkminmax']:
            result,calcmin,calcmax = self.checkMinMax(signal)
            if result == False:
                sys.exit(
"""%s minimums and maximums are not correct according to the factor and offsets set
calculated minimum: %s
calculated maximum: %s                
""" % (signal.name, calcmin, calcmax))

        sig['min'] = signal.minimum;
        sig['max'] = signal.maximum

        if signal.is_float:
            if (signal.length == 64):
                signaltype = "double"
            elif (signal.length == 32):
                signaltype = "single"
            else:
                raise Exception("Floats have to be 32 (single) or 64 (double)")
        elif not signal.is_signed:
            if signal.length == 1:
                signaltype = "bool"
            elif signal.length <= 8:
                signaltype = "uint8_t"
            elif signal.length <= 16:
                signaltype = "uint16_t"
            elif signal.length <= 32:
                signaltype = "uint32_t"
            elif signal.length <= 64:
                signaltype = "uint64_t"
            else:
                raise Exception("Not considering signals greater that 64 bits")
        elif signal.is_signed:
            if signal.length == 1:
                signaltype = "bool"
            elif signal.length <= 8:
                signaltype = "int8_t"
            elif signal.length <= 16:
                signaltype = "int16_t"
            elif signal.length <= 32:
                signaltype = "int32_t"
            elif signal.length <= 64:
                signaltype = "int64_t"
            else:
                raise Exception("Not considering signals greater that 64 bits")

        sig['value_type'] = signaltype;

        if self.settings['getsetValueOptimizeIdentity'] & (sig['factor'] == 1) & (sig['offset'] == 0):
            sig['getsetValue_type'] = signaltype;
        else:
            sig['getsetValue_type'] = self.settings['getsetValue_type'];

        if signal.choices:
            vt = {}
            for num, name in signal.choices.items():
                name = name.replace(' ', '_')
                name = re.sub('[^A-Za-z0-9_]+', '', name)
                name = name.replace('__', '_')
                vt[name] = num;

            self.valuetables[signal.name] = vt
            sig['getsetValue_type'] = "%ssig_%sVT_t" % (self.settings["prefix"], signal.name)


        if filterbynode:
            if self.node in signal.receivers:
                sig['RX'] = True
            else:
                sig['RX'] = False
            sig['TX'] = frameTX;
        else:
            sig['RX'] = True
            sig['TX'] = True;

        sig['multiplexor'] = signal.multiplexer_signal
        sig['multiplexValues'] = signal.multiplexer_ids


        sig['attributes'] = signal.dbc.attributes
        sig['attribute_definitions'] = signal.dbc.attribute_definitions


        if (sig['RX'] or sig['TX']):
            if signal.name not in self.signals:
                self.signals[signal.name] = sig
            else:
                if str(sig) == str(self.signals[signal.name]):
                    # Signal properties are equal thus is the same signa on the database
                    pass
                else:
                    raise SystemExit("Signal %s is reapeated In this database, as of now we can't handle that, please create unique names" % (signal.name))

        #TODO check if the multiplexor values should be the raw value or the physical value! They can only be integers. Either way, who would put a factor in a multiplexor signal???
        return sig

    def genFiles(self, src=None, hdr=None):
        globals = {}

        globals["settings"] = self.settings;
        globals["frames"] = self.frames;
        globals["signals"] = self.signals;
        globals["signalparents"] = self.signalparents
        globals["valuetables"] = self.valuetables;
        globals["InteractionLayer"] = self.InteractionLayer
        globals["filter"] = self.filter
        globals["BusType"] = self.BusType

        globals["prefix"] = self.settings["prefix"]; #quicker acccess than settings

        srcfilename = "cantata%s.c" % self.settings['prefix']
        hdrfilename = "cantata%s.h" % self.settings['prefix']

        p = self.PathTemplates

        codegen.processFile(fIn=p+"cantata.c.cogen", fOut=p+srcfilename, fname="", globals=globals);
        codegen.processFile(fIn=p+"cantata.h.cogen", fOut=p+hdrfilename, fname="", globals=globals);

        if src:
            shutil.copyfile(p+srcfilename, src+srcfilename)

        if hdr:
            shutil.copyfile(p+hdrfilename, hdr+hdrfilename)

if __name__ == '__main__':

    can = cantata("CAN1")

    can.load('../test/CAN1.dbc')

    src = r'../test/STM32TestProject/Core/Src/'
    hdr = r'../test/STM32TestProject/Core/Inc/'

    can.correctMinsMax()
    can.process(node="Engine")
    #can.process()

    can.genFiles(src=src, hdr=hdr);
    shutil.copyfile(r'../callbacks/STM32CANCallbacks.c', src + r'STM32CANCallbacks.c')
    shutil.copyfile(r'../callbacks/STM32CANCallbacks.h', hdr + r'STM32CANCallbacks.h')