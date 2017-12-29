/****************************************************************************************
 * 文件名  ：key.c
 * 描述    ：按键检测驱动 
 * 开发平台：STM32F103		
 * 库版本  ：ST3.5.0
 * 作者    ：吴泰月
 ***************************************************************************************/
#include "key.h"

uint8_t KeyValue = 0;				//按键置位值

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//禁用JTAG-DP，释放PB3/PB4作为IO口，同时要使能复用时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_8 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//按键扫描，按照位定义保存
void Key_Scan(void)
{
	if(KEY_1_IO)
		KeyValue |= KEY_1_MASK;
	else
		KeyValue &= ~KEY_1_MASK;

	if(KEY_2_IO)
		KeyValue |= KEY_2_MASK;
	else
		KeyValue &= ~KEY_2_MASK;
	
	if(KEY_3_IO)
		KeyValue |= KEY_3_MASK;
	else
		KeyValue &= ~KEY_3_MASK;
	
	if(KEY_4_IO)
		KeyValue |= KEY_4_MASK;
	else
		KeyValue &= ~KEY_4_MASK;
	
	if(KEY_5_IO)
		KeyValue |= KEY_5_MASK;
	else
		KeyValue &= ~KEY_5_MASK;
	
	if(KEY_6_IO)
		KeyValue |= KEY_6_MASK;
	else
		KeyValue &= ~KEY_6_MASK;
	
	if(KEY_7_IO)
		KeyValue |= KEY_7_MASK;
	else
		KeyValue &= ~KEY_7_MASK;
	
	if(KEY_8_IO)
		KeyValue |= KEY_8_MASK;
	else
		KeyValue &= ~KEY_8_MASK;

	KeyValue = ~KeyValue;			//取反，置位则代表按下
}

void Key_Deal(void)
{
	if(KeyValue & KEY_7_MASK && KeyValue & KEY_8_MASK)		//按键7/8同时按下
	{
		logic_channel[4] = 2000;							//通道5设置为2000
	}
	else if(KeyValue & KEY_1_MASK)							//只有按键1按下
		logic_channel[4] = 1000;
	else if(KeyValue & KEY_2_MASK)							//只有按键2按下
		logic_channel[4] = 1500;
}

