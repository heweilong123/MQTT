/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "dev8266.h"
#include "devMQTT.h"
#include "devBoardLed.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum INITOVER_EventFlag{
  INITOVER_UART_CMD = 1,
  INITOVER_UART_WIFI,
  INITOVER_DEV_WIFI,
  INITOVER_DEV_MQTT
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern uint8_t rx_len_cmd;  
extern uint8_t rx_buffer_cmd[200];

extern uint8_t rx_flag_wifi;
extern uint8_t rx_len_wifi; 
extern uint8_t rx_buffer_wifi[1024];
extern uint8_t rx_data_wifi[1024];
extern DMA_HandleTypeDef hdma_usart3_rx;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for usart1Task */
osThreadId_t usart1TaskHandle;
const osThreadAttr_t usart1Task_attributes = {
  .name = "usart1Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
/* Definitions for wifiTask */
osThreadId_t wifiTaskHandle;
const osThreadAttr_t wifiTask_attributes = {
  .name = "wifiTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal5,
};
/* Definitions for usart3task */
osThreadId_t usart3taskHandle;
const osThreadAttr_t usart3task_attributes = {
  .name = "usart3task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal6,
};
/* Definitions for statusTask */
osThreadId_t statusTaskHandle;
const osThreadAttr_t statusTask_attributes = {
  .name = "statusTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for mqttTask */
osThreadId_t mqttTaskHandle;
const osThreadAttr_t mqttTask_attributes = {
  .name = "mqttTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal4,
};
/* Definitions for usart1Event */
osEventFlagsId_t usart1EventHandle;
const osEventFlagsAttr_t usart1Event_attributes = {
  .name = "usart1Event"
};
/* Definitions for initEvent */
osEventFlagsId_t initEventHandle;
const osEventFlagsAttr_t initEvent_attributes = {
  .name = "initEvent"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Usart01Task(void *argument);
void WifiTask(void *argument);
void Usart3Task(void *argument);
void StatusTask(void *argument);
void MqttTask(void *argument);

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

  /* creation of usart1Task */
  usart1TaskHandle = osThreadNew(Usart01Task, NULL, &usart1Task_attributes);

  /* creation of wifiTask */
  wifiTaskHandle = osThreadNew(WifiTask, NULL, &wifiTask_attributes);

  /* creation of usart3task */
  usart3taskHandle = osThreadNew(Usart3Task, NULL, &usart3task_attributes);

  /* creation of statusTask */
  statusTaskHandle = osThreadNew(StatusTask, NULL, &statusTask_attributes);

  /* creation of mqttTask */
  mqttTaskHandle = osThreadNew(MqttTask, NULL, &mqttTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of usart1Event */
  usart1EventHandle = osEventFlagsNew(&usart1Event_attributes);

  /* creation of initEvent */
  initEventHandle = osEventFlagsNew(&initEvent_attributes);

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
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Usart01Task */
/**
* @brief Function implementing the usart1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Usart01Task */
void Usart01Task(void *argument)
{
  /* USER CODE BEGIN Usart01Task */
	MY_CMD_INIT();
	printf("CMD INIT OVER\r\n");
  osEventFlagsSet(initEventHandle, INITOVER_UART_CMD);
  osStatus result = 0;
  /* Infinite loop */
  for(;;)
  {
    result = osEventFlagsWait(usart1EventHandle, USART_FLAG_RECDATA, 
                              osFlagsWaitAny | osFlagsNoClear, 0xffffffff);
    if(result == USART_FLAG_RECDATA)			
		{	
			MY_UART_Transmit(rx_buffer_cmd, rx_len_cmd);
			for(uint8_t i=0;i<rx_len_cmd;i++)
			{
				rx_buffer_cmd[i]=0;
			}
			rx_len_cmd=0;
      osEventFlagsClear(usart1EventHandle, USART_FLAG_RECDATA);
		}
    osDelay(1);
  }
  /* USER CODE END Usart01Task */
}

/* USER CODE BEGIN Header_WifiTask */
/**
* @brief Function implementing the wifiTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_WifiTask */
void WifiTask(void *argument)
{
  /* USER CODE BEGIN WifiTask */

  /* Infinite loop */
  for(;;)
  {
    // wifi must work last uart3 init over;
    while(osEventFlagsWait(initEventHandle, INITOVER_UART_WIFI, osFlagsWaitAny | osFlagsNoClear, 0xffffffff)
       & INITOVER_UART_WIFI  != INITOVER_UART_WIFI)
    {
      osDelay(100);
    }

    Wifi_Reset(1);

    memset(rx_data_wifi, 0x00, sizeof(rx_data_wifi));

    while(Wifi_IsReady() != HAL_OK){
      printf("wait 1...\r\n");
    }
    printf("WIFI ready\r\n");

    while(Wifi_WIFIMODE(3) != HAL_OK){
      printf("wait 2...\r\n");
    }
    printf("WIFI mode ready\r\n");
    
    while(Wifi_JoinWifi("1234", "heweilong") != HAL_OK){
      printf("wait 3...\r\n");
    }
    printf("WIFI JOIN WIFI\r\n");
  
    while(Wifi_ConnectMode(0) != HAL_OK){
      printf("wait 4...\r\n");
    }
    printf("WIFI CONNECT MODE READY\r\n");

    while(Wifi_TCPConnect("183.230.40.39",6002) != HAL_OK){
      printf("wait 5...\r\n");
    }
    printf("WIFI TCP CONNECT SERVER\r\n");

    while(Wifi_TransmissionMode(1) != HAL_OK){
      printf("wait 6...\r\n");
    }
    printf("WIFI TCP Transmission SET OVER\r\n");
    
    printf("WIFI INIT OVER\r\n");

    osEventFlagsSet(initEventHandle, INITOVER_DEV_WIFI);

    while(osEventFlagsGet (initEventHandle) & INITOVER_DEV_WIFI  == INITOVER_DEV_WIFI){
      osDelay(100);
    }

    osDelay(100);
  }
  /* USER CODE END WifiTask */
}

/* USER CODE BEGIN Header_Usart3Task */
/**
* @brief Function implementing the usart3task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Usart3Task */
void Usart3Task(void *argument)
{
  /* USER CODE BEGIN Usart3Task */
  while(osEventFlagsWait(initEventHandle, INITOVER_UART_CMD, osFlagsWaitAny | osFlagsNoClear, 0xffffffff)
      & INITOVER_UART_CMD  != INITOVER_UART_CMD){
    osDelay(100);
  }

  MY_WIFI_INIT();
	printf("UART WIFI INIT OVER\r\n");
  
  osEventFlagsSet(initEventHandle, INITOVER_UART_WIFI);

  static uint32_t lastCount = 0;
  uint32_t curCount  = 0; 
  /* Infinite loop */
  for(;;)
  {
    //process all the receive data and intercept the first group data 
    uint32_t temp  = __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
    curCount = sizeof(rx_buffer_wifi) - temp;

    if((curCount > 1) && (curCount == lastCount)){ //receive data over
      //stop uart rec
      HAL_UART_DMAStop(&huart3);
      
      //save this frame data
      memset(rx_data_wifi, 0x00, strlen((const char *)rx_data_wifi));
      memcpy(rx_data_wifi, rx_buffer_wifi, curCount);
      //save thisi data parameters
      rx_len_wifi = curCount;
      rx_flag_wifi = 1;

      //start uartuart rec
			memset(rx_buffer_wifi, 0x00, curCount);
			
      HAL_UART_Receive_DMA(&huart3, rx_buffer_wifi, sizeof(rx_buffer_wifi)); 

      //dis this frame message
      printf("curCount = %d\r\n", curCount);
      printf("wifi: %s\r\n", rx_data_wifi);
    } 

    lastCount = curCount;
    
    osDelay(10);
  }
  /* USER CODE END Usart3Task */
}

/* USER CODE BEGIN Header_StatusTask */
/**
* @brief Function implementing the statusTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StatusTask */
void StatusTask(void *argument)
{
  /* USER CODE BEGIN StatusTask */

  /* Infinite loop */
  for(;;)
  {
    BoardLed_R_TOG();
    osDelay(1000);
  }
  /* USER CODE END StatusTask */
}

/* USER CODE BEGIN Header_MqttTask */
/**
* @brief Function implementing the mqttTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MqttTask */
void MqttTask(void *argument)
{
  /* USER CODE BEGIN MqttTask */
  uint8_t tCount = 0;
  /* Infinite loop */
  for(;;)
  {
    // MQTT must work last wifi init over;
    while(osEventFlagsWait(initEventHandle, INITOVER_DEV_WIFI, osFlagsWaitAny | osFlagsNoClear, 0xffffffff)
        & INITOVER_DEV_WIFI  != INITOVER_DEV_WIFI)
    {
      osDelay(100);
    }

    while(MQTT_CONNECT() != HAL_OK){
      printf("MQTT wait 1...\r\n");
    }
    printf("MQTT CONNECT OVER\r\n");

    while(MQTT_SUBSCRIBE("topic", 2) != HAL_OK){
      printf("MQTT wait 2...\r\n");
    }
    printf("MQTT SUBSCRIBE \"topic\" OVER\r\n");

    while(MQTT_SUBSCRIBE("test", 2) != HAL_OK){
      printf("MQTT wait 2...\r\n");
    }
    printf("MQTT SUBSCRIBE \"test\" OVER\r\n");

    printf("MQTT INIT OVER");

    osEventFlagsSet(initEventHandle, INITOVER_DEV_MQTT);

    while(osEventFlagsGet (initEventHandle) & INITOVER_DEV_MQTT  == INITOVER_DEV_MQTT){
      
      MQTT_RECDATA_PROCESS();

      tCount++;
      if(tCount > 10){
        tCount = 0;
        MQTT_PINGREQ();
        printf("MQTT_PINGREQ\r\n");
      }
      osDelay(100);
    }

    osDelay(100);
  }
  /* USER CODE END MqttTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

