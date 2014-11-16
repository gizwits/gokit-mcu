/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 
	
#include <stm32f10x_it.h>
#include "hal_uart.h"
#include "hal_key.h"
#include "delay.h"
#include "protocol.h"

extern m2w_mcuStatus							m_m2w_mcuStatus;
extern uint8_t 										uart_buf[]; 
extern uint8_t 										uart_Count;
extern uint8_t 										cmd_flag ;
extern uint8_t 										cmd_len ;
extern uint8_t 										wait_ack_time;
extern uint8_t 										check_status_time;
extern uint8_t										report_status_idle_time;
extern uint16_t 									Key_Return;           						//按键返回值
extern uint8_t 										cmd_flag1, cmd_flag2;

extern uint8_t get_one_package;
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/***ev;i***********************************************************************/

void USART1_IRQHandler(void)
{  
	uint8_t 	vlue;
	short			i;
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  { 
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		vlue = USART_ReceiveData(USART1);
		if(get_one_package ==0)
		{
			if(cmd_flag1 ==0)
			{
				if(vlue == 0xff)
				{   
						uart_Count = 0;						
						uart_buf[uart_Count]=vlue;
						uart_Count++;	
						cmd_flag1 = 1;
				}			
				return ;
			}
			if(cmd_flag2 ==0)
			{
				if(cmd_flag2)
				{
						uart_buf[uart_Count]=vlue;
						uart_Count++;
						if(uart_buf[1] == 0xff)
						{
							cmd_flag2 = 1;							
						}	
						else
						{
							cmd_flag1 = 0;
						}
				}
				cmd_flag2 = 1;
			}
			uart_buf[uart_Count] = vlue;
			if(uart_Count >=4 && uart_buf[uart_Count] == 0x55 && uart_buf[uart_Count-1] == 0xFF){}
			else uart_Count++;
			if(uart_Count == 0x04)
			{
				cmd_len = uart_buf[2]*256 +  uart_buf[3]; 															
			}
			if(uart_Count ==  (cmd_len + 4))
			{
				get_one_package = 1;
				cmd_flag1 = 0;
			}														
		}		
  }	
}

/******************************************************************************/
/*             KEY1 :长按  RESET WIFI, KEY2 :短按  配置WiFi联                 */
/*             定时器3中断服务程序                                            */
/******************************************************************************/
void TIM3_IRQHandler(void)   				
{
  static uint8_t Key_State   = 0;        							//按键状态     
	static uint8_t Key_Prev    = 0;        							//上一次按键     
	static uint16_t Key_Delay   = 0;        						//按键连发时间     
	static uint8_t Key_Series  = FALSE;    							//标志连发开始	
	
	uint16_t Key_Press  = NO_KEY;          	 						//按键值     
		
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  		//清除TIMx更新中断标志 
		wait_ack_time++;
		check_status_time++;
		report_status_idle_time++;
			
		Key_Press  =	Get_Key();	

		switch (Key_State)
		{
			case 0:
				if(Key_Press != NO_KEY)
				{
					Key_State = 1;															//转到按键确认              
					Key_Prev  = Key_Press;											//保存按键状态
				}	
				break;
			case 1:
				if(Key_Press == Key_Prev) 										//确认和上次按键相同
				{
					Key_State = 2;															//判断按键长按                         
					Key_Return = KEY_DOWN | Key_Prev;
				}	
				else 																					//按键抬起,是抖动,不响应按键 
				{
					Key_State = 0;
				}
				break;
				case 2:
				if(Key_Press == NO_KEY )											//按键释放了 
				{
					Key_State = 0;
					Key_Delay = 0; 
					Key_Series  = FALSE;
					Key_Return  = KEY_UP | Key_Prev;      			//返回按键抬起值
					break;
				}	
				if ( Key_Press ==Key_Prev )
				{
					Key_Delay++; 
					if (Key_Delay>KEY_SERIES_FLAG) 
					{               
						Key_Delay  = 0;                  
						Key_Return = KEY_LONG | Key_Prev;   			//返回长按后的值 				
						break; 
					}
				}
				break;
			default:
				break;
		}		
	}
} 

void EXTI15_10_IRQHandler(void) 
{
	EXTI->EMR &= (uint32_t)~(1<<1);   									//屏蔽中断事件

	while(EXTI_GetITStatus(EXTI_Line12)!= RESET ) 
	{		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
		{
			m_m2w_mcuStatus.status_r.ir_status &= ~(1<<0);
		}
		else
		{		
			m_m2w_mcuStatus.status_r.ir_status |= (1<<0);
		}	
	
		EXTI_ClearITPendingBit(EXTI_Line12);
	}	
	
	EXTI->EMR |= (uint32_t)(1<<1);  										//开启中断事件  
}

/**
  * @}
  */ 
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
