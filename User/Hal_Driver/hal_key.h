#ifndef _HAL_KEY_H
#define _HAL_KEY_H

#include <stdio.h>
#include <stm32f10x.h>

#define GPIO_KEY1_CLK    	RCC_APB2Periph_GPIOB
#define GPIO_KEY1_PORT   	GPIOB
#define GPIO_KEY1_PIN    	GPIO_Pin_12

#define GPIO_KEY2_CLK    	RCC_APB2Periph_GPIOB
#define GPIO_KEY2_PORT   	GPIOB
#define GPIO_KEY2_PIN    	GPIO_Pin_13

#define GPIO_KEY3_CLK    	RCC_APB2Periph_GPIOB
#define GPIO_KEY3_PORT   	GPIOB
#define GPIO_KEY3_PIN    	GPIO_Pin_14

#define GPIO_KEY4_CLK    	RCC_APB2Periph_GPIOB
#define GPIO_KEY4_PORT   	GPIOB
#define GPIO_KEY4_PIN    	GPIO_Pin_15


#define PRESS_KEY1   			0x0001
#define PRESS_KEY2   			0x0002
#define PRESS_KEY3   			0x0004
#define PRESS_KEY4   			0x0008

#define NO_KEY      			0x0000
#define KEY_DOWN    			0x0020     			//按下
#define KEY_UP    	 			0x0040     			//抬起
#define KEY_LIAN     			0x0080     			//连发
#define KEY_LONG     			0x0100

#define  KEY_SERIES_DELAY 5       				//连发时间间隔
#define  KEY_SERIES_FLAG  200      				//长按时间间隔
#define  FALSE       			0
#define  TRUE        			1

void KEY_GPIO_Init(void);
uint8_t Read_KEY_State(void);
uint8_t Get_Key(void);
void TIM3_Int_Init(u16 arr,u16 psc);
void KeyHandle(void);

#endif /*_HAL_KEY_H*/

