#ifndef _HAL_HEMP_HUM_H
#define _HAL_HEMP_HUM_H

#include <stdio.h>
#include <stm32f10x.h>
#include "delay.h"
#include "sys.h"  

//Set GPIO Direction
#define DHT11_IO_IN()  GPIO_InitTypeDef GPIO_InitStruct;\
	                     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;\
	                     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;\
	                     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;\
	                     GPIO_Init(GPIOB, &GPIO_InitStruct);
											 
#define DHT11_IO_OUT() GPIO_InitTypeDef GPIO_InitStruct;\
	                     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;\
	                     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;\
	                     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;\
	                     GPIO_Init(GPIOB, &GPIO_InitStruct);
	
#define	DHT11_DQ_OUT PBout(5) 
#define	DHT11_DQ_IN  PBin(5)  


u8 DHT11_Init(void); //Init DHT11
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity); //Read DHT11 Value
u8 DHT11_Read_Byte(void);//Read One Byte
u8 DHT11_Read_Bit(void);//Read One Bit
u8 DHT11_Check(void);//Chack DHT11
void DHT11_Rst(void);//Reset DHT11    



#endif /*_HAL_HEMP_HUM_H*/

