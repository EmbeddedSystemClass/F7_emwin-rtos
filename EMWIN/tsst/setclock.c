#include "setclock.h"

#include "GUI.h"
#include "DIALOG.h"
#include "rtc.h"
#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"
#include "CALENDAR.h"
#include "EmWinHZFont.h"
#include "clockapp_usepic.h"

/*
*********************************************************************************************************
*                                        �궨��
*********************************************************************************************************
*/
#define ID_SPINBOX_0  (GUI_ID_USER + 0x01)
#define ID_SPINBOX_1  (GUI_ID_USER + 0x02)
#define ID_SPINBOX_2  (GUI_ID_USER + 0x03)
#define ID_SPINBOX_3  (GUI_ID_USER + 0x04)
#define ID_SPINBOX_4  (GUI_ID_USER + 0x05)
#define ID_SPINBOX_5  (GUI_ID_USER + 0x06)
#define ID_CALENDAR0  (GUI_ID_USER + 0x07)

/*
*********************************************************************************************************
*                                        ����
*********************************************************************************************************
*/
const char *apDays[] =
{
	"��",
	"��",
	"һ",
	"��",
	"��",
	"��",
	"��",
	"��",
};

const char *apMonths[]=
{
	"1��",
	"2��",
	"3��",
	"4��",
	"5��",
	"6��",
	"7��",
	"8��",
	"9��",
	"10��",
	"11��",
	"12��",
};


