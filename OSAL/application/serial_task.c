/****************************************************************************************
 * 文件名  ：serial_task.c
 * 描述    ：系统串口通信任务
 * 开发平台：
 * 库版本  ：
 ***************************************************************************************/
#include "application.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "usart.h"
#include "led.h"
#include "delay.h"
#include "nrf24l01.h"
#include "adc.h"
#include "key.h"

uint8 Serial_TaskID;					//系统串口通信任务ID
uint8 NRF_Status = 0;					//nrf模块外部连接状态，0为未连接，1为连接上
uint8 Link_Status = 0;					//nrf模块通信连接状态，0为断线状态，1为在线
int16_t physical_chan[13];				//物理通道原始值，前5通道为模拟量，后8通道为数字开关量
int16_t logic_channel[16];				//逻辑通道值，16通道，但只使用前8通道，值范围1000~2000

/*********************************************************************
 * LOCAL FUNCTION PROTOTYPES
 */
/*********************************************************************
 * FUNCTIONS
 *********************************************************************/
//串口通信任务初始化
void Serial_Task_Init(uint8 task_id)
{
	Serial_TaskID = task_id;

	//串口配置初始化
	Usart_Init( COM1,921600,STOP_1_B,WROD_LEN_8B,PARITY_NO,HARD_NO );
	//Usart_Init( COM2,100000,STOP_2_B,WROD_LEN_9B,PARITY_EVEN,HARD_NO );

	osal_start_timerEx(Serial_TaskID,RE_CHECK_NRF,1000);		//1秒后才开始初始化NRF，等待供电稳定

	NRF_SPI_Init();
	LED_Init();
	Adc_Init();
	Key_Init();

	Usart_Puts(COM1,"Fucking running! \r\n");
}

//串口通信任务事件处理
uint16 Serial_Task_EventProcess(uint8 task_id,uint16 task_event)
{
	if ( task_event & SYS_EVENT_MSG )   	//判断系统消息事件
  	{
  		osal_sys_msg_t *MSGpkt;    			//定义一个指向接受系统消息结构体的指针
	    //从消息队列获取消息  
	    MSGpkt = (osal_sys_msg_t *)osal_msg_receive( task_id ); 
    
	    while ( MSGpkt )
	    {
	      	switch ( MSGpkt->hdr.event )  	//判断消息事件
	      	{
	          	case OSAL_PRINTF:
	          		break;

	        	default:
	          		break;
	      	}

	      	// Release the memory
	      	osal_msg_deallocate( (uint8 *)MSGpkt );

	      	// Next  获取下一个消息
	      	MSGpkt = (osal_sys_msg_t *)osal_msg_receive( task_id );
	    }

    	// return unprocessed events
    	return (task_event ^ SYS_EVENT_MSG);
  	}
  	
	if(task_event & READ_ADC)
	{
		int i;

		for(i=0;i<4;i++)
		{
			if(i<2)										//按照左手模式重新映射
				physical_chan[i+2] = Get_Adc_Average(i,10);
			else
				physical_chan[3-i] = Get_Adc_Average(i,10);

			if( abs(physical_chan[i]-2048)<50 )
				logic_channel[i] = 1500;
			else
			{
				logic_channel[i] = physical_chan[i]/4096.0*1000 + 1000;
				if(i!=2)
					logic_channel[i] = 2000 -  logic_channel[i] +1000;
			}
		}
		physical_chan[4] = Get_Adc_Average(8,10);		//电池电压模拟值

		//Usart_Printf(COM1,"physical: %d %d %d %d %d \t",physical_chan[0],physical_chan[1],physical_chan[2],physical_chan[3],physical_chan[4]);
		//Usart_Printf(COM1,"logic: %d %d %d %d %d\r\n",logic_channel[0],logic_channel[1],logic_channel[2],logic_channel[3],logic_channel[4]);

	  	if(NRF_Status == 1)
		{
			osal_memcpy(NRF_Tx_BUF,(uint8_t*)logic_channel,32);
			NRF_Tx_Fast(NRF_Tx_BUF,32);
		}
		
		return task_event ^ READ_ADC;
	}

	if(task_event & KEY_SCAN)
	{
		Key_Scan();
		Key_Deal();

		//Usart_Printf(COM1,"KeyValue : %x \r\n",(uint8_t)KeyValue);

	  	return task_event ^ KEY_SCAN;
	}

	if(task_event & NRF_UNLINK)
	{
		// Usart_Puts(COM1,"fucking\r\n");
		Link_Status = 0;

	  	return task_event ^ NRF_UNLINK;
	}

	if(task_event & RE_CHECK_NRF)
	{
		if( NRF_Check() == SUCCESS )
		{
			NRF_Status = 1;
			Usart_Puts(COM1,"Check nrf24l01 success !\r\n");

			NRF_TX_Mode();
			Usart_Puts(COM1,"NRF set tx mode !\r\n");
		}
		else
		{
			osal_start_timerEx(Serial_TaskID,RE_CHECK_NRF,1000);		//初始化NRF失败则1秒后重试
		}
		
	  	return task_event ^ RE_CHECK_NRF;
	}

	return 0;
}

