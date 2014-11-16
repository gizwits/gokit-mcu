/**
  ******************************************************************************
  * @file    sa_gpio.c
  * @author  sa
  * @version V0.1
  * @date    2013/10/15
  * @brief   sa_STM32库的GPIO模块源文件
  *			 对STM32固件库V3.5的再一次封装
  *         
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "sa_gpio.h"


/**
  * @brief  GPIO初始化
  * @param  GPIOx: 初始化的GPIO端口 					
  *			GPIOx		x:(A..G) 	例:GPIOA
  * @param  GPIO_Pin: 选择待设置的 GPIO 管脚，使用操作符“|”可以一次选中多个管脚 	
  *			GPIO_Pin_x	x:(0..15)	例:GPIO_Pin_1 | GPIO_Pin_2
  * @param	GPIO_Mode:选择初始化模式
  *			GPIO_Mode_AIN 			模拟输入 
  *			GPIO_Mode_IN_FLOATING 	浮空输入 
  *			GPIO_Mode_IPD 			下拉输入 
  *			GPIO_Mode_IPU 			上拉输入 
  *			GPIO_Mode_Out_OD 		开漏输出 
  *			GPIO_Mode_Out_PP 		推挽输出 
  *			GPIO_Mode_AF_OD 		复用开漏输出 
  *			GPIO_Mode_AF_PP 		复用推挽输出
  * @param  GPIO_Speed:用以设置选中管脚的速率
  *			GPIO_Speed_10MHz 		最高输出速率 10MHz 
  *			GPIO_Speed_2MHz 		最高输出速率 2MHz 
  *			GPIO_Speed_50MHz 		最高输出速率 50MHz  		
  * @retval None
  */
void SA_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	if (GPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if (GPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	}    
	else if (GPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	} 
	else if (GPIOx == GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else
	{
		if (GPIOx == GPIOG)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		}
	}
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin;				
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode; 		 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed;		 
	GPIO_Init(GPIOx, &GPIO_InitStructure);					 
}
 
