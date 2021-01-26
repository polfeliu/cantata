/**
 ******************************************************************************
 * @details This file was created with the CANDatabaseTool
 * @author Pol Feliu Cuberes
 * @link https://github.com/polfeliu/CANDatabaseLayer
 * @section License
 * This file was automatically generated and is subject to the license of this project
 * Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
 ******************************************************************************
 */

#ifndef __db_H
#define __db_H
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdint.h> 
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"

typedef float single;


/*
 * Interaction Layer: Start function prototype
 */
        
void CAN1_InteractionLayerStart(void);
    



/*
 * CAN Filters: CAN Filters filter and mask
 */

// PassRatio: 80%  // Messages that this ECU Reads
// MatchedRatio: 80%  // Messages that the Filters lets pass
// Efficiency: 100%  // Effiency of the filter (passRation/matchedRatio)
        
#define CAN1_StandardFilter   0b00010110001
#define CAN1_StandardMask     0b10000001000
#define CAN1_ExtendedFilter   0b00000000000000000000000000000
#define CAN1_ExtendedMask     0b11111111111111111111111111111
 


/*
 * CAN Callbacks: Receive Callback prototype
 */


void CAN1_ReceiveCallback(uint64_t data, uint32_t ID, bool is_extended, uint8_t DLC);

/*
 * Enum definitions for CANbyteorder_t
 */
typedef enum {
    little_endian, //intel
    big_endian //motorola
} CANbyteorder_t;

/*
 * Enum definitions of types of signals
 */
typedef enum {
    Tbool,
    Tdouble, 
    Tsingle,
    Tuint8_t,
    Tuint16_t,
    Tuint32_t,
    Tuint64_t,
    Tint8_t,
    Tint16_t,
    Tint32_t,
    Tint64_t
} CANvaluetype_t;

/*
 * Enum definitions for value tables
 */

typedef enum {
    CAN1sig_GearLockVT_Gear_Lock_On=1,
    CAN1sig_GearLockVT_Gear_Lock_Off=0,
}CAN1sig_GearLockVT_t;

typedef enum {
    CAN1sig_EXSignal1VT_Description_for_the_value_0x8=8,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x7=7,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x6=6,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x5=5,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x4=4,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x3=3,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x2=2,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x1=1,
    CAN1sig_EXSignal1VT_Description_for_the_value_0x0=0,
}CAN1sig_EXSignal1VT_t;

typedef enum {
    CAN1sig_EXSignal2VT_Description_for_the_value_0x8=8,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x7=7,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x6=6,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x5=5,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x4=4,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x3=3,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x2=2,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x1=1,
    CAN1sig_EXSignal2VT_Description_for_the_value_0x0=0,
}CAN1sig_EXSignal2VT_t;

typedef enum {
    CAN1sig_ShiftRequestVT_Shift_Request_On=1,
    CAN1sig_ShiftRequestVT_Shift_Request_Off=0,
}CAN1sig_ShiftRequestVT_t;

typedef enum {
    CAN1sig_GearVT_Idle=0,
    CAN1sig_GearVT_Gear_1=1,
    CAN1sig_GearVT_Gear_2=2,
    CAN1sig_GearVT_Gear_3=3,
    CAN1sig_GearVT_Gear_4=4,
    CAN1sig_GearVT_Gear_5=5,
}CAN1sig_GearVT_t;

typedef enum {
    CAN1sig_StatusVT_Error=3,
    CAN1sig_StatusVT_GoSleep=2,
    CAN1sig_StatusVT_Running=1,
    CAN1sig_StatusVT_WakeUp=0,
}CAN1sig_StatusVT_t;

typedef enum {
    CAN1sig_IdleRunningVT_Running=0,
    CAN1sig_IdleRunningVT_Idle=1,
}CAN1sig_IdleRunningVT_t;

/*
 * Export message structs
 */

struct CAN1_FloatExample4_t CAN1_FloatExample4;
struct CAN1_FloatExample3_t CAN1_FloatExample3;
struct CAN1_FloatExample2_t CAN1_FloatExample2;
struct CAN1_FloatExample_t CAN1_FloatExample;
struct CAN1_ABSdata_t CAN1_ABSdata;
struct CAN1_MultiplexExample2_t CAN1_MultiplexExample2;
struct CAN1_MultiplexExample_t CAN1_MultiplexExample;
struct CAN1_Ignition_Info_t CAN1_Ignition_Info;
struct CAN1_NM_Engine_t CAN1_NM_Engine;
struct CAN1_GearBoxInfo_t CAN1_GearBoxInfo;
struct CAN1_EngineStatus_t CAN1_EngineStatus;
struct CAN1_EngineData_t CAN1_EngineData;

