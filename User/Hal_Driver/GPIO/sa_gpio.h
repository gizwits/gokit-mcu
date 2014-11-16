/**
  ******************************************************************************
  * @file    sa_gpio.h
  * @author  sa
  * @version V0.1
  * @date    2013/10/15
  * @brief   sa_STM32库的GPIO模块头文件
  *			 对STM32固件库V3.5的再一次封装
  *         
  ******************************************************************************
  * @stm32f10x_gpio.h 接口描述
  *	GPIO_DeInit 					将外设 GPIOx 寄存器重设为缺省值 
  * GPIO_AFIODeInit 				将复用功能（重映射事件控制和 EXTI 设置）重设为缺省值 
  * GPIO_Init 						根据 GPIO_InitStruct 中指定的参数初始化外设 GPIOx 寄存器 
  * GPIO_StructInit 				把 GPIO_InitStruct 中的每一个参数按缺省值填入 
  * GPIO_ReadInputDataBit 			读取指定端口管脚的输入 
  * GPIO_ReadInputData 				读取指定的 GPIO 端口输入 
  * GPIO_ReadOutputDataBit 			读取指定端口管脚的输出 
  * GPIO_ReadOutputData 			读取指定的 GPIO 端口输出 
  * GPIO_SetBits 					设置指定的数据端口位 
  * GPIO_ResetBits 					清除指定的数据端口位 
  * GPIO_WriteBit 					设置或者清除指定的数据端口位 
  * GPIO_Write 						向指定 GPIO 数据端口写入数据 
  * GPIO_PinLockConfig 				锁定 GPIO 管脚设置寄存器 
  * GPIO_EventOutputConfig 			选择 GPIO 管脚用作事件输出 
  * GPIO_EventOutputCmd 			使能或者失能事件输出 
  * GPIO_PinRemapConfig 			改变指定管脚的映射 
  * GPIO_EXTILineConfig 			选择 GPIO 管脚用作外部中断线路 
  ******************************************************************************
  */
#ifndef _SA_GPIO_H_
#define _SA_GPIO_H_

#include "stm32f10x.h"


void SA_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed);


#endif
