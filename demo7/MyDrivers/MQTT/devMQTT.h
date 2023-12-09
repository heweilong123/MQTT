#ifndef __DEV_MQTT_H__
#define __DEV_MQTT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include  "dev8266.h"
#include "main.h"

#define MQTT_SEND_BUFFER WIFI_SNEDDATA
#define MQTT_REC_BUFFER  WIFI_RECDATA
#define MQTT_RECFLAG     WIFI_RECFLAG
#define MQTT_SEND_DATA(len)  Wifi_SendBufData(len)
#define MQTT_BACKDATA_VERIFY(str) Wifi_BackData_Verify(str)

HAL_StatusTypeDef MQTT_CONNECT(void);
HAL_StatusTypeDef MQTT_DISCONNECT(void);

HAL_StatusTypeDef MQTT_PINGREQ(void);

HAL_StatusTypeDef MQTT_SUBSCRIBE(char* topic, uint8_t serviceLevel);
HAL_StatusTypeDef MQTT_UNSUBACK(char* topic);

HAL_StatusTypeDef MQTT_PUBLISH(char* topic, uint8_t serviceLevel, const char* data);

HAL_StatusTypeDef MQTT_PUBREL(uint16_t id);

void MQTT_RECDATA_PROCESS(void);
#ifdef __cplusplus
}
#endif

#endif 
