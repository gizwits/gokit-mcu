#include "hal_key.h"
#include "delay.h"
#include "protocol.h"



extern m2w_mcuStatus			m_m2w_mcuStatus;
extern m2w_setModule			m_m2w_setModule;
extern pro_commonCmd			m_pro_commonCmd;
extern int								SN;		
extern uint32_t						wait_wifi_status;

uint16_t Key_Return = NO_KEY;           	//按键返回值

/*******************************************************************************
* Function Name  : KEY_GPIO_Init
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_KEY1_CLK | GPIO_KEY2_CLK | GPIO_KEY3_CLK | GPIO_KEY4_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
	GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
	GPIO_Init(GPIO_KEY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY3_PIN;
	GPIO_Init(GPIO_KEY3_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY4_PIN;
	GPIO_Init(GPIO_KEY4_PORT, &GPIO_InitStructure);
	
}

/*******************************************************************************
* Function Name  : TIM3_Int_Init
* Description    : TIM3 initialization function
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 						//时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 								//根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 											//使能指定的TIM3中断,允许更新中断
 
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  								//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  			//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  						//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 								//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  																//初始化NVIC寄存器 
	TIM_Cmd(TIM3, ENABLE);  																				//使能TIMx					 
}

/*******************************************************************************
* Function Name  : Get_Key
* Description    : Read the KEY state
* Input          : None
* Output         : None
* Return         : uint8_t KEY state
* Attention		 : None
*******************************************************************************/
uint8_t Get_Key(void) 
{
	if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_PIN))
	{
			return PRESS_KEY1;
	}	
	else if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT,GPIO_KEY2_PIN))
	{
			return PRESS_KEY2;
	}
	else if(!GPIO_ReadInputDataBit(GPIO_KEY3_PORT,GPIO_KEY3_PIN))
	{
			return PRESS_KEY3;
	}
	else if(!GPIO_ReadInputDataBit(GPIO_KEY4_PORT,GPIO_KEY4_PIN))
	{
			return PRESS_KEY4;
	}
  else
		return NO_KEY;
}

/*******************************************************************************
* Function Name  : KeyHandle
* Description    : The key response function
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void KeyHandle(void)
{
 	if(Key_Return & PRESS_KEY1)
 	{
 		if(Key_Return & KEY_LONG)
		{
			m_pro_commonCmd.head_part.cmd = CMD_RESET_MODULE;
			m_pro_commonCmd.head_part.sn = ++SN;
			m_pro_commonCmd.sum = CheckSum((uint8_t *)&m_pro_commonCmd, sizeof(pro_commonCmd));
			SendToUart((uint8_t *)&m_pro_commonCmd, sizeof(pro_commonCmd), 1);
			
			LED_RGB_Control(0,0,50);
			LED_RGB_Control(0,0,0);
			Key_Return = 0;
		}
 	}
 	if(Key_Return & PRESS_KEY2)
 	{
		if(Key_Return & KEY_LONG) 
		{
			m_m2w_setModule.config_info = 0x01;		//soft ap
			LED_RGB_Control(50,0,0);		
			wait_wifi_status = 1;
		}
		else if(Key_Return & KEY_UP) 
		{
			m_m2w_setModule.config_info = 0x02;		//air link
			LED_RGB_Control(0,50,0);
			wait_wifi_status = 1;
		}
		else
		{
			Key_Return = 0;
			return ;
		}
		
		m_m2w_setModule.head_part.sn = ++SN;
		m_m2w_setModule.sum = CheckSum((uint8_t *)&m_m2w_setModule, sizeof(m2w_setModule));
		SendToUart((uint8_t *)&m_m2w_setModule, sizeof(m2w_setModule), 1);
			
		delay_ms(500);
		Key_Return = 0;
	} 

 	if(Key_Return & PRESS_KEY3)
 	{
		if(Key_Return & KEY_LONG)
		{
			m_m2w_mcuStatus.status_r.alert_byte = 0x01;		//alert 1
			LED_RGB_Control(50,0,0);	
			LED_RGB_Control(0,0,0);	
		}
		else if(Key_Return & KEY_UP)
		{
			m_m2w_mcuStatus.status_r.fault_byte = 0x03;		//fault 1 and 2
			LED_RGB_Control(0,50,0);	
			LED_RGB_Control(0,0,0);	
		}
		else
		{
			Key_Return = 0;
			return ;
		}
	
		ReportStatus(REPORT_STATUS);
		m_m2w_mcuStatus.status_r.alert_byte = 0x00;			//clean the alert
		m_m2w_mcuStatus.status_r.fault_byte = 0x00;			//clean the fault
		delay_ms(500);
		Key_Return = 0;
	}		
	
	 if(Key_Return & PRESS_KEY4)
 	{
		if(Key_Return & KEY_LONG)
		{
			m_m2w_mcuStatus.status_r.alert_byte = 0x02;		//alert 2
			LED_RGB_Control(50,0,0);	
			LED_RGB_Control(0,0,0);	
		}
		else if(Key_Return & KEY_UP)
		{
			m_m2w_mcuStatus.status_r.fault_byte = 0x0C;		//fault 3 and 4
			LED_RGB_Control(0,50,0);	
			LED_RGB_Control(0,0,0);	
		}
		else
		{
			Key_Return = 0;
			return ;
		}
	
		ReportStatus(REPORT_STATUS);
		m_m2w_mcuStatus.status_r.alert_byte = 0x00;			//clean the alert
		m_m2w_mcuStatus.status_r.fault_byte = 0x00;			//clean the fault
		delay_ms(500);
		Key_Return = 0;
	}		
}