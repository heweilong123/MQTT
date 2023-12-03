#ifndef __DEV_MQTT_H__
#define __DEV_MQTT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include  "dev8266.h"
#include "main.h"

#define MQTT_SEND_BUFFER WIFI_SNEDDATA
#define MQTT_SEND_DATA(len)  Wifi_SendBufData(len)
#define MQTT_BACKDATA_VERIFY(str) Wifi_BackData_Verify(str)

HAL_StatusTypeDef MQTT_CONNECT(void);
HAL_StatusTypeDef MQTT_DISCONNECT(void);

HAL_StatusTypeDef MQTT_PINGREQ(void);

HAL_StatusTypeDef MQTT_SUBSCRIBE(char* topic, uint8_t serviceLevel);

#ifdef __cplusplus
}
#endif

#endif 
