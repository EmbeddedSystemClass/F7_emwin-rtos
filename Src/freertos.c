/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "gt9147.h"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "limits.h"
#include "GUI.h"
#include "WM.h"
#include "led_beep.h"
#include "DIALOG.h"
#include "icondemo.h"
#include "Hzfontupdata.h"

#include "pngdisplay.h"
#include "jpegdisplay.h"
#include "gifdisplay.h"
#include "bmpdisplay.h"
#include "picture_app.h"
#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define START_TASK_PRIO			1
//�����ջ��С	
#define START_STK_SIZE 			128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO			2
//�����ջ��С
#define TOUCH_STK_SIZE			512
//������
TaskHandle_t TouchTask_Handler;
//touch����
void touch_task(void *pvParameters);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 			3
//�����ջ��С
#define LED0_STK_SIZE			512
//������
TaskHandle_t Led0Task_Handler;
//led0����
void led0_task(void *pvParameters);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO		4
//�����ջ��С
#define EMWINDEMO_STK_SIZE		2048
//������
TaskHandle_t EmwindemoTask_Handler;
//emwindemo_task����
void emwindemo_task(void *pvParameters);

extern USBH_HandleTypeDef  hUSBHost;

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  
//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������                
    vTaskStartScheduler();  
}


//��ʼ����������
void start_task(void *pvParameters)
{
	__HAL_RCC_CRC_CLK_ENABLE();		//ʹ��CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();  					//STemWin��ʼ��
	WM_MULTIBUF_Enable(1);  		//����STemWin�໺��,RGB�����ܻ��õ�
    taskENTER_CRITICAL();           //�����ٽ���
	//������������
    xTaskCreate((TaskFunction_t )touch_task,             
                (const char*    )"touch_task",           
                (uint16_t       )TOUCH_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TOUCH_TASK_PRIO,        
                (TaskHandle_t*  )&TouchTask_Handler);   	
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,             
                (const char*    )"led0_task",           
                (uint16_t       )LED0_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )LED0_TASK_PRIO,        
                (TaskHandle_t*  )&Led0Task_Handler);  
    //����EMWIN Demo����
    xTaskCreate((TaskFunction_t )emwindemo_task,             
                (const char*    )"emwindemo_task",           
                (uint16_t       )EMWINDEMO_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EMWINDEMO_TASK_PRIO,        
                (TaskHandle_t*  )&EmwindemoTask_Handler);   				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}


//EMWINDEMO����
void emwindemo_task(void *pvParameters)
{
//	//����Ƥ��
//	GUI_CURSOR_Show();
	iconviewdemo();
//	jpegdisplay_demo();
//	gifdisplay_demo();
//	pngdisplay_demo();
	while(1)
	{	
		GUI_Delay(100);
	}
}

//���������������
void touch_task(void *pvParameters)
{
	while(1)
	{
		
		GUI_TOUCH_Exec();
//		USBH_Process(&hUSBHost);	
		vTaskDelay(5);		//��ʱ5ms
	}
}

//LED0����
void led0_task(void *p_arg)
{
	uint8_t CPU_RunInfo[400];
	GUI_ALLOC_DATATYPE k;
	GUI_ALLOC_INFO info;
	while(1)
	{
		GUI_ALLOC_GetMemInfo(&info);
		printf("TotalBytes=%ld,UsedBytes=%ld\r\n",info.TotalBytes,info.UsedBytes);
//		k=GUI_ALLOC_GetNumUsedBytes();
//		printf("UsedBytes=%ld\r\n",k);
//		memset(CPU_RunInfo,0,400); //��Ϣ����������

//		vTaskList((char *)&CPU_RunInfo); //��ȡ��������ʱ����Ϣ

//		printf("---------------------------------------------------------\r\n");
//		printf("������      ����״̬      ���ȼ�      ʣ��ջ     �������\r\n");
//		printf("%s", CPU_RunInfo);
//		printf("---------------------------------------------------------\r\n");

//		memset(CPU_RunInfo,0,400); //��Ϣ����������

//		vTaskGetRunTimeStats((char *)&CPU_RunInfo);

//		printf("������            ���м���            ʹ����\r\n");
//		printf("%s", CPU_RunInfo);
//		printf("-------------------------------------------------------\r\n\n");

		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		vTaskDelay(1000);		//��ʱ1000ms
	}
}
