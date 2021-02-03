/**
 ******************************************************************************
 * @details This file was created with cantata, a code generation tool for can databases
 * @author Pol Feliu Cuberes
 * @link https://github.com/polfeliu/cantata
 ******************************************************************************
 */

#ifndef __db_H
#define __db_H
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdint.h> 
#include "stdbool.h"
#include "string.h"

#include "FreeRTOS.h"
#include "task.h" 

typedef float single;


/*
 * Interaction Layer: Start and Stop function prototypes
 */
        
void CAN1_InteractionLayerStart(void);
void CAN1_InteractionLayerStop(void);
    

/*
 * CAN Filters: CAN Filters filter and mask
 */

// PassRatio: 80.0 %  // Messages that this ECU Reads
// MatchedRatio: 80.0 %  // Messages that the Filters lets pass
// Efficiency: 100.0 %  // Effiency of the filter (passRation/matchedRatio)

#define CAN1_StandardFilter   0b00010110001
#define CAN1_StandardMask     0b10000001000
#define CAN1_ExtendedFilter   0b00000000000000000000000000000
#define CAN1_ExtendedMask     0b11111111111111111111111111111
 


/*
 * CAN Callbacks: Receive Callback prototype
 */


void CAN1_ReceiveCallback(uint8_t data[], uint8_t DLC, uint32_t ID, bool is_extended);

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
    double (*const getValue)(void);
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
    single (*const getValue)(void);
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
    double (*const getValue)(void);
    bool (*const setValue)(double);
    void (*const setRaw)(double);
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
    single (*const getValue)(void);
    bool (*const setValue)(single);
    void (*const setRaw)(single);
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
    single (*const getValue)(void);
    bool (*const setValue)(single);
    void (*const setRaw)(single);
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
    double (*const getValue)(void);
    bool (*const setValue)(double);
    void (*const setRaw)(uint16_t);
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
    CAN1sig_GearLockVT_t (*const getValue)(void);
    bool (*const setValue)(CAN1sig_GearLockVT_t);
    void (*const setRaw)(bool);
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
    uint8_t (*const getValue)(void);
    bool (*const setValue)(uint8_t);
    void (*const setRaw)(uint8_t);
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
    double (*const getValue)(void);
    bool (*const setValue)(double);
    void (*const setRaw)(uint16_t);
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
    int8_t (*const getValue)(void);
    bool (*const setValue)(int8_t);
    void (*const setRaw)(int8_t);
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
    int8_t (*const getValue)(void);
    bool (*const setValue)(int8_t);
    void (*const setRaw)(int8_t);
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
    int8_t (*const getValue)(void);
    bool (*const setValue)(int8_t);
    void (*const setRaw)(int8_t);
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
    CAN1sig_EXSignal1VT_t (*const getValue)(void);
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
    CAN1sig_EXSignal2VT_t (*const getValue)(void);
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
    int8_t (*const getValue)(void);
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
    int8_t (*const getValue)(void);
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
    bool (*const getValue)(void);
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
    bool (*const getValue)(void);
    bool (*const setValue)(bool);
    void (*const setRaw)(bool);
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
    CAN1sig_ShiftRequestVT_t (*const getValue)(void);
    bool (*const setValue)(CAN1sig_ShiftRequestVT_t);
    void (*const setRaw)(bool);
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
    CAN1sig_GearVT_t (*const getValue)(void);
    bool (*const setValue)(CAN1sig_GearVT_t);
    void (*const setRaw)(uint8_t);
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
    uint8_t (*const getValue)(void);
    bool (*const setValue)(uint8_t);
    void (*const setRaw)(uint8_t);
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
    CAN1sig_StatusVT_t (*const getValue)(void);
    bool (*const setValue)(CAN1sig_StatusVT_t);
    void (*const setRaw)(uint8_t);
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
    uint8_t (*const getValue)(void);
    bool (*const setValue)(uint8_t);
    void (*const setRaw)(uint8_t);
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
    uint16_t (*const getValue)(void);
    bool (*const setValue)(uint16_t);
    void (*const setRaw)(uint16_t);
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
    double (*const getValue)(void);
    bool (*const setValue)(double);
    void (*const setRaw)(uint8_t);
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
    CAN1sig_IdleRunningVT_t (*const getValue)(void);
    bool (*const setValue)(CAN1sig_IdleRunningVT_t);
    void (*const setRaw)(bool);
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
    uint8_t (*const getValue)(void);
    bool (*const setValue)(uint8_t);
    void (*const setRaw)(uint8_t);
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
    uint16_t (*const getValue)(void);
    bool (*const setValue)(uint16_t);
    void (*const setRaw)(uint16_t);
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
    double (*const getValue)(void);
    bool (*const setValue)(double);
    void (*const setRaw)(uint16_t);
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
    void (*const receive)(void);
    void (*on_receive)(void);
    union CAN1_FloatExample4raw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_FloatExample4raw_DoubleExample2_s{
            uint64_t sig: 64;
        }CAN1sig_DoubleExample2;
    }raw;
};
// Comment: None
struct CAN1_FloatExample3_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const receive)(void);
    void (*on_receive)(void);
    union CAN1_FloatExample3raw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_FloatExample3raw_SingleExample3_s{
            uint64_t sig: 32;
        }CAN1sig_SingleExample3;
    }raw;
};
// Comment: None
struct CAN1_FloatExample2_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    union CAN1_FloatExample2raw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_FloatExample2raw_DoubleExample_s{
            uint64_t sig: 64;
        }CAN1sig_DoubleExample;
    }raw;
};
// Comment: None
struct CAN1_FloatExample_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    union CAN1_FloatExampleraw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_FloatExampleraw_SingleExample_s{
            uint64_t sig: 32;
        }CAN1sig_SingleExample;
        struct __attribute__((__packed__)) CAN1_FloatExampleraw_SingleExample2_s{
            uint64_t pad1: 32;
            uint64_t sig: 32;
        }CAN1sig_SingleExample2;
    }raw;
};
// Comment: None
struct CAN1_ABSdata_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    union CAN1_ABSdataraw_u{
        uint8_t bytes[6];
        struct __attribute__((__packed__)) CAN1_ABSdataraw_CarSpeed_s{
            uint64_t sig: 10;
        }CAN1sig_CarSpeed;
        struct __attribute__((__packed__)) CAN1_ABSdataraw_GearLock_s{
            uint64_t pad1: 10;
            uint64_t sig: 1;
        }CAN1sig_GearLock;
        struct __attribute__((__packed__)) CAN1_ABSdataraw_Diagnostics_s{
            uint64_t pad1: 16;
            uint64_t sig: 8;
        }CAN1sig_Diagnostics;
        struct __attribute__((__packed__)) CAN1_ABSdataraw_AccelerationForce_s{
            uint64_t pad1: 32;
            uint64_t sig: 16;
        }CAN1sig_AccelerationForce;
    }raw;
};
// Comment: None
struct CAN1_MultiplexExample2_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    union CAN1_MultiplexExample2raw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_MultiplexExample2raw_ExSignal7_s{
            uint64_t sig: 8;
        }CAN1sig_ExSignal7;
        struct __attribute__((__packed__)) CAN1_MultiplexExample2raw_ExSignal8_s{
            uint64_t pad1: 8;
            uint64_t sig: 8;
        }CAN1sig_ExSignal8;
        struct __attribute__((__packed__)) CAN1_MultiplexExample2raw_ExSignal9_s{
            uint64_t pad1: 16;
            uint64_t sig: 8;
        }CAN1sig_ExSignal9;
    }raw;
};
// Comment: None
struct CAN1_MultiplexExample_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const receive)(void);
    void (*on_receive)(void);
    union CAN1_MultiplexExampleraw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_MultiplexExampleraw_EXSignal1_s{
            uint64_t sig: 8;
        }CAN1sig_EXSignal1;
        struct __attribute__((__packed__)) CAN1_MultiplexExampleraw_EXSignal2_s{
            uint64_t pad1: 8;
            uint64_t sig: 8;
        }CAN1sig_EXSignal2;
        struct __attribute__((__packed__)) CAN1_MultiplexExampleraw_EXSignal3_s{
            uint64_t pad1: 16;
            uint64_t sig: 8;
        }CAN1sig_EXSignal3;
        struct __attribute__((__packed__)) CAN1_MultiplexExampleraw_EXSignal4_s{
            uint64_t pad1: 24;
            uint64_t sig: 8;
        }CAN1sig_EXSignal4;
        //EXSignal5 is not mapped to this ECU

        //EXSignal6 is not mapped to this ECU

    }raw;
};
// Comment: None
struct CAN1_Ignition_Info_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const receive)(void);
    void (*on_receive)(void);
    union CAN1_Ignition_Inforaw_u{
        uint8_t bytes[2];
        struct __attribute__((__packed__)) CAN1_Ignition_Inforaw_StarterKey_s{
            uint64_t pad1: 7;
            uint64_t sig: 1;
        }CAN1sig_StarterKey;
    }raw;
};
// Comment: None
struct CAN1_NM_Engine_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    union CAN1_NM_Engineraw_u{
        uint8_t bytes[4];
        struct __attribute__((__packed__)) CAN1_NM_Engineraw_SleepInd_s{
            uint64_t pad1: 12;
            uint64_t sig: 1;
        }CAN1sig_SleepInd;
    }raw;
};
// Comment: None
struct CAN1_GearBoxInfo_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    union CAN1_GearBoxInforaw_u{
        uint8_t bytes[1];
        struct __attribute__((__packed__)) CAN1_GearBoxInforaw_GearLock_s{
            uint64_t pad1: 4;
            uint64_t sig: 1;
        }CAN1sig_GearLock;
        struct __attribute__((__packed__)) CAN1_GearBoxInforaw_ShiftRequest_s{
            uint64_t pad1: 5;
            uint64_t sig: 1;
        }CAN1sig_ShiftRequest;
        struct __attribute__((__packed__)) CAN1_GearBoxInforaw_Gear_s{
            uint64_t sig: 3;
        }CAN1sig_Gear;
        struct __attribute__((__packed__)) CAN1_GearBoxInforaw_EcoMode_s{
            uint64_t pad1: 6;
            uint64_t sig: 2;
        }CAN1sig_EcoMode;
    }raw;
};
// Comment: None
struct CAN1_EngineStatus_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    union CAN1_EngineStatusraw_u{
        uint8_t bytes[1];
        struct __attribute__((__packed__)) CAN1_EngineStatusraw_Status_s{
            uint64_t sig: 2;
        }CAN1sig_Status;
        struct __attribute__((__packed__)) CAN1_EngineStatusraw_ErrorCode_s{
            uint64_t pad1: 2;
            uint64_t sig: 6;
        }CAN1sig_ErrorCode;
    }raw;
};
// Comment: None
struct CAN1_EngineData_t{
    const uint32_t ID;
    const bool is_extended;
    const uint8_t DLC;
    void (*const send)(void);
    const uint32_t repetitions;
    uint32_t repetitionsleft;
    union CAN1_EngineDataraw_u{
        uint8_t bytes[8];
        struct __attribute__((__packed__)) CAN1_EngineDataraw_EngSpeed_s{
            uint64_t sig: 16;
        }CAN1sig_EngSpeed;
        struct __attribute__((__packed__)) CAN1_EngineDataraw_EngTemp_s{
            uint64_t pad1: 16;
            uint64_t sig: 7;
        }CAN1sig_EngTemp;
        struct __attribute__((__packed__)) CAN1_EngineDataraw_IdleRunning_s{
            uint64_t pad1: 23;
            uint64_t sig: 1;
        }CAN1sig_IdleRunning;
        struct __attribute__((__packed__)) CAN1_EngineDataraw_PetrolLevel_s{
            uint64_t pad1: 24;
            uint64_t sig: 8;
        }CAN1sig_PetrolLevel;
        struct __attribute__((__packed__)) CAN1_EngineDataraw_EngForce_s{
            uint64_t pad1: 32;
            uint64_t sig: 16;
        }CAN1sig_EngForce;
        struct __attribute__((__packed__)) CAN1_EngineDataraw_EngPower_s{
            uint64_t pad1: 48;
            uint64_t sig: 16;
        }CAN1sig_EngPower;
    }raw;
};

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */

