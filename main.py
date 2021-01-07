import os
import cogapp
import cantools
import shutil
import re
import sys
from pprint import pprint
import os

codegen = cogapp.Cog();
codegen.options.bDeleteCode = True;


def bit_not(n, numbits=32):
    return (1 << numbits) - 1 - n


class CANDatabaseLayer:

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

    def __init__(self, name):
        self.settings['prefix'] = name
        self.reset()

    def reset(self):
        self.frames = {}
        self.signals = {}
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
        filter = 0b1001
        mask = 0b1110
        id = 0b1001

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

        passRatio = NpassIDs / Nidsall #wanted ratio of messages passing
        matchedratio = Nidsmatched/Nidsall # obtained ratio of messages passing
        efficiency = passRatio/matchedratio

        print("""{0:.0%}  of messages should be received by this ECU""".format(passRatio))
        print("""This filter lets {0:.0%}""".format(matchedratio))
        print("""Thus the filter has a {0:.0%} of efficiency""" .format(efficiency))

        self.filter = filterobject;

        #print(format(result, '#034b'))
        return filterobject


    def load(self, file):
        self.reset()
        self.db = cantools.database.load_file(file)

    def save(self, file):
        cantools.database.dump_file(self.db, file)

    def processFreeRTOSInteractionLayer(self):
        #For Now we consider all messages as cyclic
        timegroups = {}

        for framename, fr in self.InteractionLayerFrames.items():
            time = str(fr["cycle_time"])
            if not time in timegroups:
                timegroups[time] = []

            timegroups[time].append(framename)

        self.InteractionLayer = timegroups

    def process(self, node = None):
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


        if sigmax == 0:
            if phymax == 0:
                error = error + 0
            else:
                error = error + 1
        else:
            error = error + abs((phymax - sigmax) / sigmax)

        if sigmin == 0:
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

    def processFrame(self, frame, filterbynode=False):
        if frame.is_multiplexed():
            print("We don't still handle multiplexed messages and signals")
        else:

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
                sig = self.processSignal(signal, frameTX, filterbynode=filterbynode)

                sig["mask"] = "0b" + "1" * signal.length;

                sig["startbit"] = signal.start

                if signal.byte_order == "big_endian":
                    sig["startbit"] = sig["startbit"] - signal.length + 1

                fr["signals"][signal.name] = sig

                if sig['RX']:
                    frameRX = True

            fr["RX"] = frameRX
            fr["TX"] = frameTX

            if frameRX or frameTX:
                self.frames[frame.name] = fr;

            if frameTX:
                fr["send_type"] = frame.send_type
                fr["cycle_time"] = frame.cycle_time
                self.InteractionLayerFrames[frame.name] = fr;

    def processSignal(self, signal, frameTX, filterbynode=False):
        sig = {};
        sig['length'] = signal.length;
        sig['byte_order'] = signal.byte_order;

        if signal.byte_order == "big_endian":
            print("big_endian (motorola) byte orders are dodgy");

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

        if (sig['RX'] or sig['TX']):
            self.signals[signal.name] = sig

        return sig

    def genFiles(self, srcfile=None, hdrfile=None):
        globals = {}

        globals["settings"] = self.settings;
        globals["frames"] = self.frames;
        globals["signals"] = self.signals;
        globals["valuetables"] = self.valuetables;
        globals["InteractionLayer"] = self.InteractionLayer
        globals["filter"] = self.filter

        globals["prefix"] = self.settings["prefix"]; #quicker acccess than settings

        p = self.PathTemplates

        codegen.processFile(fIn=p+"DatabaseLayer.c.cogen", fOut=p+"DatabaseLayer.c", fname="", globals=globals);
        codegen.processFile(fIn=p+"DatabaseLayer.h.cogen", fOut=p+"DatabaseLayer.h", fname="", globals=globals);

        #codegen.processFile(fIn=p + "InteractionLayer.c.cogen", fOut=p + "InteractionLayer.c", fname="", globals=globals);

        if srcfile:
            shutil.copyfile(p+r'DatabaseLayer.c', srcfile+r'DatabaseLayer.c')


        if hdrfile:
            shutil.copyfile(p+r'DatabaseLayer.h', hdrfile+r'DatabaseLayer.h')

if __name__ == '__main__':

    can = CANDatabaseLayer("CAN1")

    can.load('./test/CAN1.dbc')

    src = r'./test/STM32TestProject/Core/Src/'
    hdr = r'./test/STM32TestProject/Core/Inc/'


    can.correctMinsMax()
    can.process(node="Engine")
    #can.process()

    can.genFiles(srcfile=src, hdrfile=hdr);
    shutil.copyfile(r'STM32CANCallbacks.c', src + r'STM32CANCallbacks.c')
    shutil.copyfile(r'STM32CANCallbacks.h', hdr + r'STM32CANCallbacks.h')


