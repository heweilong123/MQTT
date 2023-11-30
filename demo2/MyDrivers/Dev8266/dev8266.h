#ifndef __DEV_8266_H__
#define __DEV_8266_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef enum
{
  WIFI_OK       = 0x00,
  WIFI_NOWORK,
  WIFI_NOINIT,
  WIFI_ERROR
} WIFI_StatusTypeDef;

void Wifi_Serial(UART_HandleTypeDef* serial, unsigned char* data, unsigned char* len, unsigned char* flag);

WIFI_StatusTypeDef Wifi_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
