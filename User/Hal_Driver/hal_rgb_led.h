#ifndef _HAL_RGB_LED_H
#define _HAL_RGB_LED_H

#include <stdio.h>
#include <stm32f10x.h>
#include "hal_rgb_led.h"
#include "protocol.h"


#define  R_MAX  255
#define  G_MAX  255
#define  B_MAX  255

#define SCL_LOW 	GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SCL_HIGH 	GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define SDA_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SDA_HIGH	GPIO_SetBits(GPIOB,GPIO_Pin_7)


void RGB_LED_Init(void);
void LED_R_Control(uint8_t R);
void LED_G_Control(uint8_t G);
void LED_B_Control(uint8_t B);
void LED_RGB_Control(uint8_t R,uint8_t B,uint8_t G);

#endif /*_HAL_RGB_LED_H*/

