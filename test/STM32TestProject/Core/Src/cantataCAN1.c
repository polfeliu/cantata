/**
 ******************************************************************************
 * @details This file was created with cantata, a code generation tool for can databases
 * @author Pol Feliu Cuberes
 * @link https://github.com/polfeliu/cantata
 ******************************************************************************
 */

#include "cantataCAN1.h" 
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

uint32_t SingleToUint32(single s){
    union SingleUint32_u{
        single s;
        uint32_t u;
    }SingleUint32 = { .s = s};

    return SingleUint32.u;
}
single Uint32ToSingle(uint32_t u){
    union SingleUint32_u{
        single s;
        uint32_t u;
    }SingleUint32 = { .u = u};

    return SingleUint32.s;
}

uint64_t DoubleToUint64(double d){
    union DoubleUint64_u{
        double d;
        uint64_t u;
    }DoubleUint64 = { .d = d};
    return DoubleUint64.u;
}

double Uint64ToDouble(uint64_t u){
    union DoubleUint64_u{
        double d;
        uint64_t u;
    }DoubleUint64 = { .u = u};
    return DoubleUint64.d;
}


/*
 * Interaction Layer: Tasks to send the cyclic messages
 */
        
TaskHandle_t vTaskInteractionLayer_CAN1_cyclic_1000ms_Handle;
static void vTaskInteractionLayer_CAN1_cyclic_1000ms( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(1000);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;){

        CAN1_NM_Engine.send();

        vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
    }
}
    
/*
 * Interaction Layer: Tasks to send the cyclic message at fast rate
 */
        
TaskHandle_t vTaskInteractionLayer_CAN1_ABSdata_fast_Handle;
static void vTaskInteractionLayer_CAN1_ABSdata_fast( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(100);
    vTaskSuspend(vTaskInteractionLayer_CAN1_ABSdata_fast_Handle); //Start in Suspended State
    for(;;){

        if((CAN1_ABSdata.repetitionsleft == 0)
        ){
            // If repetitions are completed and signals are inactive suspend the task
            vTaskSuspend(vTaskInteractionLayer_CAN1_ABSdata_fast_Handle);
        }else{
            CAN1_ABSdata.send();
            if(CAN1_ABSdata.repetitionsleft > 0){
                CAN1_ABSdata.repetitionsleft--;
            }
            vTaskDelay(xTimeIncrement);
        }       
        
    }
}
TaskHandle_t vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume_Handle;
static void vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume( void *pvParameters ){
    for(;;){
        xTaskNotifyWait( 0,     //ulBitsToClearOnEntry
                         0,     //ulBitsToClearOnExit
                         NULL,  //*pulNotificationValue
                         portMAX_DELAY );
        vTaskDelay(pdMS_TO_TICKS(100));
        CAN1_ABSdata.repetitionsleft = CAN1_ABSdata.repetitions;
        vTaskResume(vTaskInteractionLayer_CAN1_ABSdata_fast_Handle);
    }
}


TaskHandle_t vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle;
static void vTaskInteractionLayer_CAN1_MultiplexExample2_fast( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(100);
    vTaskSuspend(vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle); //Start in Suspended State
    for(;;){

        if((CAN1_MultiplexExample2.repetitionsleft == 0)
            &(CAN1sig_ExSignal9.raw == CAN1sig_ExSignal9.inactiveValue)
        ){
            // If repetitions are completed and signals are inactive suspend the task
            vTaskSuspend(vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle);
        }else{
            CAN1_MultiplexExample2.send();
            if(CAN1_MultiplexExample2.repetitionsleft > 0){
                CAN1_MultiplexExample2.repetitionsleft--;
            }
            vTaskDelay(xTimeIncrement);
        }       
        
    }
}
TaskHandle_t vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle;
static void vTaskInteractionLayer_CAN1_EngineStatus_fast( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(50);
    vTaskSuspend(vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle); //Start in Suspended State
    for(;;){

        if(false
            |(CAN1sig_ErrorCode.raw != CAN1sig_ErrorCode.inactiveValue)
        ){
            CAN1_EngineStatus.repetitionsleft = CAN1_EngineStatus.repetitions;
        }
        
        if((CAN1_EngineStatus.repetitionsleft == 0)
            &(CAN1sig_ErrorCode.raw == CAN1sig_ErrorCode.inactiveValue)
        ){
            // If repetitions are completed and signals are inactive suspend the task
            vTaskSuspend(vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle);
        }else{
            CAN1_EngineStatus.send();
            if(CAN1_EngineStatus.repetitionsleft > 0){
                CAN1_EngineStatus.repetitionsleft--;
            }
            vTaskDelay(xTimeIncrement);
        }       
        
    }
}
TaskHandle_t vTaskInteractionLayer_CAN1_EngineData_fast_Handle;
static void vTaskInteractionLayer_CAN1_EngineData_fast( void *pvParameters ){
    const TickType_t xTimeIncrement = pdMS_TO_TICKS(100);
    vTaskSuspend(vTaskInteractionLayer_CAN1_EngineData_fast_Handle); //Start in Suspended State
    for(;;){

        if((CAN1_EngineData.repetitionsleft == 0)
        ){
            // If repetitions are completed and signals are inactive suspend the task
            vTaskSuspend(vTaskInteractionLayer_CAN1_EngineData_fast_Handle);
        }else{
            CAN1_EngineData.send();
            if(CAN1_EngineData.repetitionsleft > 0){
                CAN1_EngineData.repetitionsleft--;
            }
            vTaskDelay(xTimeIncrement);
        }       
        
    }
}
TaskHandle_t vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume_Handle;
static void vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume( void *pvParameters ){
    for(;;){
        xTaskNotifyWait( 0,     //ulBitsToClearOnEntry
                         0,     //ulBitsToClearOnExit
                         NULL,  //*pulNotificationValue
                         portMAX_DELAY );
        vTaskDelay(pdMS_TO_TICKS(100));
        CAN1_EngineData.repetitionsleft = CAN1_EngineData.repetitions;
        vTaskResume(vTaskInteractionLayer_CAN1_EngineData_fast_Handle);
    }
}


