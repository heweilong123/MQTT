#include "devMQTT.h"
#include <string.h>
#include <stdio.h>

const char MQTT_CLIENTID[] =  "589493534";
const char MQTT_USERNAME[] =  "330283";
const char MQTT_USERPAWD[] =  "123456";

HAL_StatusTypeDef MQTT_CONNECT(void)
{
    memset(MQTT_SEND_BUFFER, 0x00, sizeof(MQTT_SEND_BUFFER));

    uint8_t number = 0;
    MQTT_SEND_BUFFER[number ++] = 0x10;
    MQTT_SEND_BUFFER[number ++] = 0xFF;
    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = 0x04;
    MQTT_SEND_BUFFER[number ++] = 0x4D;
    MQTT_SEND_BUFFER[number ++] = 0x51;
    MQTT_SEND_BUFFER[number ++] = 0x54;
    MQTT_SEND_BUFFER[number ++] = 0x54;
    MQTT_SEND_BUFFER[number ++] = 0x04;
    MQTT_SEND_BUFFER[number ++] = 0xC2;
    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = 0x78;

    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = strlen(MQTT_CLIENTID);
    for(uint8_t i = 0; i < strlen(MQTT_CLIENTID); i++)
        MQTT_SEND_BUFFER[number ++] = *(MQTT_CLIENTID + i);

    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = strlen(MQTT_USERNAME);
    for(uint8_t i = 0; i < strlen(MQTT_USERNAME); i++)
        MQTT_SEND_BUFFER[number ++] = *(MQTT_USERNAME + i);

    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = strlen(MQTT_USERPAWD);
    for(uint8_t i = 0; i < strlen(MQTT_USERPAWD); i++)
        MQTT_SEND_BUFFER[number ++] = *(MQTT_USERPAWD + i);

    MQTT_SEND_BUFFER[1] = number - 2;

    MQTT_SEND_DATA(MQTT_SEND_BUFFER[1] + 2);;
                                    
    Wifi_Delay(100);

    char recData[4] = {0x20, 0x02, 0x01, 0x00};
    if(MQTT_BACKDATA_VERIFY(recData) == HAL_OK){
        printf("MQTT CONNECT\r\n");
        return HAL_OK;
    }
    else{
        printf("MQTT DISCONNECT\r\n");
        return HAL_ERROR;
    }
}

