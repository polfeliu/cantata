from pprint import pprint
import cantools
import random
import os


def Uint64Format(data):
    for padi in range(8 - len(data)):
        data.append(0)

    val = "0x";
    for i in [7,6,5,4,3,2,1,0]:
        byte = "{:02x}".format(data[i])
        val += byte;
    return val

db = cantools.database.load_file('./CAN1.dbc')

message = db.messages[9]
id = message.frame_id
name = message.name
length = message.length
print(name)


### Receive generator
data = [random.randint(0, 0xFF) for i in range(length)]

#data[0] = 0
#data[1] = 0

sigs = db.decode_message(name, data)


#pprint(sigs)


#Transmit generator
signals = {}

for sig in message.signals:
    max = int(sig.maximum)
    min = int(sig.minimum)
    signals[sig.name] = random.randrange(min,max)

#signals['ExSignal7'] = 0
#signals['ExSignal8'] = 0
#signals['SleepInd'] = 1
#signals['GearLock'] = 1
#signals['ShiftRequest'] = 1
#signals['IdleRunning'] = 1

signals['Status'] = 2
signals['ErrorCode'] = 32

pprint(signals)

### THIS function doens't handle motorola signals well!!!
data = db.encode_message(name,signals,scaling=True,padding=False,strict=True)
print(Uint64Format(bytearray(data)))

#Transform old format
#val = Uint64Format([  154, 0, 20, 91, 170, 63, 179, 149,])
#print(val)