/*
 * Interaction Layer: Task to send Messages whose signals are sensitive to Write or Change
 */
TaskHandle_t vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle;
static void vTaskInteractionLayer_CAN1_OnWriteOnChange(void *pvParameters){
    for(;;){
        xTaskNotifyWait( 0,     //ulBitsToClearOnEntry
                         0,     //ulBitsToClearOnExit
                         NULL,  //*pulNotificationValue
                         portMAX_DELAY );
    
        if(false
            || (CAN1sig_AccelerationForce.sent == false)
        ){
            CAN1_ABSdata.send();
        }
    
        if(false
            || (CAN1sig_Status.sent == false)
        ){
            CAN1_EngineStatus.send();
        }
    
        if(false
            || (CAN1sig_EngSpeed.sent == false)
            || (CAN1sig_EngTemp.sent == false)
            || (CAN1sig_IdleRunning.sent == false)
        ){
            CAN1_EngineData.send();
        }
    
    }
}
    


/*
 * Interaction Layer: Start function to initialize tasks
 */
void CAN1_InteractionLayerStart(){

    /*
     * Cyclic Tasks
     */
    xTaskCreate(
        vTaskInteractionLayer_CAN1_cyclic_1000ms,
        "InteractionLayer_CAN1_cyclic_1000ms",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_cyclic_1000ms_Handle
    ); 

    /*
     * Fast Time Tasks
     */
    xTaskCreate(
        vTaskInteractionLayer_CAN1_ABSdata_fast,
        "vTaskInteractionLayer_CAN1_ABSdata_fast",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_ABSdata_fast_Handle
    ); 
    xTaskCreate(
        vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume,
        "vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume_Handle
    ); 
    xTaskCreate(
        vTaskInteractionLayer_CAN1_MultiplexExample2_fast,
        "vTaskInteractionLayer_CAN1_MultiplexExample2_fast",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle
    ); 
    xTaskCreate(
        vTaskInteractionLayer_CAN1_EngineStatus_fast,
        "vTaskInteractionLayer_CAN1_EngineStatus_fast",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle
    ); 
    xTaskCreate(
        vTaskInteractionLayer_CAN1_EngineData_fast,
        "vTaskInteractionLayer_CAN1_EngineData_fast",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_EngineData_fast_Handle
    ); 
    xTaskCreate(
        vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume,
        "vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume_Handle
    ); 

    /*
     * OnWriteOnChange Task
     */
    xTaskCreate(
        vTaskInteractionLayer_CAN1_OnWriteOnChange,
        "vTaskInteractionLayer_CAN1_OnWriteOnChange",
        100,
        NULL,
        tskIDLE_PRIORITY,
        &vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle
    ); 
}





/*
 * Interaction Layer: Function to Stop Tasks
 */
void CAN1_InteractionLayerStop(){

    /*
     * Cyclic Tasks
     */
    vTaskDelete(
        vTaskInteractionLayer_CAN1_cyclic_1000ms_Handle
    ); 

    /*
     * Fast Time Tasks
     */
    vTaskDelete(
        vTaskInteractionLayer_CAN1_ABSdata_fast_Handle
    ); 
    vTaskDelete(
        vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume_Handle
    ); 
    vTaskDelete(
        vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle
    ); 
    vTaskDelete(
        vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle
    ); 
    vTaskDelete(
        vTaskInteractionLayer_CAN1_EngineData_fast_Handle
    ); 
    vTaskDelete(
        vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume_Handle
    ); 

    /*
     * OnWriteOnChange Task
     */
    vTaskDelete(
        vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle
    ); 
}





/*
 * CAN Callbacks: Receive Callback function. This function should be called when a new message arrives. The function automatically identifies the message and unpacks it into the signals
 */

void CAN1_ReceiveCallback(uint8_t data[], uint8_t DLC, uint32_t ID, bool is_extended){
    if((ID > 0x1FFFFFFF) & is_extended){
        //invalid extended identifier
    }else if((ID > 0x7FF) & !is_extended){
        //invalid standard identifier
    }

    else if((ID==CAN1_FloatExample4.ID) & (is_extended==CAN1_FloatExample4.is_extended) & (DLC==CAN1_FloatExample4.DLC)){
        memcpy(CAN1_FloatExample4.raw.bytes, data, sizeof CAN1_FloatExample4.raw.bytes);
        CAN1_FloatExample4.receive();
    }
    else if((ID==CAN1_FloatExample3.ID) & (is_extended==CAN1_FloatExample3.is_extended) & (DLC==CAN1_FloatExample3.DLC)){
        memcpy(CAN1_FloatExample3.raw.bytes, data, sizeof CAN1_FloatExample3.raw.bytes);
        CAN1_FloatExample3.receive();
    }
    else if((ID==CAN1_MultiplexExample.ID) & (is_extended==CAN1_MultiplexExample.is_extended) & (DLC==CAN1_MultiplexExample.DLC)){
        memcpy(CAN1_MultiplexExample.raw.bytes, data, sizeof CAN1_MultiplexExample.raw.bytes);
        CAN1_MultiplexExample.receive();
    }
    else if((ID==CAN1_Ignition_Info.ID) & (is_extended==CAN1_Ignition_Info.is_extended) & (DLC==CAN1_Ignition_Info.DLC)){
        memcpy(CAN1_Ignition_Info.raw.bytes, data, sizeof CAN1_Ignition_Info.raw.bytes);
        CAN1_Ignition_Info.receive();
    }
    else{
        //ID is not received by this ECU
    }
}


