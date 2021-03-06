/****************************************************************************************
 * 文件名  ：osal_main.c
 * 描述    ：osal操作系统运行主函数，添加任务在此文件中添加
 * 开发平台：
 * 库版本  ：
 ***************************************************************************************/
#include "application.h"

/******************************************************************************
 * @fn      main
 *
 * @brief   
 *
 * @param   
 *
 * @return
 *****************************************************************************/
int main(void)
{    
	//系统硬件、外设等初始化
	
	//禁止中断
    HAL_DISABLE_INTERRUPTS();

    //osal操作系统初始化
    osal_init_system();

	//添加任务
	osal_add_Task(Serial_Task_Init,Serial_Task_EventProcess,1);	
	//添加的任务统一进行初始化
	osal_Task_init();

	osal_mem_kick();

	//允许中断
	HAL_ENABLE_INTERRUPTS();	

	//设置初始任务事件，上电就需要自动轮询的任务事件可在此添加
	osal_start_reload_timer( Serial_TaskID, READ_ADC, 20 );
	osal_start_reload_timer( Serial_TaskID, KEY_SCAN, 15 );

	//启动osal系统，不会再返回
	osal_start_system();
}
