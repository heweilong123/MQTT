#include "dev8266.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

UART_HandleTypeDef* Serial_Wifi = NULL;
unsigned char *Wifi_rxData = NULL, *Wifi_rxLen = NULL;
unsigned char *Wifi_rxFlag = NULL;

static UART_HandleTypeDef* Serial()
{
    return Serial_Wifi;
}

#define ASSERT_HAVE_WIFI()  if( Serial() == NULL || \
                                Wifi_rxData == NULL || \
                                Wifi_rxLen == NULL || \
                                Wifi_rxFlag == NULL)  \
                                    return WIFI_NOINIT;

static WIFI_StatusTypeDef WIFI_print( const char* buf, ...)
{
    ASSERT_HAVE_WIFI();

    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(Serial(), str, strlen(str), 0xff);
    va_end(v);

    return WIFI_OK;
}

void Wifi_Serial(UART_HandleTypeDef* serial, unsigned char* data, unsigned char* len, unsigned char* flag)
{
    Serial_Wifi = serial;
    Wifi_rxData = data;
    Wifi_rxLen = len;
    Wifi_rxFlag = flag;
    *Wifi_rxFlag = 0;
}

WIFI_StatusTypeDef Wifi_Reset(void)
{
    ASSERT_HAVE_WIFI();

    unsigned int counts = 0;
    WIFI_print("AT+RST\r\n");

    while(strstr(Wifi_rxData, "OK\r\n") == NULL){
        WIFI_print("AT\r\n");

        while((*Wifi_rxFlag) == 0x00){
					HAL_Delay(1);
				}
				*Wifi_rxFlag = 0x00;
        printf("rec=%s\r\n",Wifi_rxData);
        counts++;
    } 
		
    WIFI_print("AT+CWLAP\r\n");
    return  WIFI_OK;
}