/*
*********************************************************************************************************
*	                               �Ի���ؼ��б�
*********************************************************************************************************
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateSetTimeAlarm[] = {
    { WINDOW_CreateIndirect,  "Time Settings",        	0,                     0,  0,  480,272,0,0},
    { TEXT_CreateIndirect,      "ʱ������",          GUI_ID_TEXT0,            68, 14, 73, 20, 0,0},
    { TEXT_CreateIndirect,      "��������",          GUI_ID_TEXT1,            188,14, 73, 20, 0,0},
    { CHECKBOX_CreateIndirect,  "����ʱ������",  	 GUI_ID_CHECK0,           48,162,210,24, 0,0},
	{ CHECKBOX_CreateIndirect,  "������������",   	 GUI_ID_CHECK1,           168,162,210,24, 0,0},
	{ CHECKBOX_CreateIndirect,  "��������������",    GUI_ID_CHECK2,           300,162,210,24, 0,0},
    { TEXT_CreateIndirect,      "ʱ:",               GUI_ID_TEXT2,            24, 24, 29, 20, 0,0},
    { TEXT_CreateIndirect,      "��:",               GUI_ID_TEXT3,            24, 63+15,29, 20, 0,0},
    { TEXT_CreateIndirect,      "��:",               GUI_ID_TEXT4,            24, 93+30,29, 20, 0,0},
	
	{ BUTTON_CreateIndirect, "Button", GUI_ID_BUTTON0, 120, 24, 100, 45, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", GUI_ID_BUTTON1, 300, 24, 100, 45, 0, 0x0, 0 },

	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_0, 48, 33, 130, 35, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_1, 48, 62 + 15, 130, 35, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_2, 48, 90 + 30, 130, 35, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_3, 168, 33, 130, 35, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_4, 168, 63 + 15, 130, 35, 0, 0x0, 0 },
	{ SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_5, 168, 93 + 30, 130, 35, 0, 0x0, 0 },
};
/*
*********************************************************************************************************
*	�� �� ��: bsp_CalcWeek
*	����˵��: �������ڼ������ڼ�
*	��    ��: _year _mon _day  ������  (����2�ֽ��������º������ֽ�������
*	�� �� ֵ: �ܼ� ��1-7�� 7��ʾ����
*********************************************************************************************************
*/
uint8_t RTC_CalcWeek(uint16_t _year, uint8_t _mon, uint8_t _day)
{
	/*
	���գ�Zeller����ʽ
		��ʷ�ϵ�ĳһ�������ڼ���δ����ĳһ�������ڼ�������������⣬�кܶ���㹫ʽ������ͨ�ü��㹫ʽ��
	һЩ�ֶμ��㹫ʽ�����������������ǲ��գ�Zeller����ʽ��
	    ��w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1

		��ʽ�еķ��ź������£�
	     w�����ڣ�
	     c����ĸ�2λ��������-1
	     y���꣨��λ������
	     m���£�m���ڵ���3��С�ڵ���14�����ڲ��չ�ʽ�У�ĳ���1��2��Ҫ������һ���13��14�������㣬
	  	    ����2003��1��1��Ҫ����2002���13��1�������㣩��
	     d���գ�
	     [ ]����ȡ������ֻҪ�������֡�

	    �������W����7�������Ǽ��������ڼ������������0����Ϊ�����ա�
        �������Ǹ�������������������Ҫ���⴦��
            �������ܰ�ϰ�ߵ������ĸ�����������ֻ�ܰ������е������Ķ������ࡣΪ�˷���
        ���㣬���ǿ��Ը�������һ��7����������ʹ����Ϊһ��������Ȼ����������

		��2049��10��1�գ�100������죩Ϊ�����ò��գ�Zeller����ʽ���м��㣬�������£�
		���գ�Zeller����ʽ��w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1
		=49+[49/4]+[20/4]-2��20+[26�� (10+1)/10]+1-1
		=49+[12.25]+5-40+[28.6]
		=49+12+5-40+28
		=54 (����7��5)
		��2049��10��1�գ�100������죩������5��
	*/
	uint8_t y, c, m, d;
	int16_t w;

	if (_mon >= 3)
	{
		m = _mon;
		y = _year % 100;
		c = _year / 100;
		d = _day;
	}
	else	/* ĳ���1��2��Ҫ������һ���13��14�������� */
	{
		m = _mon + 12;
		y = (_year - 1) % 100;
		c = (_year - 1) / 100;
		d = _day;
	}

	w = y + y / 4 +  c / 4 - 2 * c + ((uint16_t)26*(m+1))/10 + d - 1;
	if (w == 0)
	{
		w = 7;	/* ��ʾ���� */
	}
	else if (w < 0)	/* ���w�Ǹ����������������ʽ��ͬ */
	{
		w = 7 - (-w) % 7;
	}
	else
	{
		w = w % 7;
	}
	
	/* modified by eric2013 -- 2016-12-25 */
	if (w == 0)
	{
		w = 7;	/* ��ʾ���� */
	}
	
	return w;
}
/*
*********************************************************************************************************
*	�� �� ��: InitDialogSetTimeAlarm
*	����˵��: �ص�������ʼ����Ϣ 
*	��    ��: pMsg  ��Ϣָ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void InitDialogSetTimeAlarm(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	
	/* �����ؼ���ʼ�� */
	CALENDAR_SetDefaultSize(CALENDAR_SI_HEADER, 35 );
	CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_X, 40 );
	CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_Y, 28 );

	CALENDAR_SetDefaultFont(CALENDAR_FI_CONTENT, &GUI_FontHZ16);
	CALENDAR_SetDefaultFont(CALENDAR_FI_HEADER, &GUI_FontHZ16); 
	CALENDAR_SetDefaultBkColor(CALENDAR_CI_WEEKDAY, 0xFF00FF);
	
	CALENDAR_SetDefaultDays(apDays);
	CALENDAR_SetDefaultMonths(apMonths);

	HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
	CALENDAR_Create(hWin, 
	                 270, 
	                 22, 
	                 RTC_DateStruct.Year+2000, 
	                 RTC_DateStruct.Month, 
					 RTC_DateStruct.Date,
					 2,
					 ID_CALENDAR0, 
					 WM_CF_SHOW);

	/* �ı��ؼ���ʼ�� */
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0), &GUI_FontHZ16);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1), &GUI_FontHZ16);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2), &GUI_FontHZ16);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3), &GUI_FontHZ16);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4), &GUI_FontHZ16);

	/* ��ѡ���ʼ�� */
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK0), "����ʱ������");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK0), &GUI_FontHZ16);
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK1), "������������");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK1), &GUI_FontHZ16);
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK2), "��������������");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK2), &GUI_FontHZ16);
	
	/* ��ť��ʼ�� */
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0), &GUI_FontHZ16);
    BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON0), "ȷ��");
	BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1), &GUI_FontHZ16);
    BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON1), "ȡ��");
	
	/* �༭���ʼ�� */
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_0)), GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_1)), GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_2)), GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_3)), GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_4)), GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetTextAlign(SPINBOX_GetEditHandle(WM_GetDialogItem(hWin,ID_SPINBOX_5)), GUI_TA_HCENTER | GUI_TA_VCENTER);

	/* SPINBOX��ʼ�� */
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_0), SPINBOX_EDGE_CENTER);
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_1), SPINBOX_EDGE_CENTER);
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_2), SPINBOX_EDGE_CENTER);
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_3), SPINBOX_EDGE_CENTER);
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_4), SPINBOX_EDGE_CENTER);
	SPINBOX_SetEdge(WM_GetDialogItem(hWin,ID_SPINBOX_5), SPINBOX_EDGE_CENTER);
	
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_0), &GUI_FontHZ16);
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_1), &GUI_FontHZ16);
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_2), &GUI_FontHZ16);
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_3), &GUI_FontHZ16);
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_4), &GUI_FontHZ16);
	SPINBOX_SetFont(WM_GetDialogItem(hWin,ID_SPINBOX_5), &GUI_FontHZ16);
	
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_0), 0, 23);  /* Сʱ */
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_1), 0, 59);  /* ���� */
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_2), 0, 59);  /* ���� */
	
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_3), 0, 23);  /* ����Сʱ */
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_4), 0, 59);  /* ���ӷ��� */
	SPINBOX_SetRange(WM_GetDialogItem(hWin,ID_SPINBOX_5), 0, 59);  /* �������� */
	
	HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
	HAL_RTC_GetAlarm(&RTC_Handler,&RTC_AlarmStruct,RTC_ALARM_A,RTC_FORMAT_BIN);
	
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_0), RTC_TimeStruct.Hours);   /* ʱ */								   
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_1), RTC_TimeStruct.Minutes); /* �� */							   
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_2), RTC_TimeStruct.Seconds); /* �� */
	
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_3), RTC_AlarmStruct.AlarmTime.Hours);   /* ����ʱ */			 
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_4), RTC_AlarmStruct.AlarmTime.Minutes); /* ���ӷ� */				 
	SPINBOX_SetValue(WM_GetDialogItem(hWin,ID_SPINBOX_5), RTC_AlarmStruct.AlarmTime.Seconds); /* ������ */
}