/*
 * Export signal structs
 */

struct CAN1sig_DoubleExample2_t CAN1sig_DoubleExample2;
struct CAN1sig_SingleExample3_t CAN1sig_SingleExample3;
struct CAN1sig_DoubleExample_t CAN1sig_DoubleExample;
struct CAN1sig_SingleExample_t CAN1sig_SingleExample;
struct CAN1sig_SingleExample2_t CAN1sig_SingleExample2;
struct CAN1sig_CarSpeed_t CAN1sig_CarSpeed;
struct CAN1sig_GearLock_t CAN1sig_GearLock;
struct CAN1sig_Diagnostics_t CAN1sig_Diagnostics;
struct CAN1sig_AccelerationForce_t CAN1sig_AccelerationForce;
struct CAN1sig_ExSignal7_t CAN1sig_ExSignal7;
struct CAN1sig_ExSignal8_t CAN1sig_ExSignal8;
struct CAN1sig_ExSignal9_t CAN1sig_ExSignal9;
struct CAN1sig_EXSignal1_t CAN1sig_EXSignal1;
struct CAN1sig_EXSignal2_t CAN1sig_EXSignal2;
struct CAN1sig_EXSignal3_t CAN1sig_EXSignal3;
struct CAN1sig_EXSignal4_t CAN1sig_EXSignal4;
struct CAN1sig_StarterKey_t CAN1sig_StarterKey;
struct CAN1sig_SleepInd_t CAN1sig_SleepInd;
struct CAN1sig_ShiftRequest_t CAN1sig_ShiftRequest;
struct CAN1sig_Gear_t CAN1sig_Gear;
struct CAN1sig_EcoMode_t CAN1sig_EcoMode;
struct CAN1sig_Status_t CAN1sig_Status;
struct CAN1sig_ErrorCode_t CAN1sig_ErrorCode;
struct CAN1sig_EngSpeed_t CAN1sig_EngSpeed;
struct CAN1sig_EngTemp_t CAN1sig_EngTemp;
struct CAN1sig_IdleRunning_t CAN1sig_IdleRunning;
struct CAN1sig_PetrolLevel_t CAN1sig_PetrolLevel;
struct CAN1sig_EngForce_t CAN1sig_EngForce;
struct CAN1sig_EngPower_t CAN1sig_EngPower;

/*
 * Define types of the signal structs
 */

struct CAN1sig_DoubleExample2_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    double raw;
    const double (*getValue)(void);
};

struct CAN1sig_SingleExample3_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const single initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    single raw;
    const single (*getValue)(void);
};

struct CAN1sig_DoubleExample_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    double raw;
    const double (*getValue)(void);
    const bool (*setValue)(double);
    const void (*setRaw)(double);
    bool sent;
};

struct CAN1sig_SingleExample_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const single initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    single raw;
    const single (*getValue)(void);
    const bool (*setValue)(single);
    const void (*setRaw)(single);
    bool sent;
};

struct CAN1sig_SingleExample2_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const single initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    single raw;
    const single (*getValue)(void);
    const bool (*setValue)(single);
    const void (*setRaw)(single);
    bool sent;
};

struct CAN1sig_CarSpeed_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[3];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint16_t raw;
    const double (*getValue)(void);
    const bool (*setValue)(double);
    const void (*setRaw)(uint16_t);
    bool sent;
};

struct CAN1sig_GearLock_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_GearLockVT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    bool raw;
    const CAN1sig_GearLockVT_t (*getValue)(void);
    const bool (*setValue)(CAN1sig_GearLockVT_t);
    const void (*setRaw)(bool);
    bool sent;
};

struct CAN1sig_Diagnostics_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const uint8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const uint8_t (*getValue)(void);
    const bool (*setValue)(uint8_t);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_AccelerationForce_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[1];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint16_t raw;
    const double (*getValue)(void);
    const bool (*setValue)(double);
    const void (*setRaw)(uint16_t);
    bool sent;
};

struct CAN1sig_ExSignal7_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const int8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const int8_t (*getValue)(void);
    const bool (*setValue)(int8_t);
    const void (*setRaw)(int8_t);
    bool sent;
};

