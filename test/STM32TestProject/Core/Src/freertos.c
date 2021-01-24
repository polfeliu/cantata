/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DatabaseLayer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for aux */
osThreadId_t auxHandle;
const osThreadAttr_t aux_attributes = {
  .name = "aux",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void auxTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of aux */
  auxHandle = osThreadNew(auxTask, NULL, &aux_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */


enum{
	Cyclic,
	OnWrite,
	OnWriteWithRepetitions,
	OnChange,
	OnChangeWithRepetitions,
	IfActive,
	IfActiveWithRepetitions,
	TransmitTesting,
	ReceiveTesting
} InteractionLayerDemo;


extern TaskHandle_t vTaskInteractionLayer_CAN1_cyclic_1000ms_Handle;

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	GPIO_PinState button_last;
	GPIO_PinState button = button = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);;
	bool error = false;
	uint64_t expectedmsg;

	InteractionLayerDemo = TransmitTesting; // Change to try the different modes

	if(InteractionLayerDemo != Cyclic){
		// for simplicity lets disable the cyclic task
		vTaskSuspend(vTaskInteractionLayer_CAN1_cyclic_1000ms_Handle);
	}
  /* Infinite loop */
  for(;;)
  {
    vTaskDelay(pdMS_TO_TICKS(50));

    button_last = button;
    button = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

    switch (InteractionLayerDemo) {
		case OnWrite:
			if(button != button_last){
				CAN1sig_EngSpeed.setValue(1);
			}
			break;
		case OnWriteWithRepetitions:
			if(button != button_last){
				CAN1sig_EngTemp.setValue(1);
			}
			break;
		case OnChange:
			CAN1sig_IdleRunning.setValue(button);
			break;
		case OnChangeWithRepetitions:
			CAN1sig_AccelerationForce.setValue(button);
			break;
		case IfActive:
			if(button){
				CAN1sig_ExSignal9.setValue(CAN1sig_ExSignal9.inactiveValue);
			}else{
				CAN1sig_ExSignal9.setValue(1);
			}
			break;
		case IfActiveWithRepetitions:
			if(button){
				CAN1sig_ErrorCode.setValue(CAN1sig_ExSignal9.inactiveValue);
			}else{
				CAN1sig_ErrorCode.setValue(1);
			}
			break;

		case TransmitTesting:
			error = false;

			//// ABSData
			CAN1sig_AccelerationForce.setValue(48009);
			CAN1sig_Diagnostics.setValue(138);
			CAN1sig_GearLock.setValue(0);
			CAN1sig_CarSpeed.setValue(115);

			expectedmsg = 0x0000e299008a00e6;
			CAN1_ABSdata.send();
			error |= (CAN1_ABSdata.raw != expectedmsg);


			CAN1sig_AccelerationForce.setValue(-4215);
			CAN1sig_Diagnostics.setValue(167);
			CAN1sig_GearLock.setValue(1);
			CAN1sig_CarSpeed.setValue(239);

			expectedmsg = 0x0000169900a705de;
			CAN1_ABSdata.send();
			error |= (CAN1_ABSdata.raw != expectedmsg);

			//// EngineData
			CAN1sig_EngSpeed.setValue(57288);
			CAN1sig_EngTemp.setValue(-13);
			CAN1sig_IdleRunning.setValue(0);
			CAN1sig_EngForce.setValue(12898);
			CAN1sig_EngPower.setValue(216);
			CAN1sig_PetrolLevel.setValue(217);

			expectedmsg = 0x54603262d912dfc8;
			CAN1_EngineData.send();
			error |= (CAN1_EngineData.raw != expectedmsg);

			CAN1sig_EngSpeed.setValue(31189);
			CAN1sig_EngTemp.setValue(27);
			CAN1sig_IdleRunning.setValue(1);
			CAN1sig_EngForce.setValue(42039);
			CAN1sig_EngPower.setValue(375);
			CAN1sig_PetrolLevel.setValue(56);

			expectedmsg = 0x927ca43738a679d5;
			CAN1_EngineData.send();
			error |= (CAN1_EngineData.raw != expectedmsg);

			//// EngineStatus
			CAN1sig_Status.setValue(2);
			CAN1sig_ErrorCode.setValue(32);

			expectedmsg = 0x0000000000000082;
			CAN1_EngineStatus.send();
			error |= (CAN1_EngineStatus.raw != expectedmsg);

			CAN1sig_Status.setValue(0);
			CAN1sig_ErrorCode.setValue(29);

			expectedmsg = 0x0000000000000074;
			CAN1_EngineStatus.send();
			error |= (CAN1_EngineStatus.raw != expectedmsg);


			//// GearboxInfo
			CAN1sig_Gear.setValue(6);
			CAN1sig_ShiftRequest.setValue(0);
			CAN1sig_EcoMode.setValue(1);
			CAN1sig_GearLock.setValue(0);

			expectedmsg = 0x0000000000000043;
			CAN1_GearBoxInfo.send();
			error |= (CAN1_GearBoxInfo.raw != expectedmsg);

			CAN1sig_Gear.setValue(1);
			CAN1sig_ShiftRequest.setValue(0);
			CAN1sig_EcoMode.setValue(1);
			CAN1sig_GearLock.setValue(0);

			expectedmsg = 0x0000000000000044;
			CAN1_GearBoxInfo.send();
			error |= (CAN1_GearBoxInfo.raw != expectedmsg);

			CAN1sig_Gear.setValue(3);
			CAN1sig_ShiftRequest.setValue(0);
			CAN1sig_EcoMode.setValue(1);
			CAN1sig_GearLock.setValue(0);

			expectedmsg = 0x0000000000000046;
			CAN1_GearBoxInfo.send();
			error |= (CAN1_GearBoxInfo.raw != expectedmsg);

			CAN1sig_Gear.setValue(3);
			CAN1sig_ShiftRequest.setValue(1);
			CAN1sig_EcoMode.setValue(0);
			CAN1sig_GearLock.setValue(1);

			expectedmsg = 0x0000000000000036;
			CAN1_GearBoxInfo.send();
			error |= (CAN1_GearBoxInfo.raw != expectedmsg);


			//// MultiplexExample2
			CAN1sig_ExSignal7.setValue(0);
			CAN1sig_ExSignal8.setValue(0);
			CAN1sig_ExSignal9.setValue(37);

			expectedmsg = 0x0000000000250000;
			CAN1_MultiplexExample2.send();
			error |= (CAN1_MultiplexExample2.raw != expectedmsg);

			CAN1sig_ExSignal7.setValue(1);
			CAN1sig_ExSignal8.setValue(0);
			CAN1sig_ExSignal9.setValue(0);

			expectedmsg = 0x0000000000000001;
			CAN1_MultiplexExample2.send();
			error |= (CAN1_MultiplexExample2.raw != expectedmsg);

			//// NM_Engine
			CAN1sig_SleepInd.setValue(0);

			expectedmsg = 0x0000000000000000;
			CAN1_NM_Engine.send();
			error |= (CAN1_NM_Engine.raw != expectedmsg);


			CAN1sig_SleepInd.setValue(1);

			expectedmsg = 0x0000000000001000;
			CAN1_NM_Engine.send();
			error |= (CAN1_NM_Engine.raw != expectedmsg);

			//// FloatExample

			CAN1sig_SingleExample.setValue(-2.138737678527832);
			CAN1sig_SingleExample2.setValue(-8.984071263822772e-28);

			float qwer = 1234.5;
			uint32_t asdf;
			asdf = (uint32_t) CAN1sig_SingleExample.raw;
		    //asdf = (uint32_t) ((uint64_t) CAN1sig_SingleExample.raw & CAN1_FloatExample.signals.CAN1sig_SingleExample.mask) << CAN1_FloatExample.signals.CAN1sig_SingleExample.startbit;



			expectedmsg = 0xb95b8e92c008e114;
			CAN1_FloatExample.send();
			error |= (CAN1_FloatExample.raw != expectedmsg);

			//// FloatExample2

			CAN1sig_DoubleExample.setValue(1.22832399570192E+85);
			CAN1_FloatExample2.send();
			error |= (CAN1_FloatExample2.raw != expectedmsg);


			break;

		case ReceiveTesting:
			error = false;


			//// Ignition_Info
			CAN1_Ignition_Info.raw = 0x0000000000001784;
			CAN1_Ignition_Info.receive();

			error |= (CAN1sig_StarterKey.getValue() != 1);

			CAN1_Ignition_Info.raw = 0x0000000000009d31;
			CAN1_Ignition_Info.receive();

			error |= (CAN1sig_StarterKey.getValue() != 0);


			//// MultiplexExample
			CAN1_MultiplexExample.raw = 0xe797a6e9c062d900;
			CAN1_MultiplexExample.receive();

			error |= (CAN1sig_EXSignal1.getValue() != 0);
			//error |= (CAN1sig_EXSignal5.getValue() != -23); Signal not declared as RX

			CAN1_MultiplexExample.raw = 0xb1e1e4eb60af8201;
			CAN1_MultiplexExample.receive();

			error |= (CAN1sig_EXSignal1.getValue() != 1);

			CAN1_MultiplexExample.raw = 0x7e0868676c2b0004;
			CAN1_MultiplexExample.receive();

			error |= (CAN1sig_EXSignal1.getValue() != 4);
			error |= (CAN1sig_EXSignal2.getValue() != 0);
			error |= (CAN1sig_EXSignal3.getValue() != 43);
			error |= (CAN1sig_EXSignal4.getValue() != 108);
			//error |= (CAN1sig_EXSignal6.getValue() != 104); Signal not declared as RX

			CAN1_MultiplexExample.raw = 0xe74aa821e19e0104;
			CAN1_MultiplexExample.receive();

			error |= (CAN1sig_EXSignal1.getValue() != 4);
			error |= (CAN1sig_EXSignal2.getValue() != 1);
			error |= (CAN1sig_EXSignal3.getValue() != -98);

			break;
		default:
			break;

	}

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_auxTask */
/**
* @brief Function implementing the aux thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_auxTask */
void auxTask(void *argument)
{
  /* USER CODE BEGIN auxTask */
  /* Infinite loop */
  for(;;)
  {
	  xTaskNotifyWait( 0,     //ulBitsToClearOnEntry
			  	  	  	  0,     //ulBitsToClearOnExit
	                           NULL,  //*pulNotificationValue
	                           portMAX_DELAY );
	  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  }
  /* USER CODE END auxTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
