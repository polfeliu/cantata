#include "DatabaseLayer.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"
#include "STM32CANCallbacks.h" 

uint64_t reverseBits(uint64_t num, uint8_t NO_OF_BITS)
{
    uint64_t reverse_num = 0;
    uint64_t temp = num;
    uint64_t pos = (uint64_t)1 << (NO_OF_BITS - 1);
    while(pos != 0)
    {
        if(temp & 1)
            reverse_num |= pos;

        temp = temp >> 1;
        pos = pos >> 1;
    }

    return reverse_num;
}


/*
 * Interaction Layer: Tasks to send the cyclic messages
 */
        
static void vTaskInteractionLayer_CAN1_2ms( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(2);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;){

        CAN1_MultiplexExample2.send();
        CAN1_DiagResponse_Motor.send();
        CAN1_NM_Engine.send();
        CAN1_EngineStatus.send();

        vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
    }
}
    
static void vTaskInteractionLayer_CAN1_50ms( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(50);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;){

        CAN1_GearBoxInfo.send();
        CAN1_EngineDataIEEE.send();
        CAN1_EngineData.send();
        CAN1_ABSdata.send();

        vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
    }
}
    



/*
 * Interaction Layer: Start function to initialize the cyclic tasks
 */
        
void CAN1_InteractionLayerInit(){
    

    xTaskCreate(
        vTaskInteractionLayer_CAN1_2ms,      /* Function that implements the task. */
        "InteractionLayer_CAN1_2ms",         /* Text name for the task. */
        100,                                /* Stack size in words, not bytes. */
        NULL,                               /* Parameter passed into the task. */
        tskIDLE_PRIORITY,                   /* Priority at which the task is created. */
        NULL                                /* Used to pass out the created task's handle. */
    );      
    

    xTaskCreate(
        vTaskInteractionLayer_CAN1_50ms,      /* Function that implements the task. */
        "InteractionLayer_CAN1_50ms",         /* Text name for the task. */
        100,                                /* Stack size in words, not bytes. */
        NULL,                               /* Parameter passed into the task. */
        tskIDLE_PRIORITY,                   /* Priority at which the task is created. */
        NULL                                /* Used to pass out the created task's handle. */
    );      
    }



/*
 * CAN Callbacks: Receive Callback function. This function should be called when a new message arrives. The function automatically identifies the message and unpacks it into the signals
 */

void CAN1_ReceiveCallback(uint64_t data, uint32_t ID, bool is_extended, uint8_t DLC){
    if((ID > 0x1FFFFFFF) & is_extended){
        //invalid extended identifier
    }else if((ID > 0x7FF) & !is_extended){
        //invalid standard identifier
    }

    else if((ID==CAN1_MultiplexExample.ID) & (is_extended==CAN1_MultiplexExample.is_extended)){
        CAN1_MultiplexExample.raw = data;
        CAN1_MultiplexExample.receive();
    }

    else if((ID==CAN1_Ignition_Info.ID) & (is_extended==CAN1_Ignition_Info.is_extended)){
        CAN1_Ignition_Info.raw = data;
        CAN1_Ignition_Info.receive();
    }

    else{
        //ID is not received by this ECU
    }
}


/*
 * Signal getValue, setValue and setRaw method prototypes
 */