/*
 * Signal getValue, setValue and setRaw method prototypes
 */

static double CAN1sig_DoubleExample2_getValue();
static single CAN1sig_SingleExample3_getValue();
static double CAN1sig_DoubleExample_getValue();
static bool CAN1sig_DoubleExample_setValue(double);
static void CAN1sig_DoubleExample_setRaw(double);
static single CAN1sig_SingleExample_getValue();
static bool CAN1sig_SingleExample_setValue(single);
static void CAN1sig_SingleExample_setRaw(single);
static single CAN1sig_SingleExample2_getValue();
static bool CAN1sig_SingleExample2_setValue(single);
static void CAN1sig_SingleExample2_setRaw(single);
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
static double CAN1sig_EngTemp_getValue();
static bool CAN1sig_EngTemp_setValue(double);
static void CAN1sig_EngTemp_setRaw(uint8_t);
static CAN1sig_IdleRunningVT_t CAN1sig_IdleRunning_getValue();
static bool CAN1sig_IdleRunning_setValue(CAN1sig_IdleRunningVT_t);
static void CAN1sig_IdleRunning_setRaw(bool);
static uint8_t CAN1sig_PetrolLevel_getValue();
static bool CAN1sig_PetrolLevel_setValue(uint8_t);
static void CAN1sig_PetrolLevel_setRaw(uint8_t);
static uint16_t CAN1sig_EngForce_getValue();
static bool CAN1sig_EngForce_setValue(uint16_t);
static void CAN1sig_EngForce_setRaw(uint16_t);
static double CAN1sig_EngPower_getValue();
static bool CAN1sig_EngPower_setValue(double);
static void CAN1sig_EngPower_setRaw(uint16_t);


/*
 * Signals: Signal struct definitions
 */


struct CAN1sig_DoubleExample2_t CAN1sig_DoubleExample2 = {
    .length = 64,
    .byte_order = big_endian,
    .value_type = Tdouble,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -1.7e+308,
    .max = 1.7e+308,
    .raw = 0,
    .getValue = CAN1sig_DoubleExample2_getValue
};
    
struct CAN1sig_SingleExample3_t CAN1sig_SingleExample3 = {
    .length = 32,
    .byte_order = big_endian,
    .value_type = Tsingle,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -3.4e+38,
    .max = 3.4e+38,
    .raw = 0,
    .getValue = CAN1sig_SingleExample3_getValue
};
    
struct CAN1sig_DoubleExample_t CAN1sig_DoubleExample = {
    .length = 64,
    .byte_order = little_endian,
    .value_type = Tdouble,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -1.7e+308,
    .max = 1.7e+308,
    .raw = 0,
    .getValue = CAN1sig_DoubleExample_getValue,
    .setValue = CAN1sig_DoubleExample_setValue,
    .setRaw = CAN1sig_DoubleExample_setRaw,
    .sent = true
};
    
struct CAN1sig_SingleExample_t CAN1sig_SingleExample = {
    .length = 32,
    .byte_order = big_endian,
    .value_type = Tsingle,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -3.4e+38,
    .max = 3.4e+38,
    .raw = 0,
    .getValue = CAN1sig_SingleExample_getValue,
    .setValue = CAN1sig_SingleExample_setValue,
    .setRaw = CAN1sig_SingleExample_setRaw,
    .sent = true
};
    
struct CAN1sig_SingleExample2_t CAN1sig_SingleExample2 = {
    .length = 32,
    .byte_order = big_endian,
    .value_type = Tsingle,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -3.4e+38,
    .max = 3.4e+38,
    .raw = 0,
    .getValue = CAN1sig_SingleExample2_getValue,
    .setValue = CAN1sig_SingleExample2_setValue,
    .setRaw = CAN1sig_SingleExample2_setRaw,
    .sent = true
};
    
struct CAN1sig_CarSpeed_t CAN1sig_CarSpeed = {
    .length = 10,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "mph",
    .initial_value = 0.0,
    .factor = 0.5,
    .offset = 0,
    .min = 0,
    .max = 511.5,
    .raw = 0,
    .getValue = CAN1sig_CarSpeed_getValue,
    .setValue = CAN1sig_CarSpeed_setValue,
    .setRaw = CAN1sig_CarSpeed_setRaw,
    .sent = true
};
    
struct CAN1sig_GearLock_t CAN1sig_GearLock = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_GearLock_getValue,
    .setValue = CAN1sig_GearLock_setValue,
    .setRaw = CAN1sig_GearLock_setRaw,
    .sent = true
};
    
