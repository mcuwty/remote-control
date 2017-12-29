#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"

#define ADC_CH0  	0  	//通道0	
#define ADC_CH1  	1  	//通道1
#define ADC_CH2  	2  	//通道2
#define ADC_CH3  	3  	//通道3
#define ADC_CH4  	4  	//通道4	
#define ADC_CH5  	5  	//通道5	
#define ADC_CH6  	6  	//通道6
#define ADC_CH7  	7  	//通道7
#define ADC_CH8  	8  	//通道8
#define ADC_CH9  	9  	//通道9
#define ADC_CH10  	10  //通道10	
#define ADC_CH11  	11  //通道11
#define ADC_CH12  	12  //通道12
#define ADC_CH13  	13  //通道13
#define ADC_CH14  	14  //通道14
#define ADC_CH15  	15  //通道15

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 
