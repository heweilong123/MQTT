#include "dev8266.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

const char MQTT_CLIENTID[] =  "589493534";
const char MQTT_USERNAME[] =  "330283";
const char MQTT_USERPAWD[] =  "123456";

#define ASSERT_HAVE_WIFI()  if(Wifi_IsReady() != WIFI_OK) return WIFI_NOWORK;

static WIFI_StatusTypeDef WIFI_print( const char* buf, ...)
{
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(WIFI_SERIAL, (unsigned char*)str, strlen(str), 0xff);
    va_end(v);

    return WIFI_OK;
}

WIFI_StatusTypeDef Wifi_BackData_Verify(const char* str)
{
    printf("8266 Wait %s\r\n", str);
	
    while(WIFI_RECFLAG != 0x01){
			Wifi_Delay(10);
		}
		
    WIFI_RECFLAG = 0x00;

    if(strstr((const char*)WIFI_RECDATA, str) == NULL){
        return WIFI_NOREC;
		}
    else{
        return WIFI_OK;
    }
}

WIFI_StatusTypeDef Wifi_Reset(void)
{
    WIFI_StatusTypeDef ret;

		ret = WIFI_print("AT+RST\r\n");
    if(ret != WIFI_OK) 
        return ret; 
		
    Wifi_Delay(1000);

    return ret;
}

WIFI_StatusTypeDef Wifi_IsReady(void)
{
	WIFI_RECFLAG = 0;
	
    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT\r\n");
    if(ret != WIFI_OK) 
        return ret; 
		printf("wifi Send AT\r\n");
    
    Wifi_Delay(10);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}
}

WIFI_StatusTypeDef Wifi_AllAP(void)
{
	WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CWLAP\r\n");
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(5000);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}
}

WIFI_StatusTypeDef Wifi_WIFIMODE(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CWMODE=%d\r\n", mode);
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(100);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}
}

WIFI_StatusTypeDef Wifi_JoinWifi(char* name, char* password)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CWJAP=\"%s\",\"%s\"\r\n", name, password);
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(5000);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}
}

WIFI_StatusTypeDef Wifi_ConnectMode(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPMUX=%d\r\n", mode);
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(500);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}
}

WIFI_StatusTypeDef Wifi_TCPConnect(char* ip, unsigned int port)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(3000);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
        return WIFI_OK;
	}   
}

WIFI_StatusTypeDef Wifi_TransmissionMode(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    WIFI_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPMODE=%d\r\n", mode);
    if(ret != WIFI_OK) 
        return ret; 

    Wifi_Delay(100);

    if(Wifi_BackData_Verify("OK")  != WIFI_OK ){
        printf("8266 NO OK\r\n");
        return WIFI_NOWORK;
    }
    else{
        printf("8266 OK\r\n");
	}

    if(mode == 1){
        ret = WIFI_print("AT+CIPSEND\r\n");
        if(ret != WIFI_OK) 
            return ret; 

        Wifi_Delay(100);

        if(Wifi_BackData_Verify(">")  != WIFI_OK ){
            printf("8266 NO OK\r\n");
            return WIFI_NOWORK;
        }
        else{
            printf("8266 OK\r\n");
            {
                memset(tx_buffer_wifi, 0x00, sizeof(tx_buffer_wifi));

                uint8_t number = 0;
                tx_buffer_wifi[number ++] = 0x10;
                tx_buffer_wifi[number ++] = 0xFF;
                tx_buffer_wifi[number ++] = 0x00;
                tx_buffer_wifi[number ++] = 0x04;
                tx_buffer_wifi[number ++] = 0x4D;
                tx_buffer_wifi[number ++] = 0x51;
                tx_buffer_wifi[number ++] = 0x54;
                tx_buffer_wifi[number ++] = 0x54;
                tx_buffer_wifi[number ++] = 0x04;
                tx_buffer_wifi[number ++] = 0xC2;
                tx_buffer_wifi[number ++] = 0x00;
                tx_buffer_wifi[number ++] = 0x78;

                tx_buffer_wifi[number ++] = 0x00;
                tx_buffer_wifi[number ++] = strlen(MQTT_CLIENTID);
                for(uint8_t i = 0; i < strlen(MQTT_CLIENTID); i++)
                    tx_buffer_wifi[number ++] = *(MQTT_CLIENTID + i);

                tx_buffer_wifi[number ++] = 0x00;
                tx_buffer_wifi[number ++] = strlen(MQTT_USERNAME);
                for(uint8_t i = 0; i < strlen(MQTT_USERNAME); i++)
                    tx_buffer_wifi[number ++] = *(MQTT_USERNAME + i);

                tx_buffer_wifi[number ++] = 0x00;
                tx_buffer_wifi[number ++] = strlen(MQTT_USERPAWD);
                for(uint8_t i = 0; i < strlen(MQTT_USERPAWD); i++)
                    tx_buffer_wifi[number ++] = *(MQTT_USERPAWD + i);

                tx_buffer_wifi[1] = number - 2;

//               printf("data len = %d %d\r\n", strlen(data), data[1]);
                HAL_UART_Transmit(WIFI_SERIAL, (const uint8_t*)tx_buffer_wifi, tx_buffer_wifi[1] + 2, 0xffff);
												
								Wifi_Delay(100);
             }
            return WIFI_OK;
        }
    }

    return WIFI_OK;  
}
