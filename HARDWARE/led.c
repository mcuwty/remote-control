/****************************************************************************************
 * 文件名  ：led.c
 * 描述    ：led驱动 
 * 开发平台：STM32F103		
 * 库版本  ：ST3.5.0
 * 作者    ：吴泰月
 ***************************************************************************************/
#include "led.h"	   
	    
//LED IO初始化
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
	LED_TX = 0;
	LED_RX = 0;
}