struct CAN1sig_ExSignal8_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const int8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const int8_t (*getValue)(void);
    const bool (*setValue)(int8_t);
    const void (*setRaw)(int8_t);
    bool sent;
};

struct CAN1sig_ExSignal9_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const int8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const int8_t (*getValue)(void);
    const bool (*setValue)(int8_t);
    const void (*setRaw)(int8_t);
    bool sent;
    uint32_t inactiveValue;
};

struct CAN1sig_EXSignal1_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_EXSignal1VT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const CAN1sig_EXSignal1VT_t (*getValue)(void);
};

struct CAN1sig_EXSignal2_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_EXSignal2VT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const CAN1sig_EXSignal2VT_t (*getValue)(void);
};

struct CAN1sig_EXSignal3_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const int8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const int8_t (*getValue)(void);
};

struct CAN1sig_EXSignal4_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const int8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    int8_t raw;
    const int8_t (*getValue)(void);
};

struct CAN1sig_StarterKey_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const bool initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    bool raw;
    const bool (*getValue)(void);
};

struct CAN1sig_SleepInd_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const bool initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    bool raw;
    const bool (*getValue)(void);
    const bool (*setValue)(bool);
    const void (*setRaw)(bool);
    bool sent;
};

struct CAN1sig_ShiftRequest_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_ShiftRequestVT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    bool raw;
    const CAN1sig_ShiftRequestVT_t (*getValue)(void);
    const bool (*setValue)(CAN1sig_ShiftRequestVT_t);
    const void (*setRaw)(bool);
    bool sent;
};

struct CAN1sig_Gear_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_GearVT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const CAN1sig_GearVT_t (*getValue)(void);
    const bool (*setValue)(CAN1sig_GearVT_t);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_EcoMode_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const uint8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const uint8_t (*getValue)(void);
    const bool (*setValue)(uint8_t);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_Status_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_StatusVT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const CAN1sig_StatusVT_t (*getValue)(void);
    const bool (*setValue)(CAN1sig_StatusVT_t);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_ErrorCode_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const uint8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const uint8_t (*getValue)(void);
    const bool (*setValue)(uint8_t);
    const void (*setRaw)(uint8_t);
    bool sent;
    uint32_t inactiveValue;
};

struct CAN1sig_EngSpeed_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[3];
    const uint16_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint16_t raw;
    const uint16_t (*getValue)(void);
    const bool (*setValue)(uint16_t);
    const void (*setRaw)(uint16_t);
    bool sent;
};

struct CAN1sig_EngTemp_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[4];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const double (*getValue)(void);
    const bool (*setValue)(double);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_IdleRunning_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[0];
    const CAN1sig_IdleRunningVT_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    bool raw;
    const CAN1sig_IdleRunningVT_t (*getValue)(void);
    const bool (*setValue)(CAN1sig_IdleRunningVT_t);
    const void (*setRaw)(bool);
    bool sent;
};

struct CAN1sig_PetrolLevel_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[1];
    const uint8_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint8_t raw;
    const uint8_t (*getValue)(void);
    const bool (*setValue)(uint8_t);
    const void (*setRaw)(uint8_t);
    bool sent;
};

struct CAN1sig_EngForce_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[1];
    const uint16_t initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint16_t raw;
    const uint16_t (*getValue)(void);
    const bool (*setValue)(uint16_t);
    const void (*setRaw)(uint16_t);
    bool sent;
};

struct CAN1sig_EngPower_t{
    const uint8_t length;
    const CANbyteorder_t byte_order;
    const CANvaluetype_t value_type;
    const char unit[2];
    const double initial_value ;
    const double factor ;
    const double offset ;
    const double min ;
    const double max ;
    uint16_t raw;
    const double (*getValue)(void);
    const bool (*setValue)(double);
    const void (*setRaw)(uint16_t);
    bool sent;
};

/*
 * Define types of the message structs
 */