static int8_t CAN1sig_ExSignal7_getValue();
static bool CAN1sig_ExSignal7_setValue(int8_t);
static void CAN1sig_ExSignal7_setRaw(int8_t);
static int8_t CAN1sig_ExSignal8_getValue();
static bool CAN1sig_ExSignal8_setValue(int8_t);
static void CAN1sig_ExSignal8_setRaw(int8_t);
static int8_t CAN1sig_ExSignal9_getValue();
static bool CAN1sig_ExSignal9_setValue(int8_t);
static void CAN1sig_ExSignal9_setRaw(int8_t);
static CAN1sig_EXSignal1VT_t CAN1sig_EXSignal1_getValue();
static CAN1sig_EXSignal2VT_t CAN1sig_EXSignal2_getValue();
static int8_t CAN1sig_EXSignal3_getValue();
static int8_t CAN1sig_EXSignal4_getValue();
static bool CAN1sig_StarterKey_getValue();
static bool CAN1sig_SleepInd_getValue();
static bool CAN1sig_SleepInd_setValue(bool);
static void CAN1sig_SleepInd_setRaw(bool);
static CAN1sig_ShiftRequestVT_t CAN1sig_ShiftRequest_getValue();
static bool CAN1sig_ShiftRequest_setValue(CAN1sig_ShiftRequestVT_t);
static void CAN1sig_ShiftRequest_setRaw(bool);
static CAN1sig_GearVT_t CAN1sig_Gear_getValue();
static bool CAN1sig_Gear_setValue(CAN1sig_GearVT_t);
static void CAN1sig_Gear_setRaw(uint8_t);
static uint8_t CAN1sig_EcoMode_getValue();
static bool CAN1sig_EcoMode_setValue(uint8_t);
static void CAN1sig_EcoMode_setRaw(uint8_t);
static CAN1sig_StatusVT_t CAN1sig_Status_getValue();
static bool CAN1sig_Status_setValue(CAN1sig_StatusVT_t);
static void CAN1sig_Status_setRaw(uint8_t);
static uint8_t CAN1sig_ErrorCode_getValue();
static bool CAN1sig_ErrorCode_setValue(uint8_t);
static void CAN1sig_ErrorCode_setRaw(uint8_t);
static uint16_t CAN1sig_EngSpeed_getValue();
static bool CAN1sig_EngSpeed_setValue(uint16_t);
static void CAN1sig_EngSpeed_setRaw(uint16_t);
static uint16_t CAN1sig_EngForce_getValue();
static bool CAN1sig_EngForce_setValue(uint16_t);
static void CAN1sig_EngForce_setRaw(uint16_t);
static double CAN1sig_EngTemp_getValue();
static bool CAN1sig_EngTemp_setValue(double);
static void CAN1sig_EngTemp_setRaw(uint8_t);
static CAN1sig_IdleRunningVT_t CAN1sig_IdleRunning_getValue();
static bool CAN1sig_IdleRunning_setValue(CAN1sig_IdleRunningVT_t);
static void CAN1sig_IdleRunning_setRaw(bool);
static uint8_t CAN1sig_PetrolLevel_getValue();
static bool CAN1sig_PetrolLevel_setValue(uint8_t);
static void CAN1sig_PetrolLevel_setRaw(uint8_t);
static double CAN1sig_EngPower_getValue();
static bool CAN1sig_EngPower_setValue(double);
static void CAN1sig_EngPower_setRaw(uint16_t);
static double CAN1sig_CarSpeed_getValue();
static bool CAN1sig_CarSpeed_setValue(double);
static void CAN1sig_CarSpeed_setRaw(uint16_t);
static CAN1sig_GearLockVT_t CAN1sig_GearLock_getValue();
static bool CAN1sig_GearLock_setValue(CAN1sig_GearLockVT_t);
static void CAN1sig_GearLock_setRaw(bool);
static uint8_t CAN1sig_Diagnostics_getValue();
static bool CAN1sig_Diagnostics_setValue(uint8_t);
static void CAN1sig_Diagnostics_setRaw(uint8_t);
static double CAN1sig_AccelerationForce_getValue();
static bool CAN1sig_AccelerationForce_setValue(double);
static void CAN1sig_AccelerationForce_setRaw(uint16_t);


/*
 * Signals: Signal struct definitions
 */


struct CAN1sig_ExSignal7_t CAN1sig_ExSignal7 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal7_getValue,
    .setValue = CAN1sig_ExSignal7_setValue,
    .setRaw = CAN1sig_ExSignal7_setRaw
};
    
struct CAN1sig_ExSignal8_t CAN1sig_ExSignal8 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal8_getValue,
    .setValue = CAN1sig_ExSignal8_setValue,
    .setRaw = CAN1sig_ExSignal8_setRaw
};
    
struct CAN1sig_ExSignal9_t CAN1sig_ExSignal9 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal9_getValue,
    .setValue = CAN1sig_ExSignal9_setValue,
    .setRaw = CAN1sig_ExSignal9_setRaw
};
    
struct CAN1sig_EXSignal1_t CAN1sig_EXSignal1 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_EXSignal1_getValue
};
    
struct CAN1sig_EXSignal2_t CAN1sig_EXSignal2 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_EXSignal2_getValue
};
    
struct CAN1sig_EXSignal3_t CAN1sig_EXSignal3 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_EXSignal3_getValue
};
    
struct CAN1sig_EXSignal4_t CAN1sig_EXSignal4 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_EXSignal4_getValue
};
    
struct CAN1sig_StarterKey_t CAN1sig_StarterKey = {
    .length = 1,
    .byte_order = big_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_StarterKey_getValue
};
    
struct CAN1sig_SleepInd_t CAN1sig_SleepInd = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_SleepInd_getValue,
    .setValue = CAN1sig_SleepInd_setValue,
    .setRaw = CAN1sig_SleepInd_setRaw
};
    
struct CAN1sig_ShiftRequest_t CAN1sig_ShiftRequest = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_ShiftRequest_getValue,
    .setValue = CAN1sig_ShiftRequest_setValue,
    .setRaw = CAN1sig_ShiftRequest_setRaw
};
    
struct CAN1sig_Gear_t CAN1sig_Gear = {
    .length = 3,
    .byte_order = big_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 3,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 7,
    .raw = 3,
    .getValue = CAN1sig_Gear_getValue,
    .setValue = CAN1sig_Gear_setValue,
    .setRaw = CAN1sig_Gear_setRaw
};
    
struct CAN1sig_EcoMode_t CAN1sig_EcoMode = {
    .length = 2,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 3,
    .raw = 0,
    .getValue = CAN1sig_EcoMode_getValue,
    .setValue = CAN1sig_EcoMode_setValue,
    .setRaw = CAN1sig_EcoMode_setRaw
};
    
