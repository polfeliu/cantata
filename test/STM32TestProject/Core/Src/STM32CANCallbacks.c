#include "STM32CANCallbacks.h"
#include "cantata.h"
#include "stdbool.h"

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

CAN_HandleTypeDef CANHandle;

void InitCAN1(CAN_HandleTypeDef *canh){
	CANHandle = *canh;

	CAN_FilterTypeDef sFilterConfig;

    sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterIdHigh     = ((int32_t)CAN1_StandardFilter  << 5) + ((int32_t) CAN1_ExtendedFilter >> 13);
	sFilterConfig.FilterMaskIdHigh = ((int32_t) CAN1_StandardMask   << 5) + ((int32_t) CAN1_ExtendedMask   >> 13);
	sFilterConfig.FilterIdLow 	   = ((int32_t) CAN1_ExtendedFilter << 3);
	sFilterConfig.FilterMaskIdLow  = ((int32_t) CAN1_ExtendedFilter << 3);

	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterFIFOAssignment = 0;

	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if(HAL_CAN_ConfigFilter(&CANHandle, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_CAN_Start(&CANHandle)){
	  Error_Handler();
  	}

  	if(HAL_CAN_ActivateNotification(&CANHandle, CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
  	{
	  Error_Handler();
  	}

  	CAN1_InteractionLayerStart();

  	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}


static CAN_TxHeaderTypeDef TxHeader = {
		.StdId= 0,
		.RTR = CAN_RTR_DATA,
		.IDE = CAN_ID_STD,
		.DLC = 1,
		.TransmitGlobalTime = DISABLE
};

static uint8_t TxData[8];
static uint32_t  pTxMailbox;

void CAN1_SendCallback(uint64_t data, uint32_t ID, bool is_extended, uint8_t DLC){

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	if(is_extended){
		TxHeader.IDE = CAN_ID_EXT;
		TxHeader.ExtId = ID;
	}else{
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.StdId = ID;
	}

	TxHeader.DLC = DLC;

	for(int i=0; i<8; i++){
		TxData[i] = (uint8_t) data & 0xFF;
		data = data >> 8;
	}

	while(HAL_CAN_GetTxMailboxesFreeLevel(&CANHandle) == 0){//wait for a free mailbox
		HAL_Delay(1);
	}

	HAL_CAN_AddTxMessage(
			&CANHandle,
			&TxHeader,
			TxData,
			&pTxMailbox
		);

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

}

static CAN_RxHeaderTypeDef RxHeader = {
		.StdId= 0,
		.RTR = CAN_RTR_DATA,
		.IDE = CAN_ID_STD,
		.DLC = 1,
};

static uint8_t RxData[8];

static uint64_t data;
static uint32_t ID;
static bool is_extended;
static uint8_t DLC;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef*hcan){
	if(hcan->Instance == CAN1){
		HAL_CAN_GetRxMessage(
				&CANHandle,
				CAN_RX_FIFO0,
				&RxHeader,
				RxData
			);

		data = 0;

		for(int i=0; i<8; i++){
			data |= RxData[i] << 8*i;
		}

		if(RxHeader.IDE == CAN_ID_EXT){
			is_extended = true;
			ID = RxHeader.ExtId;
		}else{
			is_extended = false;
			ID = RxHeader.StdId;
		}

		CAN1_ReceiveCallback(data, ID, is_extended, DLC);
	}

}