struct CAN1sig_Diagnostics_t CAN1sig_Diagnostics = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 255,
    .raw = 0,
    .getValue = CAN1sig_Diagnostics_getValue,
    .setValue = CAN1sig_Diagnostics_setValue,
    .setRaw = CAN1sig_Diagnostics_setRaw,
    .sent = true
};
    
struct CAN1sig_AccelerationForce_t CAN1sig_AccelerationForce = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "N",
    .initial_value = -10000.0,
    .factor = 1,
    .offset = -10000,
    .min = -10000,
    .max = 55535,
    .raw = 0,
    .getValue = CAN1sig_AccelerationForce_getValue,
    .setValue = CAN1sig_AccelerationForce_setValue,
    .setRaw = CAN1sig_AccelerationForce_setRaw,
    .sent = true
};
    
struct CAN1sig_ExSignal7_t CAN1sig_ExSignal7 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal7_getValue,
    .setValue = CAN1sig_ExSignal7_setValue,
    .setRaw = CAN1sig_ExSignal7_setRaw,
    .sent = true
};
    
struct CAN1sig_ExSignal8_t CAN1sig_ExSignal8 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal8_getValue,
    .setValue = CAN1sig_ExSignal8_setValue,
    .setRaw = CAN1sig_ExSignal8_setRaw,
    .sent = true
};
    
struct CAN1sig_ExSignal9_t CAN1sig_ExSignal9 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = -128,
    .max = 127,
    .raw = 0,
    .getValue = CAN1sig_ExSignal9_getValue,
    .setValue = CAN1sig_ExSignal9_setValue,
    .setRaw = CAN1sig_ExSignal9_setRaw,
    .sent = true,
    .inactiveValue = 0,
};
    
struct CAN1sig_EXSignal1_t CAN1sig_EXSignal1 = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tint8_t,
    .unit = "",
    .initial_value = 0.0,
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
    .initial_value = 0.0,
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
    .initial_value = 0.0,
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
    .initial_value = 0.0,
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
    .initial_value = 0.0,
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
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_SleepInd_getValue,
    .setValue = CAN1sig_SleepInd_setValue,
    .setRaw = CAN1sig_SleepInd_setRaw,
    .sent = true
};
    
struct CAN1sig_ShiftRequest_t CAN1sig_ShiftRequest = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_ShiftRequest_getValue,
    .setValue = CAN1sig_ShiftRequest_setValue,
    .setRaw = CAN1sig_ShiftRequest_setRaw,
    .sent = true
};
    
struct CAN1sig_Gear_t CAN1sig_Gear = {
    .length = 3,
    .byte_order = big_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 3.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 7,
    .raw = 3,
    .getValue = CAN1sig_Gear_getValue,
    .setValue = CAN1sig_Gear_setValue,
    .setRaw = CAN1sig_Gear_setRaw,
    .sent = true
};
    
struct CAN1sig_EcoMode_t CAN1sig_EcoMode = {
    .length = 2,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 3,
    .raw = 0,
    .getValue = CAN1sig_EcoMode_getValue,
    .setValue = CAN1sig_EcoMode_setValue,
    .setRaw = CAN1sig_EcoMode_setRaw,
    .sent = true
};
    
struct CAN1sig_Status_t CAN1sig_Status = {
    .length = 2,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 3,
    .raw = 0,
    .getValue = CAN1sig_Status_getValue,
    .setValue = CAN1sig_Status_setValue,
    .setRaw = CAN1sig_Status_setRaw,
    .sent = true
};
    
struct CAN1sig_ErrorCode_t CAN1sig_ErrorCode = {
    .length = 6,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 63,
    .raw = 0,
    .getValue = CAN1sig_ErrorCode_getValue,
    .setValue = CAN1sig_ErrorCode_setValue,
    .setRaw = CAN1sig_ErrorCode_setRaw,
    .sent = true,
    .inactiveValue = 0,
};
    
struct CAN1sig_EngSpeed_t CAN1sig_EngSpeed = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "rpm",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 65535,
    .raw = 0,
    .getValue = CAN1sig_EngSpeed_getValue,
    .setValue = CAN1sig_EngSpeed_setValue,
    .setRaw = CAN1sig_EngSpeed_setRaw,
    .sent = true
};
    
struct CAN1sig_EngTemp_t CAN1sig_EngTemp = {
    .length = 7,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "degC",
    .initial_value = -50.0,
    .factor = 2,
    .offset = -50,
    .min = -50,
    .max = 204,
    .raw = 0,
    .getValue = CAN1sig_EngTemp_getValue,
    .setValue = CAN1sig_EngTemp_setValue,
    .setRaw = CAN1sig_EngTemp_setRaw,
    .sent = true
};
    
struct CAN1sig_IdleRunning_t CAN1sig_IdleRunning = {
    .length = 1,
    .byte_order = little_endian,
    .value_type = Tbool,
    .unit = "",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 1,
    .raw = 0,
    .getValue = CAN1sig_IdleRunning_getValue,
    .setValue = CAN1sig_IdleRunning_setValue,
    .setRaw = CAN1sig_IdleRunning_setRaw,
    .sent = true
};
    
struct CAN1sig_PetrolLevel_t CAN1sig_PetrolLevel = {
    .length = 8,
    .byte_order = little_endian,
    .value_type = Tuint8_t,
    .unit = "l",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 255,
    .raw = 0,
    .getValue = CAN1sig_PetrolLevel_getValue,
    .setValue = CAN1sig_PetrolLevel_setValue,
    .setRaw = CAN1sig_PetrolLevel_setRaw,
    .sent = true
};
    