struct CAN1sig_Status_t CAN1sig_Status = {
    .length = 2,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 3,
    .raw = 0,
    .getValue = CAN1sig_Status_getValue,
    .setValue = CAN1sig_Status_setValue,
    .setRaw = CAN1sig_Status_setRaw
};
    
struct CAN1sig_ErrorCode_t CAN1sig_ErrorCode = {
    .length = 6,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 63,
    .raw = 0,
    .getValue = CAN1sig_ErrorCode_getValue,
    .setValue = CAN1sig_ErrorCode_setValue,
    .setRaw = CAN1sig_ErrorCode_setRaw
};
    
struct CAN1sig_EngSpeed_t CAN1sig_EngSpeed = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "rpm",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 65535,
    .raw = 0,
    .getValue = CAN1sig_EngSpeed_getValue,
    .setValue = CAN1sig_EngSpeed_setValue,
    .setRaw = CAN1sig_EngSpeed_setRaw
};
    
struct CAN1sig_EngForce_t CAN1sig_EngForce = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "N",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 65535,
    .raw = 0,
    .getValue = CAN1sig_EngForce_getValue,
    .setValue = CAN1sig_EngForce_setValue,
    .setRaw = CAN1sig_EngForce_setRaw
};
    
struct CAN1sig_EngTemp_t CAN1sig_EngTemp = {
    .length = 7,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "degC",
    .initial_value = 0,
    .factor = 2,
    .offset = -50,
    .min = -50,
    .max = 204,
    .raw = 0,
    .getValue = CAN1sig_EngTemp_getValue,
    .setValue = CAN1sig_EngTemp_setValue,
    .setRaw = CAN1sig_EngTemp_setRaw
};
    
struct CAN1sig_IdleRunning_t CAN1sig_IdleRunning = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_IdleRunning_getValue,
    .setValue = CAN1sig_IdleRunning_setValue,
    .setRaw = CAN1sig_IdleRunning_setRaw
};
    
struct CAN1sig_PetrolLevel_t CAN1sig_PetrolLevel = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "l",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 255,
    .raw = 0,
    .getValue = CAN1sig_PetrolLevel_getValue,
    .setValue = CAN1sig_PetrolLevel_setValue,
    .setRaw = CAN1sig_PetrolLevel_setRaw
};
    
struct CAN1sig_EngPower_t CAN1sig_EngPower = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "kW",
    .initial_value = 0,
    .factor = 0.01,
    .offset = 0,
    .min = 0.0,
    .max = 655.35,
    .raw = 0,
    .getValue = CAN1sig_EngPower_getValue,
    .setValue = CAN1sig_EngPower_setValue,
    .setRaw = CAN1sig_EngPower_setRaw
};
    
struct CAN1sig_CarSpeed_t CAN1sig_CarSpeed = {
    .length = 10,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "mph",
    .initial_value = 0,
    .factor = 0.5,
    .offset = 0,
    .min = 0.0,
    .max = 511.5,
    .raw = 0,
    .getValue = CAN1sig_CarSpeed_getValue,
    .setValue = CAN1sig_CarSpeed_setValue,
    .setRaw = CAN1sig_CarSpeed_setRaw
};
    
struct CAN1sig_GearLock_t CAN1sig_GearLock = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_GearLock_getValue,
    .setValue = CAN1sig_GearLock_setValue,
    .setRaw = CAN1sig_GearLock_setRaw
};
    
struct CAN1sig_Diagnostics_t CAN1sig_Diagnostics = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 255,
    .raw = 0,
    .getValue = CAN1sig_Diagnostics_getValue,
    .setValue = CAN1sig_Diagnostics_setValue,
    .setRaw = CAN1sig_Diagnostics_setRaw
};
    
struct CAN1sig_AccelerationForce_t CAN1sig_AccelerationForce = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "N",
    .initial_value = 0,
    .factor = 1,
    .offset = -10000,
    .min = -10000,
    .max = 55535,
    .raw = 0,
    .getValue = CAN1sig_AccelerationForce_getValue,
    .setValue = CAN1sig_AccelerationForce_setValue,
    .setRaw = CAN1sig_AccelerationForce_setRaw
};
    

/*
 * Signals: Signal getValue and setValue private methods
 */


// ExSignal7
static int8_t CAN1sig_ExSignal7_getValue(){
     return CAN1sig_ExSignal7.raw;
}
static bool CAN1sig_ExSignal7_setValue(int8_t val){
    bool saturation = false;
    CAN1sig_ExSignal7.raw =  val;
    return !saturation;
}
static void CAN1sig_ExSignal7_setRaw(int8_t raw){
    CAN1sig_ExSignal7.raw = raw;
}

// ExSignal8
static int8_t CAN1sig_ExSignal8_getValue(){
     return CAN1sig_ExSignal8.raw;
}
static bool CAN1sig_ExSignal8_setValue(int8_t val){
    bool saturation = false;
    CAN1sig_ExSignal8.raw =  val;
    return !saturation;
}
static void CAN1sig_ExSignal8_setRaw(int8_t raw){
    CAN1sig_ExSignal8.raw = raw;
}

