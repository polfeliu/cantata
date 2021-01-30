from candatabaselayer import CANDatabaseLayer
can = CANDatabaseLayer('CAN1')
can.load('./CAN1.dbc')

from pprint import pprint
import pandas as pd
import sys
xls = pd.ExcelFile("./CheckMinMax Validation.xlsx", engine='openpyxl', )
df = xls.parse('Sheet1')

examplesig = can.db.messages[0].signals[0]

from random import randint

for index, test in df.iterrows():
    if test['min'] != "x":
        print(index, "---------------------------------------")
        examplesig.length = test.length
        examplesig.type = test.type
        examplesig.scale = test.scale
        examplesig.offset = test.offset

        # test correct min and max
        examplesig.maximum = test['max']
        examplesig.minimum = test['min']

        if test.type == "single" or test.type == "double":
            examplesig.is_float = True
        else:
            examplesig.is_float = False

        if test.type == "signed":
            examplesig.is_signed = True
        else:
            examplesig.is_signed = False

        result, calcmin, calcmax = can.checkMinMax(examplesig)

        if result == False:
            print("""Test %s: This correct min and max checked wrong by the function
                        test min/max %s %s
                        calculated min/max %s %s
                        """ % (index, test['min'], test['max'], calcmin, calcmax))
            sys.exit()

        # test wrong value
        examplesig.maximum = float(test['max']) * 0.1 * randint(1, 100) + randint(-10, 10)
        examplesig.minimum = float(test['min']) * 0.1 * randint(1, 100) + randint(-10, 10)

        result, calcmin, calcmax = can.checkMinMax(examplesig)

        if result == True:
            print("""Test %s: This wrong min and max checked ok by the function
            test min/max %s %s
            calculated min/max %s %s
            """ % (index, test['min'], test['max'], calcmin, calcmax))
            sys.exit()