// Comment: None
struct CAN1_FloatExample4_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*receive)(void);
    const struct CAN1_FloatExample4_signals_t{
        const struct{
            const struct CAN1sig_DoubleExample2_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_DoubleExample2;

    }signals;
};
// Comment: None
struct CAN1_FloatExample3_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*receive)(void);
    const struct CAN1_FloatExample3_signals_t{
        const struct{
            const struct CAN1sig_SingleExample3_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_SingleExample3;

    }signals;
};
// Comment: None
struct CAN1_FloatExample2_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const struct CAN1_FloatExample2_signals_t{
        const struct{
            const struct CAN1sig_DoubleExample_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_DoubleExample;

    }signals;
};
// Comment: None
struct CAN1_FloatExample_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const struct CAN1_FloatExample_signals_t{
        const struct{
            const struct CAN1sig_SingleExample_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_SingleExample;

        const struct{
            const struct CAN1sig_SingleExample2_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_SingleExample2;

    }signals;
};
// Comment: None
struct CAN1_ABSdata_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    const struct CAN1_ABSdata_signals_t{
        const struct{
            const struct CAN1sig_CarSpeed_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_CarSpeed;

        const struct{
            const struct CAN1sig_GearLock_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_GearLock;

        const struct{
            const struct CAN1sig_Diagnostics_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_Diagnostics;

        const struct{
            const struct CAN1sig_AccelerationForce_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_AccelerationForce;

    }signals;
};
// Comment: None
struct CAN1_MultiplexExample2_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    const struct CAN1_MultiplexExample2_signals_t{
        const struct{
            const struct CAN1sig_ExSignal7_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_ExSignal7;

        const struct{
            const struct CAN1sig_ExSignal7_t *multiplexor;
            const int32_t multiplexValues[1];
            const struct CAN1sig_ExSignal8_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_ExSignal8;

        const struct{
            const struct CAN1sig_ExSignal8_t *multiplexor;
            const int32_t multiplexValues[1];
            const struct CAN1sig_ExSignal9_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_ExSignal9;

    }signals;
};
// Comment: None
struct CAN1_MultiplexExample_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*receive)(void);
    const struct CAN1_MultiplexExample_signals_t{
        const struct{
            const struct CAN1sig_EXSignal1_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EXSignal1;

        const struct{
            const struct CAN1sig_EXSignal1_t *multiplexor;
            const int32_t multiplexValues[1];
            const struct CAN1sig_EXSignal2_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EXSignal2;

        const struct{
            const struct CAN1sig_EXSignal1_t *multiplexor;
            const int32_t multiplexValues[1];
            const struct CAN1sig_EXSignal3_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EXSignal3;

        const struct{
            const struct CAN1sig_EXSignal2_t *multiplexor;
            const int32_t multiplexValues[1];
            const struct CAN1sig_EXSignal4_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EXSignal4;

        //EXSignal5 is not mapped to this ECU

        //EXSignal6 is not mapped to this ECU

    }signals;
};
// Comment: None
struct CAN1_Ignition_Info_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*receive)(void);
    const struct CAN1_Ignition_Info_signals_t{
        const struct{
            const struct CAN1sig_StarterKey_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_StarterKey;

    }signals;
};
// Comment: None
struct CAN1_NM_Engine_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const struct CAN1_NM_Engine_signals_t{
        const struct{
            const struct CAN1sig_SleepInd_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_SleepInd;

    }signals;
};
// Comment: None
struct CAN1_GearBoxInfo_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    const struct CAN1_GearBoxInfo_signals_t{
        const struct{
            const struct CAN1sig_GearLock_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_GearLock;

        const struct{
            const struct CAN1sig_ShiftRequest_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_ShiftRequest;

        const struct{
            const struct CAN1sig_Gear_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_Gear;

        const struct{
            const struct CAN1sig_EcoMode_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EcoMode;

    }signals;
};
// Comment: None
struct CAN1_EngineStatus_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    const struct CAN1_EngineStatus_signals_t{
        const struct{
            const struct CAN1sig_Status_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_Status;

        const struct{
            const struct CAN1sig_ErrorCode_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_ErrorCode;

    }signals;
};
// Comment: None
struct CAN1_EngineData_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    uint64_t raw;
    const void (*send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    const struct CAN1_EngineData_signals_t{
        const struct{
            const struct CAN1sig_EngSpeed_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EngSpeed;

        const struct{
            const struct CAN1sig_EngTemp_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EngTemp;

        const struct{
            const struct CAN1sig_IdleRunning_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_IdleRunning;

        const struct{
            const struct CAN1sig_PetrolLevel_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_PetrolLevel;

        const struct{
            const struct CAN1sig_EngForce_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EngForce;

        const struct{
            const struct CAN1sig_EngPower_t *signal;
            const uint64_t startbit;
            const uint64_t mask;
        }CAN1sig_EngPower;

    }signals;
};

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */

