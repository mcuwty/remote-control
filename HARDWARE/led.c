/****************************************************************************************
 * �ļ���  ��led.c
 * ����    ��led���� 
 * ����ƽ̨��STM32F103		
 * ��汾  ��ST3.5.0
 * ����    ����̩��
 ***************************************************************************************/
#include "led.h"	   
	    
//LED IO��ʼ��
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
