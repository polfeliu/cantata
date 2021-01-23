#include "DatabaseLayer.h"

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


struct CAN1sig_DoubleExample_t CAN1sig_DoubleExample = {
    .length = 64,
    .byte_order = little_endian,
    .value_type = Tdouble,
    .unit = "",
    .initial_value = 0,
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
    .byte_order = little_endian,
    .value_type = Tsingle,
    .unit = "",
    .initial_value = 0,
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
    .initial_value = 0,
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
    .initial_value = 0,
    .factor = 0.5,
    .offset = 0,
    .min = 0.0,
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
    .initial_value = 0,
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
    .initial_value = 0,
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
    .initial_value = 0,
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
    .initial_value = 0,
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
    .initial_value = 0,
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
    .initial_value = 0,
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
    .setRaw = CAN1sig_SleepInd_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_ShiftRequest_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_Gear_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_EcoMode_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_Status_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_ErrorCode_setRaw,
    .sent = true,
    .inactiveValue = 0,
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
    .setRaw = CAN1sig_EngSpeed_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_EngTemp_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_IdleRunning_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_PetrolLevel_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_EngForce_setRaw,
    .sent = true
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
    .setRaw = CAN1sig_EngPower_setRaw,
    .sent = true
};
    

/*
 * Signals: Signal getValue and setValue private methods
 */


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
}

/*
 * Messages:  send and receive private methods
 */


static void CAN1_FloatExample2_send(){
    CAN1_FloatExample2.raw = 0;

    CAN1_FloatExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_DoubleExample.raw & CAN1_FloatExample2.signals.CAN1sig_DoubleExample.mask) << CAN1_FloatExample2.signals.CAN1sig_DoubleExample.startbit;
    CAN1sig_DoubleExample.sent = true;

    CAN1_SendCallback(
        CAN1_FloatExample2.raw,
        CAN1_FloatExample2.ID,
        CAN1_FloatExample2.is_extended,
        CAN1_FloatExample2.DLC
    );
};

static void CAN1_FloatExample_send(){
    CAN1_FloatExample.raw = 0;

    CAN1_FloatExample.raw |= (uint64_t) ((uint64_t) CAN1sig_SingleExample.raw & CAN1_FloatExample.signals.CAN1sig_SingleExample.mask) << CAN1_FloatExample.signals.CAN1sig_SingleExample.startbit;
    CAN1sig_SingleExample.sent = true;
    CAN1_FloatExample.raw |= (uint64_t) ((uint64_t) reverseBits(CAN1sig_SingleExample2.raw,  CAN1sig_SingleExample2.length) & CAN1_FloatExample.signals.CAN1sig_SingleExample2.mask) << CAN1_FloatExample.signals.CAN1sig_SingleExample2.startbit;
    CAN1sig_SingleExample2.sent = true;

    CAN1_SendCallback(
        CAN1_FloatExample.raw,
        CAN1_FloatExample.ID,
        CAN1_FloatExample.is_extended,
        CAN1_FloatExample.DLC
    );
};

static void CAN1_ABSdata_send(){
    CAN1_ABSdata.raw = 0;

    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_CarSpeed.raw & CAN1_ABSdata.signals.CAN1sig_CarSpeed.mask) << CAN1_ABSdata.signals.CAN1sig_CarSpeed.startbit;
    CAN1sig_CarSpeed.sent = true;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_GearLock.raw & CAN1_ABSdata.signals.CAN1sig_GearLock.mask) << CAN1_ABSdata.signals.CAN1sig_GearLock.startbit;
    CAN1sig_GearLock.sent = true;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_Diagnostics.raw & CAN1_ABSdata.signals.CAN1sig_Diagnostics.mask) << CAN1_ABSdata.signals.CAN1sig_Diagnostics.startbit;
    CAN1sig_Diagnostics.sent = true;
    CAN1_ABSdata.raw |= (uint64_t) ((uint64_t) CAN1sig_AccelerationForce.raw & CAN1_ABSdata.signals.CAN1sig_AccelerationForce.mask) << CAN1_ABSdata.signals.CAN1sig_AccelerationForce.startbit;
    CAN1sig_AccelerationForce.sent = true;

    CAN1_SendCallback(
        CAN1_ABSdata.raw,
        CAN1_ABSdata.ID,
        CAN1_ABSdata.is_extended,
        CAN1_ABSdata.DLC
    );
};

