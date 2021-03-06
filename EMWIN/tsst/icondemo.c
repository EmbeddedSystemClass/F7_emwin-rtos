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
#include "updateapp.h"
#define ID_ICONVIEW_0   (GUI_ID_USER + 0x01)
#define ID_TEXT1   		(GUI_ID_USER + 0x02)
#define ID_TEXT2   		(GUI_ID_USER + 0x03)
uint8_t Document_ICON=0;

WM_HWIN IconviewWin;    //ICONVIEW控件窗口
WM_HTIMER hTimer;
TEXT_Handle TimeText_Handle;
TEXT_Handle DataText_Handle;
//app图标描述结构体
typedef struct{
	const GUI_BITMAP 	*pBitmap;   //app图标
	const char			*pText;     //app图标名字
}BITMAP_ITEM;

//ICONVIEW显示的APP图标
static const BITMAP_ITEM BitmapItemTab1[]={
	{&bmswitch,		"开关"},
	{&bmdocuments,	"文件浏览"},
	{&bmHz_Update,	"字库更新"},
	{&bmpicture,	"图片"},
	{&bmuse,		"使用率"},
	{&bmcom,		"串口"},
	{&bmQRcode,		"二维码"},
	{&bmclock,		"时钟"},
	{&bmusb,		"USB"},
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

//桌面窗口WM_HBKWIN回调函数
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
//			GUI_DrawBitmap(&bmbackground,0,0);  //绘制背景图片
			displyjpeg((u8*)"0:BK/bk.jpg",0,0,	0,	1,1);
			break;
		case WM_NOTIFY_PARENT:
			Id=WM_GetId(pMsg->hWinSrc);
			NCode=pMsg->Data.v;
			switch(Id)
			{
				case ID_ICONVIEW_0:	//ICONVIEW0控件
					switch(NCode)	//通知代码
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							Iconview0_Sel=ICONVIEW_GetSel(pMsg->hWinSrc);
							switch(Iconview0_Sel)
							{
								case 0:		//APP0
										CreateFramewin();      //创建LEDAPP
									break;
								case 1:		//APP1
										CreateDocuments();    //创建文件管理APP
									break;
                               	case 2:		//APP2
									updateappTask(WM_HBKWIN); 
//									if(warnningTask("是否确认更新"))
//										HzFontupdataCreate();    //创建字库升级
									break;
                                case 3:		//APP3
                                    CreatePICTURE(1,WM_HBKWIN);    //创建图片
									break;
								case 4:		//APP3
                                    CreateUseAppwin();    //创建使用率
									break;
								case 5:	
									comAppwin() ;//创建串口
								break;
								case 6:	
									QRcodeapp();	//二维码	
								break;
								case 7:	
									App_Calendar();		//时钟						
								break;
								case 8:	
//									App_Calendar();		//USB						
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

//ICONVIEW演示例程
void iconviewdemo(void) 
{
	int i;
	WM_SetCallback(WM_HBKWIN,cb_BkWindow); //设置桌面窗口WM_HBKWIN的回调函数
	hTimer=WM_CreateTimer(WM_HBKWIN,0,10,0);
	DataText_Handle=TEXT_CreateEx(0,0,240,20,WM_HBKWIN, WM_CF_SHOW, 0, ID_TEXT1, NULL);
	TimeText_Handle=TEXT_CreateEx(240,0,240,20,WM_HBKWIN, WM_CF_SHOW, 0, ID_TEXT2, NULL);
	TEXT_SetFont(TimeText_Handle,&GUI_FontHZ16);
	TEXT_SetFont(DataText_Handle,&GUI_FontHZ16);
	//建立一个ICONVIEW作为主界面
	IconviewWin=ICONVIEW_CreateEx(	0,0,                    //左上角坐标
							480,272,                        //小工具的水平和垂直尺寸
							WM_HBKWIN,                      //父窗口为背景窗口
							WM_CF_SHOW|WM_CF_HASTRANS,      
							ICONVIEW_CF_AUTOSCROLLBAR_V,    //自动增加垂直滚动条
							ID_ICONVIEW_0,                  //小工具ID
							80,                            //图标的水平尺寸为100
							100);                           //图标的垂直尺寸为100
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