// ExSignal9
static int8_t CAN1sig_ExSignal9_getValue(){
     return CAN1sig_ExSignal9.raw;
}
static bool CAN1sig_ExSignal9_setValue(int8_t val){
    bool saturation = false;
    CAN1sig_ExSignal9.raw =  val;
    return !saturation;
}
static void CAN1sig_ExSignal9_setRaw(int8_t raw){
    CAN1sig_ExSignal9.raw = raw;
}

// EXSignal1
static CAN1sig_EXSignal1VT_t CAN1sig_EXSignal1_getValue(){
     return CAN1sig_EXSignal1.raw;
}


// EXSignal2
static CAN1sig_EXSignal2VT_t CAN1sig_EXSignal2_getValue(){
     return CAN1sig_EXSignal2.raw;
}


// EXSignal3
static int8_t CAN1sig_EXSignal3_getValue(){
     return CAN1sig_EXSignal3.raw;
}


// EXSignal4
static int8_t CAN1sig_EXSignal4_getValue(){
     return CAN1sig_EXSignal4.raw;
}


// StarterKey
static bool CAN1sig_StarterKey_getValue(){
     return CAN1sig_StarterKey.raw;
}


// SleepInd
static bool CAN1sig_SleepInd_getValue(){
     return CAN1sig_SleepInd.raw;
}
static bool CAN1sig_SleepInd_setValue(bool val){
    bool saturation = false;
    CAN1sig_SleepInd.raw =  val;
    return !saturation;
}
static void CAN1sig_SleepInd_setRaw(bool raw){
    CAN1sig_SleepInd.raw = raw;
}

// ShiftRequest
static CAN1sig_ShiftRequestVT_t CAN1sig_ShiftRequest_getValue(){
     return CAN1sig_ShiftRequest.raw;
}
static bool CAN1sig_ShiftRequest_setValue(CAN1sig_ShiftRequestVT_t val){
    bool saturation = false;
    CAN1sig_ShiftRequest.raw =  val;
    return !saturation;
}
static void CAN1sig_ShiftRequest_setRaw(bool raw){
    CAN1sig_ShiftRequest.raw = raw;
}

// Gear
static CAN1sig_GearVT_t CAN1sig_Gear_getValue(){
     return CAN1sig_Gear.raw;
}
static bool CAN1sig_Gear_setValue(CAN1sig_GearVT_t val){
    bool saturation = false;
    CAN1sig_Gear.raw =  val;
    return !saturation;
}
static void CAN1sig_Gear_setRaw(uint8_t raw){
    CAN1sig_Gear.raw = raw;
}

// EcoMode
static uint8_t CAN1sig_EcoMode_getValue(){
     return CAN1sig_EcoMode.raw;
}
static bool CAN1sig_EcoMode_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_EcoMode.raw =  val;
    return !saturation;
}
static void CAN1sig_EcoMode_setRaw(uint8_t raw){
    CAN1sig_EcoMode.raw = raw;
}

// Status
static CAN1sig_StatusVT_t CAN1sig_Status_getValue(){
     return CAN1sig_Status.raw;
}
static bool CAN1sig_Status_setValue(CAN1sig_StatusVT_t val){
    bool saturation = false;
    CAN1sig_Status.raw =  val;
    return !saturation;
}
static void CAN1sig_Status_setRaw(uint8_t raw){
    CAN1sig_Status.raw = raw;
}

// ErrorCode
static uint8_t CAN1sig_ErrorCode_getValue(){
     return CAN1sig_ErrorCode.raw;
}
static bool CAN1sig_ErrorCode_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_ErrorCode.raw =  val;
    return !saturation;
}
static void CAN1sig_ErrorCode_setRaw(uint8_t raw){
    CAN1sig_ErrorCode.raw = raw;
}

// EngSpeed
static uint16_t CAN1sig_EngSpeed_getValue(){
     return CAN1sig_EngSpeed.raw;
}
static bool CAN1sig_EngSpeed_setValue(uint16_t val){
    bool saturation = false;
    CAN1sig_EngSpeed.raw =  val;
    return !saturation;
}
static void CAN1sig_EngSpeed_setRaw(uint16_t raw){
    CAN1sig_EngSpeed.raw = raw;
}

// EngForce
static uint16_t CAN1sig_EngForce_getValue(){
     return CAN1sig_EngForce.raw;
}
static bool CAN1sig_EngForce_setValue(uint16_t val){
    bool saturation = false;
    CAN1sig_EngForce.raw =  val;
    return !saturation;
}
static void CAN1sig_EngForce_setRaw(uint16_t raw){
    CAN1sig_EngForce.raw = raw;
}

// EngTemp
static double CAN1sig_EngTemp_getValue(){
     return ((double) CAN1sig_EngTemp.raw) * CAN1sig_EngTemp.factor + CAN1sig_EngTemp.offset;
}
static bool CAN1sig_EngTemp_setValue(double val){
    bool saturation = false;
    if(val > CAN1sig_EngTemp.max){
        saturation = true;
        val = CAN1sig_EngTemp.max;
    }else if(val < CAN1sig_EngTemp.min){
        saturation = true;
        val = CAN1sig_EngTemp.min;
    }

    CAN1sig_EngTemp.raw =  (val-CAN1sig_EngTemp.offset)/CAN1sig_EngTemp.factor;
    return !saturation;
}
static void CAN1sig_EngTemp_setRaw(uint8_t raw){
    CAN1sig_EngTemp.raw = raw;
}

