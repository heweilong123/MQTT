#ifndef __DEV_8266_H__
#define __DEV_8266_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os2.h"
#include "usart.h"

typedef enum
{
  WIFI_OK       = 0x00,
  WIFI_NOWORK,
  WIFI_NOINIT,
  WIFI_ERROR,
  WIFI_NOREC
} WIFI_StatusTypeDef;


#define Wifi_Delay(t) HAL_Delay(t);

extern uint8_t rx_flag_wifi;
extern uint8_t rx_len_wifi; 
extern uint8_t rx_data_wifi[1024];
extern uint8_t tx_buffer_wifi[1024];

#define WIFI_SERIAL   &huart3
#define WIFI_RECDATA  rx_data_wifi
#define WIFI_SNEDDATA tx_buffer_wifi
#define WIFI_RECFLAG  rx_flag_wifi
#define WIFI_RECLEN   rx_len_wifi

WIFI_StatusTypeDef Wifi_Reset(void);

WIFI_StatusTypeDef Wifi_IsReady(void);

WIFI_StatusTypeDef Wifi_AllAP(void);

/*
1 Station 模式
2 AP 模式
3 AP+Station 模式
*/
WIFI_StatusTypeDef Wifi_WIFIMODE(uint8_t mode);

/*
name      wifiname 
password  wifipassword
*/
WIFI_StatusTypeDef Wifi_JoinWifi(char* name, char* password);

/*
1 more connecct
0 single connect
*/
WIFI_StatusTypeDef Wifi_ConnectMode(uint8_t mode);

/*
name      wifiname 
password  wifipassword
*/
WIFI_StatusTypeDef Wifi_TCPConnect(char* ip, unsigned int port);

/*
1  Transparent transmission mode
0  No Transparent transmission mode
*/
WIFI_StatusTypeDef Wifi_TransmissionMode(uint8_t mode);

WIFI_StatusTypeDef Wifi_BackData_Verify(const char* str);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
