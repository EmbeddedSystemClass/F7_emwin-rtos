#include "use_app.h"
#include "DIALOG.h"
#include "EmWinHZFont.h"
#include "Freertos.h"
#include "task.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0            (GUI_ID_USER + 0x00)
#define ID_MULTIEDIT0            (GUI_ID_USER + 0x01)

//TOUCH����
//�����������ȼ�
#define CPU_TASK_PRIO			5
//�����ջ��С
#define CPU_STK_SIZE			512
//������
TaskHandle_t CPUTask_Handler;
//touch����
void cpu_task(void *pvParameters);

MULTIEDIT_HANDLE Show_Handle;
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _useappDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect,  NULL,    ID_MULTIEDIT0,  0, 0,470, 248,0,0x0,0},
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

void Cpu_TaskCreat(void)
{
	taskENTER_CRITICAL();           //�����ٽ���
	//������������
    xTaskCreate((TaskFunction_t )cpu_task,             
                (const char*    )"cpu_task",           
                (uint16_t       )CPU_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )CPU_TASK_PRIO,        
                (TaskHandle_t*  )&CPUTask_Handler);  
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

void cpu_task(void *pvParameters)
{
	char CPU_RunInfo[400];
	char Header_Buff[500];
	while(1)
	{
		MULTIEDIT_SetText(Show_Handle,0);
		memset(CPU_RunInfo,0,400); //��Ϣ����������

		vTaskList((char *)&CPU_RunInfo); //��ȡ��������ʱ����Ϣ

//		printf("---------------------------------------------------------\r\n");
//		printf("������      ����״̬      ���ȼ�      ʣ��ջ     �������\r\n");
//		printf("%s", CPU_RunInfo);
//		printf("---------------------------------------------------------\r\n");
//		MULTIEDIT_AddText(Show_Handle,CPU_RunInfo);
//		printf("---------------------------------------------------------\r\n");
		MULTIEDIT_AddText(Show_Handle,"---------------------------------------------------------\r\n");
		MULTIEDIT_AddText(Show_Handle,"������      ����״̬      ���ȼ�      ʣ��ջ     �������\r\n");
		MULTIEDIT_AddText(Show_Handle,"---------------------------------------------------------\r\n");
		MULTIEDIT_AddText(Show_Handle,CPU_RunInfo);
		MULTIEDIT_AddText(Show_Handle,"---------------------------------------------------------\r\n");
		memset(CPU_RunInfo,0,400); //��Ϣ����������

		vTaskGetRunTimeStats((char *)&CPU_RunInfo);

//		printf("������            ���м���            ʹ����\r\n");
//		printf("%s", CPU_RunInfo);
//		printf("-------------------------------------------------------\r\n\n");
		MULTIEDIT_AddText(Show_Handle,"������            ���м���            ʹ����\r\n");
		MULTIEDIT_AddText(Show_Handle, CPU_RunInfo);
		MULTIEDIT_AddText(Show_Handle,"-------------------------------------------------------\r\n\n");
		vTaskDelay(1000);		//��ʱ1000ms
	}
}
/*********************************************************************
*
*       _cbDialog
*/
static void _cbuseappDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
	  case WM_DELETE:
		   vTaskDelete(CPUTask_Handler); //ɾ����ʼ����
	  break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
	FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,2); //��ӹرհ�ť
	FRAMEWIN_AddMaxButton(hItem,FRAMEWIN_BUTTON_RIGHT,2);   //�����󻯰�ť
	FRAMEWIN_AddMinButton(hItem,FRAMEWIN_BUTTON_RIGHT,2);   //�����С����ť
	
	  
	FRAMEWIN_SetFont(hItem,&GUI_FontHZ16);
	FRAMEWIN_SetTextColor(hItem, GUI_BLACK);
	FRAMEWIN_SetTitleHeight(hItem,20);
	FRAMEWIN_SetText(hItem, "ʹ����");
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT0);
	MULTIEDIT_SetFont(hItem, &GUI_FontHZ12);
	MULTIEDIT_SetAutoScrollH(hItem,1);
    MULTIEDIT_SetAutoScrollV(hItem,1);
	MULTIEDIT_SetAutoScrollH(hItem,1);
    MULTIEDIT_SetAutoScrollV(hItem,1);
	MULTIEDIT_SetFocusable(hItem,0);
	Show_Handle=hItem;
	Cpu_TaskCreat();
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
	case WM_PAINT:
		GUI_Clear();
		GUI_SetBkColor(GUI_BLACK);
		break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_MULTIEDIT0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/

void CreateUseAppwin(void) 
{
  GUI_CreateDialogBox(_useappDialogCreate, GUI_COUNTOF(_useappDialogCreate), _cbuseappDialog, WM_HBKWIN, 0, 0);
}


