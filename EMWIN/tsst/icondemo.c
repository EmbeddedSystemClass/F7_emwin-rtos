#include "icondemo.h"
#include "iconbmp.h"
#include "DIALOG.h"
#include "FRAMEWIN.h"
#include "led_beep.h"
#include "document.h"
#include "EmWinHZFont.h"
#include "MESSAGEBOX.h"
#include "Hzfontupdata.h"
#include "filewindow.h"
#include "picture_app.h"
#include "jpegdisplay.h"
#include "use_app.h"
#include "keypad.h"
#include "comapp.h"
#include "qrcodeapp.h"
#include "rtc.h"
#include "clockapp.h"
#include "warndialog.h"

#define ID_ICONVIEW_0   (GUI_ID_USER + 0x01)
#define ID_TEXT1   		(GUI_ID_USER + 0x02)
#define ID_TEXT2   		(GUI_ID_USER + 0x03)
uint8_t Document_ICON=0;

WM_HWIN IconviewWin;    //ICONVIEW�ؼ�����
WM_HTIMER hTimer;
TEXT_Handle TimeText_Handle;
TEXT_Handle DataText_Handle;
//appͼ�������ṹ��
typedef struct{
	const GUI_BITMAP 	*pBitmap;   //appͼ��
	const char			*pText;     //appͼ������
}BITMAP_ITEM;

//ICONVIEW��ʾ��APPͼ��
static const BITMAP_ITEM BitmapItemTab1[]={
	{&bmswitch,		"����"},
	{&bmdocuments,	"�ļ����"},
	{&bmHz_Update,	"�ֿ����"},
	{&bmpicture,	"ͼƬ"},
	{&bmuse,		"ʹ����"},
	{&bmcom,		"����"},
	{&bmQRcode,		"��ά��"},
	{&bmclock,		"ʱ��"},
//	{&bmdocument,	"Cument"},
//	{&bmfolder,		"Folder"},
//	{&bmmail,		"Mail"},
//	{&bmpaint,		"Paint"},
//	{&bmpin,		"Pin"},
//	{&bmsettings,	"Set"},
//	{&bmtools,		"Tool"},
//	{&bmturntable,	"TurnTab"},
//	{&bmvideo,		"Video"},
//	{&bmwallet,		"Wallet"},
//	{&bmlightbulb,	"Light"},
//	{&bmstar,		"Star"},
};

//���洰��WM_HBKWIN�ص�����
void cb_BkWindow(WM_MESSAGE *pMsg)
{
	int Id;
	int NCode;
	static int Iconview0_Sel;
	char tbuf[40];
	switch(pMsg->MsgId)
	{
		case WM_TIMER:
			HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
			sprintf((char*)tbuf,"Date:20%02d-%02d-%02d Week:%d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date,RTC_DateStruct.WeekDay); 
//			printf("%s\r\n",tbuf);
			TEXT_SetText(DataText_Handle,tbuf);
			HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
			sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
			TEXT_SetText(TimeText_Handle,tbuf);
//			printf("%s\r\n",tbuf);
			WM_RestartTimer(hTimer,1000);
			break;
		case WM_PAINT:
            GUI_SetBkColor(GUI_BLACK);
            GUI_Clear();                        
//			GUI_DrawBitmap(&bmbackground,0,0);  //���Ʊ���ͼƬ
			displyjpeg((u8*)"0:BK/bk.jpg",0,0,	0,	1,1);
			break;
		case WM_NOTIFY_PARENT:
			Id=WM_GetId(pMsg->hWinSrc);
			NCode=pMsg->Data.v;
			switch(Id)
			{
				case ID_ICONVIEW_0:	//ICONVIEW0�ؼ�
					switch(NCode)	//֪ͨ����
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							Iconview0_Sel=ICONVIEW_GetSel(pMsg->hWinSrc);
							switch(Iconview0_Sel)
							{
								case 0:		//APP0
										CreateFramewin();      //����LEDAPP
									break;
								case 1:		//APP1
										CreateDocuments();    //�����ļ�����APP
									break;
                               	case 2:		//APP2
									if(warnningTask("�Ƿ�ȷ�ϸ���"))
										HzFontupdataCreate();    //�����ֿ�����
									break;
                                case 3:		//APP3
//                                    CreatePICTURE();    //����ͼƬ
									break;
								case 4:		//APP3
                                    CreateUseAppwin();    //����ʹ����
									break;
								case 5:	
									comAppwin() ;//��������
								break;
								case 6:	
									QRcodeapp();		
								break;
								case 7:	
//									CreateClockAPP();	
									App_Calendar();								
								break;
								default:break;
							}
							break;
						case WM_NOTIFICATION_SEL_CHANGED:
							break;	
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;		
	}
	
}

//ICONVIEW��ʾ����
void iconviewdemo(void) 
{
	int i;
	WM_SetCallback(WM_HBKWIN,cb_BkWindow); //�������洰��WM_HBKWIN�Ļص�����
	hTimer=WM_CreateTimer(WM_HBKWIN,0,10,0);
	DataText_Handle=TEXT_CreateEx(0,0,240,20,WM_HBKWIN, WM_CF_SHOW, 0, ID_TEXT1, NULL);
	TimeText_Handle=TEXT_CreateEx(240,0,240,20,WM_HBKWIN, WM_CF_SHOW, 0, ID_TEXT2, NULL);
	TEXT_SetFont(TimeText_Handle,&GUI_FontHZ16);
	TEXT_SetFont(DataText_Handle,&GUI_FontHZ16);
	//����һ��ICONVIEW��Ϊ������
	IconviewWin=ICONVIEW_CreateEx(	0,0,                    //���Ͻ�����
							480,272,                        //С���ߵ�ˮƽ�ʹ�ֱ�ߴ�
							WM_HBKWIN,                      //������Ϊ��������
							WM_CF_SHOW|WM_CF_HASTRANS,      
							ICONVIEW_CF_AUTOSCROLLBAR_V,    //�Զ����Ӵ�ֱ������
							ID_ICONVIEW_0,                  //С����ID
							80,                            //ͼ���ˮƽ�ߴ�Ϊ100
							100);                           //ͼ��Ĵ�ֱ�ߴ�Ϊ100
	ICONVIEW_SetFont(IconviewWin,&GUI_FontHZ16);
	ICONVIEW_SetBkColor(IconviewWin,ICONVIEW_CI_SEL,GUI_WHITE|0X70000000);
	ICONVIEW_SetSpace(IconviewWin,GUI_COORD_X,15);
	ICONVIEW_SetSpace(IconviewWin,GUI_COORD_Y,15);
	ICONVIEW_SetIconAlign(IconviewWin,ICONVIEW_IA_HCENTER|ICONVIEW_IA_VCENTER);
	for(i=0;i<(GUI_COUNTOF(BitmapItemTab1));i++)
	{
		ICONVIEW_AddBitmapItem(IconviewWin,BitmapItemTab1[i].pBitmap,BitmapItemTab1[i].pText);
	}
}