static void CAN1_MultiplexExample2_send(){
    CAN1_MultiplexExample2.raw = 0;

    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal7.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal7.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal7.startbit;
    CAN1sig_ExSignal7.sent = true;

    if(CAN1sig_ExSignal7.raw == 0){
    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal8.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal8.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal8.startbit;
    CAN1sig_ExSignal8.sent = true;

    if(CAN1sig_ExSignal8.raw == 0){
    CAN1_MultiplexExample2.raw |= (uint64_t) ((uint64_t) CAN1sig_ExSignal9.raw & CAN1_MultiplexExample2.signals.CAN1sig_ExSignal9.mask) << CAN1_MultiplexExample2.signals.CAN1sig_ExSignal9.startbit;
    CAN1sig_ExSignal9.sent = true;
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
static void CAN1_NM_Engine_send(){
    CAN1_NM_Engine.raw = 0;

    CAN1_NM_Engine.raw |= (uint64_t) ((uint64_t) CAN1sig_SleepInd.raw & CAN1_NM_Engine.signals.CAN1sig_SleepInd.mask) << CAN1_NM_Engine.signals.CAN1sig_SleepInd.startbit;
    CAN1sig_SleepInd.sent = true;

    CAN1_SendCallback(
        CAN1_NM_Engine.raw,
        CAN1_NM_Engine.ID,
        CAN1_NM_Engine.is_extended,
        CAN1_NM_Engine.DLC
    );
};

static void CAN1_GearBoxInfo_send(){
    CAN1_GearBoxInfo.raw = 0;

    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) CAN1sig_GearLock.raw & CAN1_GearBoxInfo.signals.CAN1sig_GearLock.mask) << CAN1_GearBoxInfo.signals.CAN1sig_GearLock.startbit;
    CAN1sig_GearLock.sent = true;
    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) CAN1sig_ShiftRequest.raw & CAN1_GearBoxInfo.signals.CAN1sig_ShiftRequest.mask) << CAN1_GearBoxInfo.signals.CAN1sig_ShiftRequest.startbit;
    CAN1sig_ShiftRequest.sent = true;
    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) reverseBits(CAN1sig_Gear.raw,  CAN1sig_Gear.length) & CAN1_GearBoxInfo.signals.CAN1sig_Gear.mask) << CAN1_GearBoxInfo.signals.CAN1sig_Gear.startbit;
    CAN1sig_Gear.sent = true;
    CAN1_GearBoxInfo.raw |= (uint64_t) ((uint64_t) CAN1sig_EcoMode.raw & CAN1_GearBoxInfo.signals.CAN1sig_EcoMode.mask) << CAN1_GearBoxInfo.signals.CAN1sig_EcoMode.startbit;
    CAN1sig_EcoMode.sent = true;

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
    CAN1sig_Status.sent = true;
    CAN1_EngineStatus.raw |= (uint64_t) ((uint64_t) CAN1sig_ErrorCode.raw & CAN1_EngineStatus.signals.CAN1sig_ErrorCode.mask) << CAN1_EngineStatus.signals.CAN1sig_ErrorCode.startbit;
    CAN1sig_ErrorCode.sent = true;

    CAN1_SendCallback(
        CAN1_EngineStatus.raw,
        CAN1_EngineStatus.ID,
        CAN1_EngineStatus.is_extended,
        CAN1_EngineStatus.DLC
    );
};