/*
*********************************************************************************************************
*	�� �� ��: _cbCallbackSetTimeAlarm
*	����˵��: �ص����� 
*	��    ��: pMsg  ��Ϣָ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void _cbCallbackSetTimeAlarm(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
	CALENDAR_DATE CALENDAR_Date;
	
    switch (pMsg->MsgId) 
    {
        case WM_INIT_DIALOG:
            InitDialogSetTimeAlarm(pMsg);
            break;
		
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
				
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
			
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
				/* ���ȷ�� */
				case GUI_ID_BUTTON0:
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						
						case WM_NOTIFICATION_RELEASED:
							
							/* �Ƿ񱣴�ʱ������ */
							if(CHECKBOX_GetState(WM_GetDialogItem(hWin,GUI_ID_CHECK0)) == 1)
							{
								RTC_TimeStruct.TimeFormat     = RTC_HOURFORMAT12_AM;
								RTC_TimeStruct.Hours   = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_0));
								RTC_TimeStruct.Minutes = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_1));
								RTC_TimeStruct.Seconds = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_2));
								RTC_Set_Time(RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds,RTC_HOURFORMAT12_PM);
							}
							
							/* �Ƿ񱣴�����ʱ������ */
							if(CHECKBOX_GetState(WM_GetDialogItem(hWin,GUI_ID_CHECK1)) == 1)
							{
								/* ���� Alarm A */
//								RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
//								RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
//								RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_3));
//								RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_4));
//								RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = SPINBOX_GetValue(WM_GetDialogItem(hWin,ID_SPINBOX_5));
//				
//								/* ���� Alarm A */
//								RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
//								RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
//								RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

//								/* ���� RTC Alarm A �Ĵ��� */
//								/* ������Ҫ��������Լ����Ƿ����óɹ���״̬��� */
//								RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);

//								/* ʹ�� RTC Alarm A �ж� */
//								RTC_ITConfig(RTC_IT_ALRA, ENABLE);

//								/* ʹ�� alarm  A */
//								RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
							}
							
							/* �Ƿ񱣴����������� */
							if(CHECKBOX_GetState(WM_GetDialogItem(hWin,GUI_ID_CHECK2)) == 1)
							{
								CALENDAR_GetSel(WM_GetDialogItem(hWin,GUI_ID_CALENDAR0), &CALENDAR_Date);
								
								RTC_DateStruct.Year = CALENDAR_Date.Year%100;
								RTC_DateStruct.Month = CALENDAR_Date.Month;
								RTC_DateStruct.Date = CALENDAR_Date.Day;
								RTC_DateStruct.WeekDay = RTC_CalcWeek(RTC_DateStruct.Year, 
																			 RTC_DateStruct.Month,
																			 RTC_DateStruct.Date);
								RTC_Set_Date(RTC_DateStruct.Year, 
											 RTC_DateStruct.Month,
											 RTC_DateStruct.Date,
											 RTC_DateStruct.WeekDay);

								//CALENDAR_SetDate(WM_GetDialogItem(hWin,GUI_ID_CALENDAR0), &CALENDAR_Date);
							}
							
						    GUI_EndDialog(hWin, 0);
							break;
					}
					break;
				
				/* ���ȡ����ť */
				case GUI_ID_BUTTON1:
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						
						case WM_NOTIFICATION_RELEASED:
							GUI_EndDialog(hWin, 0);
							break;
					}
					break;
            }
            break;
			
        default:
            WM_DefaultProc(pMsg);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: App_CalendarChild
*	����˵��: ���ӣ�ʱ�䣬�������öԻ��� 
*	��    ��: hWin �����ھ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void App_CalendarChild(WM_HWIN hWin) 
{
	WM_HWIN hWinAlarm; 
    
	hWinAlarm = GUI_CreateDialogBox(_aDialogCreateSetTimeAlarm, 
	                                GUI_COUNTOF(_aDialogCreateSetTimeAlarm), 
	                                &_cbCallbackSetTimeAlarm, 
	                                hWin, 
	                                0, 
	                                0);
	
	/* ����Ϊģ̬���� */
	WM_MakeModal(hWinAlarm);
}