struct CAN1sig_EngForce_t CAN1sig_EngForce = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "N",
    .initial_value = 0.0,
    .factor = 1,
    .offset = 0,
    .min = 0,
    .max = 65535,
    .raw = 0,
    .getValue = CAN1sig_EngForce_getValue,
    .setValue = CAN1sig_EngForce_setValue,
    .setRaw = CAN1sig_EngForce_setRaw,
    .sent = true
};
    
struct CAN1sig_EngPower_t CAN1sig_EngPower = {
    .length = 16,
    .byte_order = little_endian,
    .value_type = Tuint16_t,
    .unit = "kW",
    .initial_value = 0.0,
    .factor = 0.01,
    .offset = 0,
    .min = 0,
    .max = 655.35,
    .raw = 0,
    .getValue = CAN1sig_EngPower_getValue,
    .setValue = CAN1sig_EngPower_setValue,
    .setRaw = CAN1sig_EngPower_setRaw,
    .sent = true
};
    

/*
 * Signals: Signal getValue and setValue private methods
 */


// DoubleExample2
static double CAN1sig_DoubleExample2_getValue(){
     return CAN1sig_DoubleExample2.raw;
}


// SingleExample3
static single CAN1sig_SingleExample3_getValue(){
     return CAN1sig_SingleExample3.raw;
}


// DoubleExample
static double CAN1sig_DoubleExample_getValue(){
     return CAN1sig_DoubleExample.raw;
}
static bool CAN1sig_DoubleExample_setValue(double val){
    bool saturation = false;
    CAN1sig_DoubleExample.setRaw(val);
    return !saturation;
}
static void CAN1sig_DoubleExample_setRaw(double raw){
    CAN1sig_DoubleExample.raw = raw;
}

// SingleExample
static single CAN1sig_SingleExample_getValue(){
     return CAN1sig_SingleExample.raw;
}
static bool CAN1sig_SingleExample_setValue(single val){
    bool saturation = false;
    CAN1sig_SingleExample.setRaw(val);
    return !saturation;
}
static void CAN1sig_SingleExample_setRaw(single raw){
    CAN1sig_SingleExample.raw = raw;
}

// SingleExample2
static single CAN1sig_SingleExample2_getValue(){
     return CAN1sig_SingleExample2.raw;
}
static bool CAN1sig_SingleExample2_setValue(single val){
    bool saturation = false;
    CAN1sig_SingleExample2.setRaw(val);
    return !saturation;
}
static void CAN1sig_SingleExample2_setRaw(single raw){
    CAN1sig_SingleExample2.raw = raw;
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

    CAN1sig_CarSpeed.setRaw((val-CAN1sig_CarSpeed.offset)/CAN1sig_CarSpeed.factor);
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
    CAN1sig_GearLock.setRaw(val);
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
    CAN1sig_Diagnostics.setRaw(val);
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

    CAN1sig_AccelerationForce.setRaw((val-CAN1sig_AccelerationForce.offset)/CAN1sig_AccelerationForce.factor);
    return !saturation;
}
static void CAN1sig_AccelerationForce_setRaw(uint16_t raw){
// GenSigSendType: OnChangeWithRepetition
    if(raw != CAN1sig_AccelerationForce.raw){
    CAN1sig_AccelerationForce.sent = false;
    CAN1sig_AccelerationForce.raw = raw;
    xTaskNotify( vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle, 0, eNoAction );
    xTaskNotify(vTaskInteractionLayer_CAN1_ABSdata_fastDelayedResume_Handle, 0, eNoAction);
    }
}

// ExSignal7
static int8_t CAN1sig_ExSignal7_getValue(){
     return CAN1sig_ExSignal7.raw;
}
static bool CAN1sig_ExSignal7_setValue(int8_t val){
    bool saturation = false;
    CAN1sig_ExSignal7.setRaw(val);
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
    CAN1sig_ExSignal8.setRaw(val);
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
    CAN1sig_ExSignal9.setRaw(val);
    return !saturation;
}
static void CAN1sig_ExSignal9_setRaw(int8_t raw){
// GenSigSendType: IfActive
    CAN1sig_ExSignal9.raw = raw;
    if(raw != CAN1sig_ExSignal9.inactiveValue){
        CAN1sig_ExSignal9.sent = false;
        vTaskResume(vTaskInteractionLayer_CAN1_MultiplexExample2_fast_Handle);
    }
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
    CAN1sig_SleepInd.setRaw(val);
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
    CAN1sig_ShiftRequest.setRaw(val);
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
    CAN1sig_Gear.setRaw(val);
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
    CAN1sig_EcoMode.setRaw(val);
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
    CAN1sig_Status.setRaw(val);
    return !saturation;
}
static void CAN1sig_Status_setRaw(uint8_t raw){
// GenSigSendType: OnWrite
    CAN1sig_Status.sent = false;
    CAN1sig_Status.raw = raw;
    xTaskNotify( vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle, 0, eNoAction );
}

// ErrorCode
static uint8_t CAN1sig_ErrorCode_getValue(){
     return CAN1sig_ErrorCode.raw;
}
static bool CAN1sig_ErrorCode_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_ErrorCode.setRaw(val);
    return !saturation;
}
static void CAN1sig_ErrorCode_setRaw(uint8_t raw){
    CAN1sig_ErrorCode.raw = raw;
// GenSigSendType: IfActiveWithRepetition
    if(raw != CAN1sig_ErrorCode.inactiveValue){
        CAN1sig_ErrorCode.sent = false;
        CAN1_EngineStatus.repetitionsleft = CAN1_EngineStatus.repetitions;
        vTaskResume(vTaskInteractionLayer_CAN1_EngineStatus_fast_Handle);
    }
}