static void CAN1_EngineData_send(){
    CAN1_EngineData.raw = 0;

    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngSpeed.raw & CAN1_EngineData.signals.CAN1sig_EngSpeed.mask) << CAN1_EngineData.signals.CAN1sig_EngSpeed.startbit;
    CAN1sig_EngSpeed.sent = true;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngTemp.raw & CAN1_EngineData.signals.CAN1sig_EngTemp.mask) << CAN1_EngineData.signals.CAN1sig_EngTemp.startbit;
    CAN1sig_EngTemp.sent = true;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_IdleRunning.raw & CAN1_EngineData.signals.CAN1sig_IdleRunning.mask) << CAN1_EngineData.signals.CAN1sig_IdleRunning.startbit;
    CAN1sig_IdleRunning.sent = true;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_PetrolLevel.raw & CAN1_EngineData.signals.CAN1sig_PetrolLevel.mask) << CAN1_EngineData.signals.CAN1sig_PetrolLevel.startbit;
    CAN1sig_PetrolLevel.sent = true;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngForce.raw & CAN1_EngineData.signals.CAN1sig_EngForce.mask) << CAN1_EngineData.signals.CAN1sig_EngForce.startbit;
    CAN1sig_EngForce.sent = true;
    CAN1_EngineData.raw |= (uint64_t) ((uint64_t) CAN1sig_EngPower.raw & CAN1_EngineData.signals.CAN1sig_EngPower.mask) << CAN1_EngineData.signals.CAN1sig_EngPower.startbit;
    CAN1sig_EngPower.sent = true;

    CAN1_SendCallback(
        CAN1_EngineData.raw,
        CAN1_EngineData.ID,
        CAN1_EngineData.is_extended,
        CAN1_EngineData.DLC
    );
};

/*
 * Messages: Message struct definitions
 */



// Comment: None
struct CAN1_FloatExample2_t CAN1_FloatExample2 = {
    .ID = 0x123, //dec: 291
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_FloatExample2_send,
    .signals = {
        .CAN1sig_DoubleExample = {
            .signal = &CAN1sig_DoubleExample,
            .startbit = 0,
            .mask = 0b1111111111111111111111111111111111111111111111111111111111111111
        },
        
    }
};
// Comment: None
struct CAN1_FloatExample_t CAN1_FloatExample = {
    .ID = 0xc01fefe, //dec: 201457406
    .is_extended = true,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_FloatExample_send,
    .signals = {
        .CAN1sig_SingleExample = {
            .signal = &CAN1sig_SingleExample,
            .startbit = 0,
            .mask = 0b11111111111111111111111111111111
        },
        
        .CAN1sig_SingleExample2 = {
            .signal = &CAN1sig_SingleExample2,
            .startbit = 8,
            .mask = 0b11111111111111111111111111111111
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
    .repetitions = 3,
    .repetitionsleft = 0,
    .signals = {
        .CAN1sig_CarSpeed = {
            .signal = &CAN1sig_CarSpeed,
            .startbit = 0,
            .mask = 0b1111111111
        },
        
        .CAN1sig_GearLock = {
            .signal = &CAN1sig_GearLock,
            .startbit = 10,
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
// Comment: None
struct CAN1_MultiplexExample2_t CAN1_MultiplexExample2 = {
    .ID = 0x301, //dec: 769
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_MultiplexExample2_send,
    .repetitions = 5,
    .repetitionsleft = 0,
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
    .repetitions = 3,
    .repetitionsleft = 0,
    .signals = {
        .CAN1sig_GearLock = {
            .signal = &CAN1sig_GearLock,
            .startbit = 4,
            .mask = 0b1
        },
        
        .CAN1sig_ShiftRequest = {
            .signal = &CAN1sig_ShiftRequest,
            .startbit = 5,
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
    .repetitions = 10,
    .repetitionsleft = 0,
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
struct CAN1_EngineData_t CAN1_EngineData = {
    .ID = 0x64, //dec: 100
    .is_extended = false,
    .DLC = 8,
    .raw = 0,
    .send = CAN1_EngineData_send,
    .repetitions = 10,
    .repetitionsleft = 0,
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

