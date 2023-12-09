#include "dev8266.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define ASSERT_HAVE_WIFI()  if(Wifi_IsReady() != HAL_OK) return HAL_ERROR;

static HAL_StatusTypeDef WIFI_print( const char* buf, ...)
{
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(WIFI_SERIAL, (unsigned char*)str, strlen(str), 0xff);
    va_end(v);

    return HAL_OK;
}

HAL_StatusTypeDef Wifi_BackData_Verify(const char* str)
{
    //uint16_t waitCount = 0;
    printf("8266 Wait %s %d\r\n", str, strlen(str));
	
    // while(WIFI_RECFLAG != 0x01 && waitCount < 100){
    //         waitCount++;
	// 		Wifi_Delay(10);
	// }

    // if(waitCount == 100)
    //     return HAL_TIMEOUT;
		
    while(WIFI_RECFLAG != 0x01){
        Wifi_Delay(10);
	}

    WIFI_RECFLAG = 0x00;


    if(strstr((const char*)WIFI_RECDATA, str) == NULL){
        printf("ERRPR \r\n");
        memset(WIFI_RECDATA, 0x00, sizeof(WIFI_RECDATA));
        return HAL_ERROR;
	}
    else{
        printf("true \r\n");
        memset(WIFI_RECDATA, 0x00, sizeof(WIFI_RECDATA));
        return HAL_OK;
    }

    
}

HAL_StatusTypeDef Wifi_Reset(uint8_t mode)
{
    if(mode == 0){
        HAL_StatusTypeDef ret;

        ret = WIFI_print("AT+RST\r\n");
        if(ret != HAL_OK) 
            return ret; 
            
        Wifi_Delay(1000);

        return ret;
    }
    else{
        WIFI_RST_PIN_RST();
        
        Wifi_Delay(100);
        
        WIFI_RST_PIN_WORK();
        
        Wifi_Delay(1000);

        return HAL_OK;
    }
}

HAL_StatusTypeDef Wifi_IsReady(void)
{
	WIFI_RECFLAG = 0;
	
    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT\r\n");
    if(ret != HAL_OK) 
        return ret; 
		printf("wifi Send AT\r\n");
    
    Wifi_Delay(10);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}
}

HAL_StatusTypeDef Wifi_AllAP(void)
{
	WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CWLAP\r\n");
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(5000);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}
}

HAL_StatusTypeDef Wifi_WIFIMODE(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CWMODE=%d\r\n", mode);
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(100);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}
}

HAL_StatusTypeDef Wifi_JoinWifi(char* name, char* password)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CWJAP=\"%s\",\"%s\"\r\n", name, password);
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(5000);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}
}

HAL_StatusTypeDef Wifi_ConnectMode(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPMUX=%d\r\n", mode);
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(500);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}
}

HAL_StatusTypeDef Wifi_TCPConnect(char* ip, unsigned int port)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(3000);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
        return HAL_OK;
	}   
}

HAL_StatusTypeDef Wifi_TransmissionMode(uint8_t mode)
{
    WIFI_RECFLAG = 0;
	
    ASSERT_HAVE_WIFI();

    HAL_StatusTypeDef ret;

    ret = WIFI_print("AT+CIPMODE=%d\r\n", mode);
    if(ret != HAL_OK) 
        return ret; 

    Wifi_Delay(100);

    if(Wifi_BackData_Verify("OK")  != HAL_OK ){
        printf("8266 NO OK\r\n");
        return HAL_ERROR;
    }
    else{
        printf("8266 OK\r\n");
	}

    if(mode == 1){
        ret = WIFI_print("AT+CIPSEND\r\n");
        if(ret != HAL_OK) 
            return ret; 

        Wifi_Delay(100);

        if(Wifi_BackData_Verify(">")  != HAL_OK ){
            printf("8266 NO OK\r\n");
            return HAL_ERROR;
        }
        else{
            printf("8266 OK\r\n");

            return HAL_OK;
        }
    }

    return HAL_OK;  
}

void Wifi_SendBufData(uint16_t dataLen)
{
    HAL_UART_Transmit(WIFI_SERIAL, (const uint8_t*)tx_buffer_wifi, dataLen, 0xffff);
}
