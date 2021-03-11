#ifndef __STM32CANCallbacks_H
#define __STM32CANCallbacks_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stdbool.h"

#define vTaskInteractionLayer_CAN1_EngineStatus_Stack_Depth 800
#define vTaskInteractionLayer_CAN1_EngineData_Stack_Depth 600
#define vTaskInteractionLayer_CAN1_EngineData_fastDelayedResume_Stack_Depth 600
#define vTaskInteractionLayer_CAN1_OnWriteOnChange_Stack_Depth 600


void CAN1_SendCallback(uint8_t data[], uint8_t DLC, uint32_t ID, bool is_extended /*, bool FDF, bool BRS*/);
void InitCAN1(CAN_HandleTypeDef *canh);

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */
