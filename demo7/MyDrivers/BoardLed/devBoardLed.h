#ifndef __DEV_BOARDLED_H__
#define __DEV_BOARDLED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define BoardLed_R_ON()     HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)
#define BoardLed_R_OFF()    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)
#define BoardLed_R_TOG()    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)

#define BoardLed_G_ON()     HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET)
#define BoardLed_G_OFF()    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)
#define BoardLed_G_TOG()    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)

#define BoardLed_B_ON()     HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)
#define BoardLed_B_OFF()    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)
#define BoardLed_B_TOG()    HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

#ifdef __cplusplus
}
#endif

#endif 