// IdleRunning
static CAN1sig_IdleRunningVT_t CAN1sig_IdleRunning_getValue(){
     return CAN1sig_IdleRunning.raw;
}
static bool CAN1sig_IdleRunning_setValue(CAN1sig_IdleRunningVT_t val){
    bool saturation = false;
    CAN1sig_IdleRunning.raw =  val;
    return !saturation;
}
static void CAN1sig_IdleRunning_setRaw(bool raw){
    CAN1sig_IdleRunning.raw = raw;
}

// PetrolLevel
static uint8_t CAN1sig_PetrolLevel_getValue(){
     return CAN1sig_PetrolLevel.raw;
}
static bool CAN1sig_PetrolLevel_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_PetrolLevel.raw =  val;
    return !saturation;
}
static void CAN1sig_PetrolLevel_setRaw(uint8_t raw){
    CAN1sig_PetrolLevel.raw = raw;
}

// EngPower
static double CAN1sig_EngPower_getValue(){
     return ((double) CAN1sig_EngPower.raw) * CAN1sig_EngPower.factor + CAN1sig_EngPower.offset;
}
static bool CAN1sig_EngPower_setValue(double val){
    bool saturation = false;
    if(val > CAN1sig_EngPower.max){
        saturation = true;
        val = CAN1sig_EngPower.max;
    }else if(val < CAN1sig_EngPower.min){
        saturation = true;
        val = CAN1sig_EngPower.min;
    }

    CAN1sig_EngPower.raw =  (val-CAN1sig_EngPower.offset)/CAN1sig_EngPower.factor;
    return !saturation;
}
static void CAN1sig_EngPower_setRaw(uint16_t raw){
    CAN1sig_EngPower.raw = raw;
}

// CarSpeed
static double CAN1sig_CarSpeed_getValue(){
     return ((double) CAN1sig_CarSpeed.raw) * CAN1sig_CarSpeed.factor + CAN1sig_CarSpeed.offset;
}
static bool CAN1sig_CarSpeed_setValue(double val){
    bool saturation = false;
    if(val > CAN1sig_CarSpeed.max){
        saturation = true;
        val = CAN1sig_CarSpeed.max;
    }else if(val < CAN1sig_CarSpeed.min){
        saturation = true;
        val = CAN1sig_CarSpeed.min;
    }

    CAN1sig_CarSpeed.raw =  (val-CAN1sig_CarSpeed.offset)/CAN1sig_CarSpeed.factor;
    return !saturation;
}
static void CAN1sig_CarSpeed_setRaw(uint16_t raw){
    CAN1sig_CarSpeed.raw = raw;
}

// GearLock
static CAN1sig_GearLockVT_t CAN1sig_GearLock_getValue(){
     return CAN1sig_GearLock.raw;
}
static bool CAN1sig_GearLock_setValue(CAN1sig_GearLockVT_t val){
    bool saturation = false;
    CAN1sig_GearLock.raw =  val;
    return !saturation;
}
static void CAN1sig_GearLock_setRaw(bool raw){
    CAN1sig_GearLock.raw = raw;
}

// Diagnostics
static uint8_t CAN1sig_Diagnostics_getValue(){
     return CAN1sig_Diagnostics.raw;
}
static bool CAN1sig_Diagnostics_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_Diagnostics.raw =  val;
    return !saturation;
}
static void CAN1sig_Diagnostics_setRaw(uint8_t raw){
    CAN1sig_Diagnostics.raw = raw;
}

// AccelerationForce
static double CAN1sig_AccelerationForce_getValue(){
     return ((double) CAN1sig_AccelerationForce.raw) * CAN1sig_AccelerationForce.factor + CAN1sig_AccelerationForce.offset;
}
static bool CAN1sig_AccelerationForce_setValue(double val){
    bool saturation = false;
    if(val > CAN1sig_AccelerationForce.max){
        saturation = true;
        val = CAN1sig_AccelerationForce.max;
    }else if(val < CAN1sig_AccelerationForce.min){
        saturation = true;
        val = CAN1sig_AccelerationForce.min;
    }

    CAN1sig_AccelerationForce.raw =  (val-CAN1sig_AccelerationForce.offset)/CAN1sig_AccelerationForce.factor;
    return !saturation;
}
static void CAN1sig_AccelerationForce_setRaw(uint16_t raw){
    CAN1sig_AccelerationForce.raw = raw;
}

/*
 * Messages:  send and receive private methods
 */


