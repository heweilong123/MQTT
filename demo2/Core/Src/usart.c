/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <string.h>
#include "main.h"

#include "stm32h7xx_it.h"

#include "dev8266.h"

extern uint8_t rx_len_cmd;  
extern uint8_t rx_buffer_cmd[200];
extern uint8_t tx_buffer_cmd[200];

extern uint8_t rx_len_wifi;  
extern uint8_t rx_buffer_wifi[255];
extern uint8_t rx_data_wifi[255];
extern uint8_t rx_flag;
/* USER CODE END 0 */

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_lpuart1_rx;
DMA_HandleTypeDef hdma_lpuart1_tx;
DMA_HandleTypeDef hdma_usart3_rx;

/* LPUART1 init function */

void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspInit 0 */

  /* USER CODE END LPUART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    PeriphClkInitStruct.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_D3PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LPUART1 clock enable */
    __HAL_RCC_LPUART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**LPUART1 GPIO Configuration
    PA9     ------> LPUART1_TX
    PA10     ------> LPUART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_LPUART;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* LPUART1 DMA Init */
    /* LPUART1_RX Init */
    hdma_lpuart1_rx.Instance = BDMA_Channel0;
    hdma_lpuart1_rx.Init.Request = BDMA_REQUEST_LPUART1_RX;
    hdma_lpuart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_lpuart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_lpuart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_lpuart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_lpuart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_lpuart1_rx.Init.Mode = DMA_NORMAL;
    hdma_lpuart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_lpuart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_lpuart1_rx);

    /* LPUART1_TX Init */
    hdma_lpuart1_tx.Instance = BDMA_Channel1;
    hdma_lpuart1_tx.Init.Request = BDMA_REQUEST_LPUART1_TX;
    hdma_lpuart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_lpuart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_lpuart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_lpuart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_lpuart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_lpuart1_tx.Init.Mode = DMA_NORMAL;
    hdma_lpuart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_lpuart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_lpuart1_tx);

    /* LPUART1 interrupt Init */
    HAL_NVIC_SetPriority(LPUART1_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspInit 1 */

  /* USER CODE END LPUART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Stream0;
    hdma_usart3_rx.Init.Request = DMA_REQUEST_USART3_RX;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart3_rx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspDeInit 0 */

  /* USER CODE END LPUART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPUART1_CLK_DISABLE();

    /**LPUART1 GPIO Configuration
    PA9     ------> LPUART1_TX
    PA10     ------> LPUART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* LPUART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* LPUART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspDeInit 1 */

  /* USER CODE END LPUART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 5);
  return ch;
}

int fgetc(FILE *f)
{
	uint8_t  ch;
  HAL_UART_Receive(&hlpuart1,(uint8_t *)&ch, 1, 0xFFFF);
	return  ch;
}

void MY_UART_Transmit(unsigned char* data, unsigned char len)
{
  memcpy(tx_buffer_cmd, data, len);	
  BDMA->IFCR |= 0xF0;
  HAL_UART_Transmit_DMA(&hlpuart1, tx_buffer_cmd, len);

  BDMA_Channel_TypeDef * bdma = hdma_lpuart1_tx.Instance;
  while(bdma->CNDTR != 0);
  USART_TypeDef * usart = hlpuart1.Instance;
  while((usart->ISR & (1<<6)) == (1<<6));
}

void MY_CMD_INIT(void)
{
	__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&hlpuart1,rx_buffer_cmd,sizeof(rx_buffer_cmd));
	rx_len_cmd = 0;
}

void MY_WIFI_INIT(void)
{
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart3, rx_buffer_wifi, sizeof(rx_buffer_wifi));
  HAL_Delay(100);
  // unsigned char usart3Send[] = "AT+RST\r\n";
  // HAL_UART_Transmit(&huart3, usart3Send, sizeof(usart3Send),0xff);
  Wifi_Serial(&huart3, rx_data_wifi, &rx_len_wifi, &rx_flag);
  Wifi_Reset();
}
/* USER CODE END 1 */
