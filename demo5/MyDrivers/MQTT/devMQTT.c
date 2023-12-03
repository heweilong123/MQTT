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
        printf("MQTT CONNECT TRUE\r\n");
        return HAL_OK;
    }
    else{
        printf("MQTT CONNECT ERROR\r\n");
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef MQTT_DISCONNECT(void)
{
    memset(MQTT_SEND_BUFFER, 0x00, sizeof(MQTT_SEND_BUFFER));

    uint8_t number = 0;
    MQTT_SEND_BUFFER[number ++] = 0xE0;
    MQTT_SEND_BUFFER[number ++] = 0x00;

    MQTT_SEND_DATA(2);;
                   
    Wifi_Delay(100);
    
    return HAL_OK;
}

HAL_StatusTypeDef MQTT_PINGREQ(void)
{
    memset(MQTT_SEND_BUFFER, 0x00, sizeof(MQTT_SEND_BUFFER));

    uint8_t number = 0;
    MQTT_SEND_BUFFER[number ++] = 0xC0;
    MQTT_SEND_BUFFER[number ++] = 0x00;

    MQTT_SEND_DATA(2);;
                                    
    Wifi_Delay(100);

    char recData[] = {0xD0, 0x00};
    if(MQTT_BACKDATA_VERIFY(recData) == HAL_OK){
        printf("MQTT PINGREQ TRUE\r\n");
        return HAL_OK;
    }
    else{
        printf("MQTT PINGREQ ERROR\r\n");
        return HAL_ERROR;
    }   
}

HAL_StatusTypeDef MQTT_SUBSCRIBE(char* topic, uint8_t serviceLevel)
{
    memset(MQTT_SEND_BUFFER, 0x00, sizeof(MQTT_SEND_BUFFER));

    uint8_t number = 0;
    MQTT_SEND_BUFFER[number ++] = 0x82;
    MQTT_SEND_BUFFER[number ++] = 0xFF;
    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = 0x0A;

    MQTT_SEND_BUFFER[number ++] = 0x00;
    MQTT_SEND_BUFFER[number ++] = strlen(topic);
    for(uint8_t i = 0; i < strlen(topic); i++)
        MQTT_SEND_BUFFER[number ++] = *(topic + i);
        
    MQTT_SEND_BUFFER[number ++] = serviceLevel;

    MQTT_SEND_BUFFER[1] = number - 2;

    MQTT_SEND_DATA(MQTT_SEND_BUFFER[1]  + 2);
                                    
    Wifi_Delay(100);

    char recData[] = {0x90, 0x03, MQTT_SEND_BUFFER[2],  MQTT_SEND_BUFFER[3], serviceLevel};
    if(MQTT_BACKDATA_VERIFY(recData) == HAL_OK){
        printf("MQTT SUBSCRIBE \"%s\" TRUE\r\n", topic);
        return HAL_OK;
    }
    else{
        printf("MQTT SUBSCRIBE \"%s\" ERROR\r\n",topic);
        return HAL_ERROR;
    }   
}