static void CAN1_MultiplexExample2_send(){
    CAN1_MultiplexExample2.raw = 0;

    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal7.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal7.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal7.startbit;

    if(CAN1sig_ExSignal7.raw == 0){
    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal8.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal8.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal8.startbit;

    if(CAN1sig_ExSignal8.raw == 0){
    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal9.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal9.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal9.startbit;
    }
    }
    CAN1_SendCallback(
        CAN1_MultiplexExample2.raw,
        CAN1_MultiplexExample2.ID,
        CAN1_MultiplexExample2.is_extended,
        CAN1_MultiplexExample2.DLC
    );
};
static void CAN1_MultiplexExample_receive(){

    CAN1sig_EXSignal1.raw = (CAN1_MultiplexExample.raw >> CAN1_MultiplexExample.signals.CAN1sig_EXSignal1.startbit) & CAN1_MultiplexExample.signals.CAN1sig_EXSignal1.mask;

    if(CAN1sig_EXSignal1.raw == 4){
    CAN1sig_EXSignal2.raw = (CAN1_MultiplexExample.raw >> CAN1_MultiplexExample.signals.CAN1sig_EXSignal2.startbit) & CAN1_MultiplexExample.signals.CAN1sig_EXSignal2.mask;

    if(CAN1sig_EXSignal2.raw == 0){
    CAN1sig_EXSignal4.raw = (CAN1_MultiplexExample.raw >> CAN1_MultiplexExample.signals.CAN1sig_EXSignal4.startbit) & CAN1_MultiplexExample.signals.CAN1sig_EXSignal4.mask;
    }
    }
    
};
static void CAN1_Ignition_Info_receive(){

    CAN1sig_StarterKey.raw = reverseBits((CAN1_Ignition_Info.raw >> CAN1_Ignition_Info.signals.CAN1sig_StarterKey.startbit) & CAN1_Ignition_Info.signals.CAN1sig_StarterKey.mask, CAN1sig_StarterKey.length);
    
};
static void CAN1_DiagResponse_Motor_send(){
    CAN1_DiagResponse_Motor.raw = 0;

    CAN1_SendCallback(
        CAN1_DiagResponse_Motor.raw,
        CAN1_DiagResponse_Motor.ID,
        CAN1_DiagResponse_Motor.is_extended,
        CAN1_DiagResponse_Motor.DLC
    );
};
static void CAN1_NM_Engine_send(){
    CAN1_NM_Engine.raw = 0;

    CAN1_NM_Engine.raw |= (uint64_t) ((uint64_t) CAN1sig_SleepInd.raw & CAN1_NM_Engine.signals.CAN1sig_SleepInd.mask) << CAN1_NM_Engine.signals.CAN1sig_SleepInd.startbit;
    CAN1_SendCallback(
        CAN1_NM_Engine.raw,
        CAN1_NM_Engine.ID,
        CAN1_NM_Engine.is_extended,
        CAN1_NM_Engine.DLC
    );
};
static void CAN1_GearBoxInfo_send(){
    CAN1_GearBoxInfo.raw = 0;

    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) CAN1sig_ShiftRequest.raw & CAN1_GearBoxInfo.signals.CAN1sig_ShiftRequest.mask) << CAN1_GearBoxInfo.signals.CAN1sig_ShiftRequest.startbit;
    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) reverseBits(CAN1sig_Gear.raw,  CAN1sig_Gear.length) & CAN1_GearBoxInfo.signals.CAN1sig_Gear.mask) << CAN1_GearBoxInfo.signals.CAN1sig_Gear.startbit;
    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) CAN1sig_EcoMode.raw & CAN1_GearBoxInfo.signals.CAN1sig_EcoMode.mask) << CAN1_GearBoxInfo.signals.CAN1sig_EcoMode.startbit;
    CAN1_SendCallback(
        CAN1_GearBoxInfo.raw,
        CAN1_GearBoxInfo.ID,
        CAN1_GearBoxInfo.is_extended,
        CAN1_GearBoxInfo.DLC
    );
};
static void CAN1_EngineStatus_send(){
    CAN1_EngineStatus.raw = 0;

    CAN1_EngineStatus.raw |= (uint64_t) ((uint64_t) CAN1sig_Status.raw & CAN1_EngineStatus.signals.CAN1sig_Status.mask) << CAN1_EngineStatus.signals.CAN1sig_Status.startbit;
    CAN1_EngineStatus.raw |= (uint64_t) ((uint64_t) CAN1sig_ErrorCode.raw & CAN1_EngineStatus.signals.CAN1sig_ErrorCode.mask) << CAN1_EngineStatus.signals.CAN1sig_ErrorCode.startbit;
    CAN1_SendCallback(
        CAN1_EngineStatus.raw,
        CAN1_EngineStatus.ID,
        CAN1_EngineStatus.is_extended,
        CAN1_EngineStatus.DLC
    );
};
static void CAN1_EngineDataIEEE_send(){
    CAN1_EngineDataIEEE.raw = 0;

    CAN1_EngineDataIEEE.raw |= (uint64_t) ((uint64_t) CAN1sig_EngSpeed.raw & CAN1_EngineDataIEEE.signals.CAN1sig_EngSpeed.mask) << CAN1_EngineDataIEEE.signals.CAN1sig_EngSpeed.startbit;
    CAN1_EngineDataIEEE.raw |= (uint64_t) ((uint64_t) CAN1sig_EngForce.raw & CAN1_EngineDataIEEE.signals.CAN1sig_EngForce.mask) << CAN1_EngineDataIEEE.signals.CAN1sig_EngForce.startbit;
    CAN1_SendCallback(
        CAN1_EngineDataIEEE.raw,
        CAN1_EngineDataIEEE.ID,
        CAN1_EngineDataIEEE.is_extended,
        CAN1_EngineDataIEEE.DLC
    );
};
static void CAN1_EngineData_send(){
    CAN1_EngineData.raw = 0;

    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngSpeed.raw & CAN1_EngineData.signals.CAN1sig_EngSpeed.mask) << CAN1_EngineData.signals.CAN1sig_EngSpeed.startbit;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngTemp.raw & CAN1_EngineData.signals.CAN1sig_EngTemp.mask) << CAN1_EngineData.signals.CAN1sig_EngTemp.startbit;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_IdleRunning.raw & CAN1_EngineData.signals.CAN1sig_IdleRunning.mask) << CAN1_EngineData.signals.CAN1sig_IdleRunning.startbit;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_PetrolLevel.raw & CAN1_EngineData.signals.CAN1sig_PetrolLevel.mask) << CAN1_EngineData.signals.CAN1sig_PetrolLevel.startbit;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngForce.raw & CAN1_EngineData.signals.CAN1sig_EngForce.mask) << CAN1_EngineData.signals.CAN1sig_EngForce.startbit;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngPower.raw & CAN1_EngineData.signals.CAN1sig_EngPower.mask) << CAN1_EngineData.signals.CAN1sig_EngPower.startbit;
    CAN1_SendCallback(
        CAN1_EngineData.raw,
        CAN1_EngineData.ID,
        CAN1_EngineData.is_extended,
        CAN1_EngineData.DLC
    );
};
static void CAN1_ABSdata_send(){
    CAN1_ABSdata.raw = 0;

    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_CarSpeed.raw & CAN1_ABSdata.signals.CAN1sig_CarSpeed.mask) << CAN1_ABSdata.signals.CAN1sig_CarSpeed.startbit;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_GearLock.raw & CAN1_ABSdata.signals.CAN1sig_GearLock.mask) << CAN1_ABSdata.signals.CAN1sig_GearLock.startbit;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_Diagnostics.raw & CAN1_ABSdata.signals.CAN1sig_Diagnostics.mask) << CAN1_ABSdata.signals.CAN1sig_Diagnostics.startbit;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_AccelerationForce.raw & CAN1_ABSdata.signals.CAN1sig_AccelerationForce.mask) << CAN1_ABSdata.signals.CAN1sig_AccelerationForce.startbit;
    CAN1_SendCallback(
        CAN1_ABSdata.raw,
        CAN1_ABSdata.ID,
        CAN1_ABSdata.is_extended,
        CAN1_ABSdata.DLC
    );
};