// EngSpeed
static uint16_t CAN1sig_EngSpeed_getValue(){
     return CAN1sig_EngSpeed.raw;
}
static bool CAN1sig_EngSpeed_setValue(uint16_t val){
    bool saturation = false;
    CAN1sig_EngSpeed.setRaw(val);
    return !saturation;
}
static void CAN1sig_EngSpeed_setRaw(uint16_t raw){
// GenSigSendType: OnWrite
    CAN1sig_EngSpeed.sent = false;
    CAN1sig_EngSpeed.raw = raw;
    xTaskNotify( vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle, 0, eNoAction );
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

    CAN1sig_EngTemp.setRaw((val-CAN1sig_EngTemp.offset)/CAN1sig_EngTemp.factor);
    return !saturation;
}
static void CAN1sig_EngTemp_setRaw(uint8_t raw){
// GenSigSendType: OnWriteWithRepetition
    CAN1sig_EngTemp.sent = false;
    CAN1sig_EngTemp.raw = raw;
    xTaskNotify( vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle, 0, eNoAction );
    xTaskNotify(vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume_Handle, 0, eNoAction);
}

// IdleRunning
static CAN1sig_IdleRunningVT_t CAN1sig_IdleRunning_getValue(){
     return CAN1sig_IdleRunning.raw;
}
static bool CAN1sig_IdleRunning_setValue(CAN1sig_IdleRunningVT_t val){
    bool saturation = false;
    CAN1sig_IdleRunning.setRaw(val);
    return !saturation;
}
static void CAN1sig_IdleRunning_setRaw(bool raw){
// GenSigSendType: OnChange
    if(raw != CAN1sig_IdleRunning.raw){
    CAN1sig_IdleRunning.sent = false;
    CAN1sig_IdleRunning.raw = raw;
    xTaskNotify( vTaskInteractionLayer_CAN1_OnWriteOnChange_Handle, 0, eNoAction );
    }
}

// PetrolLevel
static uint8_t CAN1sig_PetrolLevel_getValue(){
     return CAN1sig_PetrolLevel.raw;
}
static bool CAN1sig_PetrolLevel_setValue(uint8_t val){
    bool saturation = false;
    CAN1sig_PetrolLevel.setRaw(val);
    return !saturation;
}
static void CAN1sig_PetrolLevel_setRaw(uint8_t raw){
    CAN1sig_PetrolLevel.raw = raw;
}

// EngForce
static uint16_t CAN1sig_EngForce_getValue(){
     return CAN1sig_EngForce.raw;
}
static bool CAN1sig_EngForce_setValue(uint16_t val){
    bool saturation = false;
    CAN1sig_EngForce.setRaw(val);
    return !saturation;
}
static void CAN1sig_EngForce_setRaw(uint16_t raw){
    CAN1sig_EngForce.raw = raw;
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

    CAN1sig_EngPower.setRaw((val-CAN1sig_EngPower.offset)/CAN1sig_EngPower.factor);
    return !saturation;
}
static void CAN1sig_EngPower_setRaw(uint16_t raw){
    CAN1sig_EngPower.raw = raw;
}

/*
 * Messages:  send and receive private methods
 */


static void CAN1_FloatExample4_receive(){

    portENTER_CRITICAL();
    CAN1sig_DoubleExample2.raw = Uint64ToDouble(reverseBits(CAN1_FloatExample4.raw.CAN1sig_DoubleExample2.sig, CAN1sig_DoubleExample2.length));
    portEXIT_CRITICAL();

    if(CAN1_FloatExample4.on_receive != NULL){CAN1_FloatExample4.on_receive();}
    
};
static void CAN1_FloatExample3_receive(){

    portENTER_CRITICAL();
    CAN1sig_SingleExample3.raw = Uint32ToSingle(reverseBits(CAN1_FloatExample3.raw.CAN1sig_SingleExample3.sig, CAN1sig_SingleExample3.length));
    portEXIT_CRITICAL();

    if(CAN1_FloatExample3.on_receive != NULL){CAN1_FloatExample3.on_receive();}
    
};
static void CAN1_FloatExample2_send(){
    portENTER_CRITICAL();
    memset (CAN1_FloatExample2.raw.bytes,0,sizeof CAN1_FloatExample2.raw.bytes);
    CAN1_FloatExample2.raw.CAN1sig_DoubleExample.sig = DoubleToUint64(CAN1sig_DoubleExample.raw);
    CAN1sig_DoubleExample.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_FloatExample2.raw.bytes,
        CAN1_FloatExample2.DLC,
        CAN1_FloatExample2.ID,
        CAN1_FloatExample2.is_extended
    );
};

static void CAN1_FloatExample_send(){
    portENTER_CRITICAL();
    memset (CAN1_FloatExample.raw.bytes,0,sizeof CAN1_FloatExample.raw.bytes);
    CAN1_FloatExample.raw.CAN1sig_SingleExample.sig = reverseBits(SingleToUint32(CAN1sig_SingleExample.raw),  CAN1sig_SingleExample.length);
    CAN1sig_SingleExample.sent = true;
    CAN1_FloatExample.raw.CAN1sig_SingleExample2.sig = reverseBits(SingleToUint32(CAN1sig_SingleExample2.raw),  CAN1sig_SingleExample2.length);
    CAN1sig_SingleExample2.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_FloatExample.raw.bytes,
        CAN1_FloatExample.DLC,
        CAN1_FloatExample.ID,
        CAN1_FloatExample.is_extended
    );
};

