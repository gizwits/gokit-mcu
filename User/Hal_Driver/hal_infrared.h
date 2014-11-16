#ifndef _HAL_INFRARED_H
#define _HAL_INFRARED_H

#include <stdio.h>
#include <stm32f10x.h>
#include "delay.h"
#include "hal_uart.h"

void IR_EXTI_Init(void);
void IR_TIM_Init(void);
void IR_TIM_Init(void);

void IR_Init(void);
void IR_Handle(void);
void IR_GPIO_Init(void);
#endif /*_HAL_INFRARED_H*/


