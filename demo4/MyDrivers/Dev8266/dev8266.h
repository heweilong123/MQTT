#ifndef __DEV_8266_H__
#define __DEV_8266_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os2.h"
#include "usart.h"

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

#define WIFI_RST_PIN_RST()  HAL_GPIO_WritePin(WifiRST_GPIO_Port, WifiRST_Pin, GPIO_PIN_RESET);
#define WIFI_RST_PIN_WORK() HAL_GPIO_WritePin(WifiRST_GPIO_Port, WifiRST_Pin, GPIO_PIN_SET);
/**
 * mode 1 handware 0 software
*/
HAL_StatusTypeDef Wifi_Reset(uint8_t mode);

HAL_StatusTypeDef Wifi_IsReady(void);

HAL_StatusTypeDef Wifi_AllAP(void);

/*
1 Station 模式
2 AP 模式
3 AP+Station 模式
*/
HAL_StatusTypeDef Wifi_WIFIMODE(uint8_t mode);

/*
name      wifiname 
password  wifipassword
*/
HAL_StatusTypeDef Wifi_JoinWifi(char* name, char* password);

/*
1 more connecct
0 single connect
*/
HAL_StatusTypeDef Wifi_ConnectMode(uint8_t mode);

/*
name      wifiname 
password  wifipassword
*/
HAL_StatusTypeDef Wifi_TCPConnect(char* ip, unsigned int port);

/*
1  Transparent transmission mode
0  No Transparent transmission mode
*/
HAL_StatusTypeDef Wifi_TransmissionMode(uint8_t mode);

HAL_StatusTypeDef Wifi_BackData_Verify(const char* str);

/*
  senddata WIFI_SNEDDATA
  dataLen send data len
*/
void Wifi_SendBufData(uint16_t dataLen);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