static void CAN1_ABSdata_send(){
    portENTER_CRITICAL();
    memset (CAN1_ABSdata.raw.bytes,0,sizeof CAN1_ABSdata.raw.bytes);
    CAN1_ABSdata.raw.CAN1sig_CarSpeed.sig = CAN1sig_CarSpeed.raw;
    CAN1sig_CarSpeed.sent = true;
    CAN1_ABSdata.raw.CAN1sig_GearLock.sig = CAN1sig_GearLock.raw;
    CAN1sig_GearLock.sent = true;
    CAN1_ABSdata.raw.CAN1sig_Diagnostics.sig = CAN1sig_Diagnostics.raw;
    CAN1sig_Diagnostics.sent = true;
    CAN1_ABSdata.raw.CAN1sig_AccelerationForce.sig = CAN1sig_AccelerationForce.raw;
    CAN1sig_AccelerationForce.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_ABSdata.raw.bytes,
        CAN1_ABSdata.DLC,
        CAN1_ABSdata.ID,
        CAN1_ABSdata.is_extended
    );
};

static void CAN1_MultiplexExample2_send(){
    portENTER_CRITICAL();
    memset (CAN1_MultiplexExample2.raw.bytes,0,sizeof CAN1_MultiplexExample2.raw.bytes);
    CAN1_MultiplexExample2.raw.CAN1sig_ExSignal7.sig = CAN1sig_ExSignal7.raw;
    CAN1sig_ExSignal7.sent = true;

    if(CAN1sig_ExSignal7.raw == 0){
    CAN1_MultiplexExample2.raw.CAN1sig_ExSignal8.sig = CAN1sig_ExSignal8.raw;
    CAN1sig_ExSignal8.sent = true;

    if(CAN1sig_ExSignal8.raw == 0){
    CAN1_MultiplexExample2.raw.CAN1sig_ExSignal9.sig = CAN1sig_ExSignal9.raw;
    CAN1sig_ExSignal9.sent = true;
    }
    }
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_MultiplexExample2.raw.bytes,
        CAN1_MultiplexExample2.DLC,
        CAN1_MultiplexExample2.ID,
        CAN1_MultiplexExample2.is_extended
    );
};

static void CAN1_MultiplexExample_receive(){

    portENTER_CRITICAL();
    CAN1sig_EXSignal1.raw = CAN1_MultiplexExample.raw.CAN1sig_EXSignal1.sig;

    if(CAN1sig_EXSignal1.raw == 4){
    CAN1sig_EXSignal2.raw = CAN1_MultiplexExample.raw.CAN1sig_EXSignal2.sig;

    if(CAN1sig_EXSignal2.raw == 0){
    CAN1sig_EXSignal4.raw = CAN1_MultiplexExample.raw.CAN1sig_EXSignal4.sig;
    }
    CAN1sig_EXSignal3.raw = CAN1_MultiplexExample.raw.CAN1sig_EXSignal3.sig;
    }
    portEXIT_CRITICAL();

    if(CAN1_MultiplexExample.on_receive != NULL){CAN1_MultiplexExample.on_receive();}
    
};
static void CAN1_Ignition_Info_receive(){

    portENTER_CRITICAL();
    CAN1sig_StarterKey.raw = reverseBits(CAN1_Ignition_Info.raw.CAN1sig_StarterKey.sig, CAN1sig_StarterKey.length);
    portEXIT_CRITICAL();

    if(CAN1_Ignition_Info.on_receive != NULL){CAN1_Ignition_Info.on_receive();}
    
};
static void CAN1_NM_Engine_send(){
    portENTER_CRITICAL();
    memset (CAN1_NM_Engine.raw.bytes,0,sizeof CAN1_NM_Engine.raw.bytes);
    CAN1_NM_Engine.raw.CAN1sig_SleepInd.sig = CAN1sig_SleepInd.raw;
    CAN1sig_SleepInd.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_NM_Engine.raw.bytes,
        CAN1_NM_Engine.DLC,
        CAN1_NM_Engine.ID,
        CAN1_NM_Engine.is_extended
    );
};

static void CAN1_GearBoxInfo_send(){
    portENTER_CRITICAL();
    memset (CAN1_GearBoxInfo.raw.bytes,0,sizeof CAN1_GearBoxInfo.raw.bytes);
    CAN1_GearBoxInfo.raw.CAN1sig_GearLock.sig = CAN1sig_GearLock.raw;
    CAN1sig_GearLock.sent = true;
    CAN1_GearBoxInfo.raw.CAN1sig_ShiftRequest.sig = CAN1sig_ShiftRequest.raw;
    CAN1sig_ShiftRequest.sent = true;
    CAN1_GearBoxInfo.raw.CAN1sig_Gear.sig = reverseBits(CAN1sig_Gear.raw,  CAN1sig_Gear.length);
    CAN1sig_Gear.sent = true;
    CAN1_GearBoxInfo.raw.CAN1sig_EcoMode.sig = CAN1sig_EcoMode.raw;
    CAN1sig_EcoMode.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_GearBoxInfo.raw.bytes,
        CAN1_GearBoxInfo.DLC,
        CAN1_GearBoxInfo.ID,
        CAN1_GearBoxInfo.is_extended
    );
};