/*
 * Messages: Message struct definitions
 */



// Comment: None
struct CAN1_MultiplexExample2_t CAN1_MultiplexExample2 = {
    .ID = 0x301, //dec: 769
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_MultiplexExample2_send,
    .signals = {
        .CAN1sig_ExSignal7 = {
            .signal = &CAN1sig_ExSignal7,
            .startbit = 0,
            .mask = 0b11111111
        },
        
        .CAN1sig_ExSignal8 = {
            .multiplexor = &CAN1sig_ExSignal7,
            .multiplexValues = {0},
            .signal = &CAN1sig_ExSignal8,
            .startbit = 8,
            .mask = 0b11111111
        },
        
        .CAN1sig_ExSignal9 = {
            .multiplexor = &CAN1sig_ExSignal8,
            .multiplexValues = {0},
            .signal = &CAN1sig_ExSignal9,
            .startbit = 16,
            .mask = 0b11111111
        },
        
    }
};
// Comment: None
struct CAN1_MultiplexExample_t CAN1_MultiplexExample = {
    .ID = 0x300, //dec: 768
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .receive = CAN1_MultiplexExample_receive,
    .signals = {
        .CAN1sig_EXSignal1 = {
            .signal = &CAN1sig_EXSignal1,
            .startbit = 0,
            .mask = 0b11111111
        },
        
        .CAN1sig_EXSignal2 = {
            .multiplexor = &CAN1sig_EXSignal1,
            .multiplexValues = {4},
            .signal = &CAN1sig_EXSignal2,
            .startbit = 8,
            .mask = 0b11111111
        },
        
        .CAN1sig_EXSignal3 = {
            .multiplexor = &CAN1sig_EXSignal1,
            .multiplexValues = {4},
            .signal = &CAN1sig_EXSignal3,
            .startbit = 16,
            .mask = 0b11111111
        },
        
        .CAN1sig_EXSignal4 = {
            .multiplexor = &CAN1sig_EXSignal2,
            .multiplexValues = {0},
            .signal = &CAN1sig_EXSignal4,
            .startbit = 24,
            .mask = 0b11111111
        },
        
        //EXSignal5 is not mapped to this ECU

        //EXSignal6 is not mapped to this ECU

    }
};
// Comment: None
struct CAN1_Ignition_Info_t CAN1_Ignition_Info = {
    .ID = 0x67, //dec: 103
    .is_extended = false,
    .DLC = 2,
    .raw = 0,
    .receive = CAN1_Ignition_Info_receive,
    .signals = {
        .CAN1sig_StarterKey = {
            .signal = &CAN1sig_StarterKey,
            .startbit = 7,
            .mask = 0b1
        },
        
    }
};
// Comment: None
struct CAN1_DiagResponse_Motor_t CAN1_DiagResponse_Motor = {
    .ID = 0x608, //dec: 1544
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_DiagResponse_Motor_send,
    .signals = {
    }
};
// Comment: None
struct CAN1_NM_Engine_t CAN1_NM_Engine = {
    .ID = 0x51b, //dec: 1307
    .is_extended = false,
    .DLC = 4,
    .raw = 0,
    .send = CAN1_NM_Engine_send,
    .signals = {
        .CAN1sig_SleepInd = {
            .signal = &CAN1sig_SleepInd,
            .startbit = 12,
            .mask = 0b1
        },
        
    }
};
// Comment: None
struct CAN1_GearBoxInfo_t CAN1_GearBoxInfo = {
    .ID = 0x3fc, //dec: 1020
    .is_extended = false,
    .DLC = 1,
    .raw = 0,
    .send = CAN1_GearBoxInfo_send,
    .signals = {
        .CAN1sig_ShiftRequest = {
            .signal = &CAN1sig_ShiftRequest,
            .startbit = 4,
            .mask = 0b1
        },
        
        .CAN1sig_Gear = {
            .signal = &CAN1sig_Gear,
            .startbit = 0,
            .mask = 0b111
        },
        
        .CAN1sig_EcoMode = {
            .signal = &CAN1sig_EcoMode,
            .startbit = 6,
            .mask = 0b11
        },
        
    }
};
// Comment: None
struct CAN1_EngineStatus_t CAN1_EngineStatus = {
    .ID = 0x65, //dec: 101
    .is_extended = false,
    .DLC = 1,
    .raw = 0,
    .send = CAN1_EngineStatus_send,
    .signals = {
        .CAN1sig_Status = {
            .signal = &CAN1sig_Status,
            .startbit = 0,
            .mask = 0b11
        },
        
        .CAN1sig_ErrorCode = {
            .signal = &CAN1sig_ErrorCode,
            .startbit = 2,
            .mask = 0b111111
        },
        
    }
};
// Comment: None
struct CAN1_EngineDataIEEE_t CAN1_EngineDataIEEE = {
    .ID = 0x66, //dec: 102
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_EngineDataIEEE_send,
    .signals = {
        .CAN1sig_EngSpeed = {
            .signal = &CAN1sig_EngSpeed,
            .startbit = 0,
            .mask = 0b11111111111111111111111111111111
        },
        
        .CAN1sig_EngForce = {
            .signal = &CAN1sig_EngForce,
            .startbit = 32,
            .mask = 0b11111111111111111111111111111111
        },
        
    }
};
// Comment: None
struct CAN1_EngineData_t CAN1_EngineData = {
    .ID = 0x64, //dec: 100
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_EngineData_send,
    .signals = {
        .CAN1sig_EngSpeed = {
            .signal = &CAN1sig_EngSpeed,
            .startbit = 0,
            .mask = 0b1111111111111111
        },
        
        .CAN1sig_EngTemp = {
            .signal = &CAN1sig_EngTemp,
            .startbit = 16,
            .mask = 0b1111111
        },
        
        .CAN1sig_IdleRunning = {
            .signal = &CAN1sig_IdleRunning,
            .startbit = 23,
            .mask = 0b1
        },
        
        .CAN1sig_PetrolLevel = {
            .signal = &CAN1sig_PetrolLevel,
            .startbit = 24,
            .mask = 0b11111111
        },
        
        .CAN1sig_EngForce = {
            .signal = &CAN1sig_EngForce,
            .startbit = 32,
            .mask = 0b1111111111111111
        },
        
        .CAN1sig_EngPower = {
            .signal = &CAN1sig_EngPower,
            .startbit = 48,
            .mask = 0b1111111111111111
        },
        
    }
};
// Comment: None
struct CAN1_ABSdata_t CAN1_ABSdata = {
    .ID = 0xc9, //dec: 201
    .is_extended = false,
    .DLC = 6,
    .raw = 0,
    .send = CAN1_ABSdata_send,
    .signals = {
        .CAN1sig_CarSpeed = {
            .signal = &CAN1sig_CarSpeed,
            .startbit = 0,
            .mask = 0b1111111111
        },
        
        .CAN1sig_GearLock = {
            .signal = &CAN1sig_GearLock,
            .startbit = 15,
            .mask = 0b1
        },
        
        .CAN1sig_Diagnostics = {
            .signal = &CAN1sig_Diagnostics,
            .startbit = 16,
            .mask = 0b11111111
        },
        
        .CAN1sig_AccelerationForce = {
            .signal = &CAN1sig_AccelerationForce,
            .startbit = 32,
            .mask = 0b1111111111111111
        },
        
    }
};

