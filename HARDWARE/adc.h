#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"

#define ADC_CH0  	0  	//ͨ��0	
#define ADC_CH1  	1  	//ͨ��1
#define ADC_CH2  	2  	//ͨ��2
#define ADC_CH3  	3  	//ͨ��3
#define ADC_CH4  	4  	//ͨ��4	
#define ADC_CH5  	5  	//ͨ��5	
#define ADC_CH6  	6  	//ͨ��6
#define ADC_CH7  	7  	//ͨ��7
#define ADC_CH8  	8  	//ͨ��8
#define ADC_CH9  	9  	//ͨ��9
#define ADC_CH10  	10  //ͨ��10	
#define ADC_CH11  	11  //ͨ��11
#define ADC_CH12  	12  //ͨ��12
#define ADC_CH13  	13  //ͨ��13
#define ADC_CH14  	14  //ͨ��14
#define ADC_CH15  	15  //ͨ��15

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 