static void CAN1_EngineStatus_send(){
    portENTER_CRITICAL();
    memset (CAN1_EngineStatus.raw.bytes,0,sizeof CAN1_EngineStatus.raw.bytes);
    CAN1_EngineStatus.raw.CAN1sig_Status.sig = CAN1sig_Status.raw;
    CAN1sig_Status.sent = true;
    CAN1_EngineStatus.raw.CAN1sig_ErrorCode.sig = CAN1sig_ErrorCode.raw;
    CAN1sig_ErrorCode.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_EngineStatus.raw.bytes,
        CAN1_EngineStatus.DLC,
        CAN1_EngineStatus.ID,
        CAN1_EngineStatus.is_extended
    );
};

static void CAN1_EngineData_send(){
    portENTER_CRITICAL();
    memset (CAN1_EngineData.raw.bytes,0,sizeof CAN1_EngineData.raw.bytes);
    CAN1_EngineData.raw.CAN1sig_EngSpeed.sig = CAN1sig_EngSpeed.raw;
    CAN1sig_EngSpeed.sent = true;
    CAN1_EngineData.raw.CAN1sig_EngTemp.sig = CAN1sig_EngTemp.raw;
    CAN1sig_EngTemp.sent = true;
    CAN1_EngineData.raw.CAN1sig_IdleRunning.sig = CAN1sig_IdleRunning.raw;
    CAN1sig_IdleRunning.sent = true;
    CAN1_EngineData.raw.CAN1sig_PetrolLevel.sig = CAN1sig_PetrolLevel.raw;
    CAN1sig_PetrolLevel.sent = true;
    CAN1_EngineData.raw.CAN1sig_EngForce.sig = CAN1sig_EngForce.raw;
    CAN1sig_EngForce.sent = true;
    CAN1_EngineData.raw.CAN1sig_EngPower.sig = CAN1sig_EngPower.raw;
    CAN1sig_EngPower.sent = true;
    portEXIT_CRITICAL();

    CAN1_SendCallback(
        CAN1_EngineData.raw.bytes,
        CAN1_EngineData.DLC,
        CAN1_EngineData.ID,
        CAN1_EngineData.is_extended
    );
};

/*
 * Messages: Message structs definitions
 */



// Comment: None
struct CAN1_FloatExample4_t CAN1_FloatExample4 = {
    .ID = 0xb1, //dec: 177
    .is_extended = false,
    .DLC = 8,
    .receive = CAN1_FloatExample4_receive,
    .on_receive = NULL,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_FloatExample3_t CAN1_FloatExample3 = {
    .ID = 0x132, //dec: 306
    .is_extended = false,
    .DLC = 8,
    .receive = CAN1_FloatExample3_receive,
    .on_receive = NULL,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_FloatExample2_t CAN1_FloatExample2 = {
    .ID = 0x123, //dec: 291
    .is_extended = false,
    .DLC = 8,
    .send = CAN1_FloatExample2_send,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_FloatExample_t CAN1_FloatExample = {
    .ID = 0xc01fefe, //dec: 201457406
    .is_extended = true,
    .DLC = 8,
    .send = CAN1_FloatExample_send,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_ABSdata_t CAN1_ABSdata = {
    .ID = 0xc9, //dec: 201
    .is_extended = false,
    .DLC = 6,
    .send = CAN1_ABSdata_send,
    .repetitions = 3,
    .repetitionsleft = 0,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_MultiplexExample2_t CAN1_MultiplexExample2 = {
    .ID = 0x301, //dec: 769
    .is_extended = false,
    .DLC = 8,
    .send = CAN1_MultiplexExample2_send,
    .repetitions = 5,
    .repetitionsleft = 0,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_MultiplexExample_t CAN1_MultiplexExample = {
    .ID = 0x300, //dec: 768
    .is_extended = false,
    .DLC = 8,
    .receive = CAN1_MultiplexExample_receive,
    .on_receive = NULL,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_Ignition_Info_t CAN1_Ignition_Info = {
    .ID = 0x67, //dec: 103
    .is_extended = false,
    .DLC = 2,
    .receive = CAN1_Ignition_Info_receive,
    .on_receive = NULL,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_NM_Engine_t CAN1_NM_Engine = {
    .ID = 0x51b, //dec: 1307
    .is_extended = false,
    .DLC = 4,
    .send = CAN1_NM_Engine_send,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_GearBoxInfo_t CAN1_GearBoxInfo = {
    .ID = 0x3fc, //dec: 1020
    .is_extended = false,
    .DLC = 1,
    .send = CAN1_GearBoxInfo_send,
    .repetitions = 3,
    .repetitionsleft = 0,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_EngineStatus_t CAN1_EngineStatus = {
    .ID = 0x65, //dec: 101
    .is_extended = false,
    .DLC = 1,
    .send = CAN1_EngineStatus_send,
    .repetitions = 10,
    .repetitionsleft = 0,
    .raw = {
        .bytes = {0}
    },
};
// Comment: None
struct CAN1_EngineData_t CAN1_EngineData = {
    .ID = 0x64, //dec: 100
    .is_extended = false,
    .DLC = 8,
    .send = CAN1_EngineData_send,
    .repetitions = 10,
    .repetitionsleft = 0,
    .raw = {
        .bytes = {0}
    },
};

