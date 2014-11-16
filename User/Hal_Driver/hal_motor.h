#ifndef _HAL_MOTOR_H
#define _HAL_MOTOR_H

#include <stdio.h>
#include <stm32f10x.h>
#include "hal_uart.h"
#include "sys.h"
#include "sa_gpio.h"

#define Motor_stop        0
#define Motor_Forward     1
#define Motor_Reverse     2


#define MOT1 PBout(8)
#define MOT2 PBout(9)

#define MOTOR_ARR 899 //8kHZ
#define MOTOR_MAX 100
#define MOTOR_MAX1 -100
#define MOTOR_MIN 0




void Motor_Init(void);
void Motor_status(uint8_t status);

#endif /*_HAL_MOTOR_H*/


