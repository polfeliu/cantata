#ifndef __STM32CANCallbacks_H
#define __STM32CANCallbacks_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stdbool.h"


void CAN1_SendCallback(uint64_t data, uint32_t ID, bool is_extended, uint8_t DLC);
void InitCAN1(CAN_HandleTypeDef *canh);

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */
