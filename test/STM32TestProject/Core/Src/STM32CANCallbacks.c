#include "STM32CANCallbacks.h"
#include "cantataCAN1.h"
#include "stdbool.h"

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "queue.h"

CAN_HandleTypeDef CANHandle;

static void CAN_Receive(void *pvParameters);
TaskHandle_t CAN_Receive_Handle = NULL;

void InitCAN1(CAN_HandleTypeDef *canh){
	CANHandle = *canh;

	CAN_FilterTypeDef sFilterConfig;

	// Common Filter Parameters
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;

	// Config Standard Filter
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterIdHigh = CAN1_StandardFilter << 5;
	sFilterConfig.FilterMaskIdHigh = CAN1_StandardMask << 5;
	sFilterConfig.FilterIdLow = 0 << 2; //IDE (Standard)
	sFilterConfig.FilterMaskIdLow = 1 << 2; //IDE

	if(HAL_CAN_ConfigFilter(&CANHandle, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	// Config Extended Filter
    sFilterConfig.FilterBank = 1;
    sFilterConfig.FilterIdHigh = CAN1_ExtendedFilter >> 13;
	sFilterConfig.FilterMaskIdHigh = CAN1_ExtendedMask >> 13;
	sFilterConfig.FilterIdLow = (CAN1_ExtendedFilter << 3) |  (1 << 2); //IDE (Extended);
	sFilterConfig.FilterMaskIdLow = (CAN1_ExtendedMask << 3) | (1 << 2); //IDE;

	if(HAL_CAN_ConfigFilter(&CANHandle, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_CAN_Start(&CANHandle)){
	  Error_Handler();
  	}

  	xTaskCreate( //Create Deferred Interrupt Processing Task
		CAN_Receive,
		"CAN_Receive_Handle",
		100,
		NULL,
		tskIDLE_PRIORITY,
		&CAN_Receive_Handle
	);

  	if(HAL_CAN_ActivateNotification(&CANHandle, CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
  	{
	  Error_Handler();
  	}

  	CAN1_InteractionLayerStart();

}


static CAN_TxHeaderTypeDef TxHeader = {
		.StdId= 0,
		.RTR = CAN_RTR_DATA,
		.IDE = CAN_ID_STD,
		.DLC = 1,
		.TransmitGlobalTime = DISABLE
};

static uint32_t  pTxMailbox;

void CAN1_SendCallback(uint8_t data[], uint8_t DLC, uint32_t ID, bool is_extended /*, bool FDF, bool BRS*/){

	if(is_extended){
		TxHeader.IDE = CAN_ID_EXT;
		TxHeader.ExtId = ID;
	}else{
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.StdId = ID;
	}

	TxHeader.DLC = DLC;

	while(HAL_CAN_GetTxMailboxesFreeLevel(&CANHandle) == 0){//wait for a free mailbox
		//HAL_Delay(1); If not using FreeRTOS
		vTaskDelay(1); // Wait 1 tick (minimum possible)
	}

	HAL_CAN_AddTxMessage(
			&CANHandle,
			&TxHeader,
			data,
			&pTxMailbox
		);

}


typedef struct CAN_msg_s {
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t data[8];
}CAN_msg_t;

static QueueHandle_t xCANRXQueue;

static void CAN_Receive(void *pvParameters){
	CAN_msg_t msg;
	uint16_t ID;
	bool is_extended;

	xCANRXQueue = xQueueCreate(20,sizeof( CAN_msg_t ) ); 

	for(;;){
		if(xQueueReceive(xCANRXQueue, &msg, portMAX_DELAY) == pdPASS){

			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

			if (msg.RxHeader.IDE == CAN_ID_EXT) {
				is_extended = true;
				ID = msg.RxHeader.ExtId;
			} else {
				is_extended = false;
				ID = msg.RxHeader.StdId;
			}

			CAN1_ReceiveCallback(
							msg.data,
							msg.RxHeader.DLC,
							ID,
							is_extended //,
							//false, // FDF
							//false	 // BRS
						);

		}
	}
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef*hcan){
	CAN_msg_t msg;

	if(hcan->Instance == CANHandle.Instance){
		HAL_CAN_GetRxMessage(
				&CANHandle,
				CAN_RX_FIFO0,
				&msg.RxHeader,
				msg.data
			);

		if(xCANRXQueue != NULL){
			xQueueSendFromISR( xCANRXQueue, &msg, NULL);
		}
	}

}
