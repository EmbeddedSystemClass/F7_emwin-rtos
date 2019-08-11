#include "picture_app.h"

#include "pngdisplay.h"
#include "jpegdisplay.h"
#include "gifdisplay.h"
#include "bmpdisplay.h"
#include "EmWinHZFont.h"
#include "DIALOG.h"
#include "document.h"
#include "diskio.h"
#include "ff.h"
#include "warndialog.h"
#define ID_WINDOW_0             (GUI_ID_USER + 0x01)
#define ID_BUTTON_0             (GUI_ID_USER + 0x02)
#define ID_BUTTON_1             (GUI_ID_USER + 0x03)
#define ID_BUTTON_2             (GUI_ID_USER + 0x04)
#define ID_TEXT_0            	(GUI_ID_USER + 0x05)


WM_HWIN Picture_Window;
char *Picture_Path;
uint32_t *picoffsettbl;	//����offset������  
uint8_t PictureShoe_Mode=0;
uint8_t *pname;			//��·�����ļ���
uint16_t totwavnum; 		//�����ļ�����
uint16_t curindex;		//��ǰ����	
extern GUI_CONST_STORAGE GUI_BITMAP bmright;
extern GUI_CONST_STORAGE GUI_BITMAP bmreturn;
extern GUI_CONST_STORAGE GUI_BITMAP bmleft;
extern char Now_Path[300];
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//�õ�path·����,Ŀ���ļ����ܸ���
//path:·��		    
//����ֵ:����Ч�ļ���
u16 picture_get_tnum(u8 *path)
{	  
	u8 res;
	u16 rval=0;
 	DIR tdir;	 		//��ʱĿ¼
	FILINFO* tfileinfo;	//��ʱ�ļ���Ϣ	 	
	tfileinfo=(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));//�����ڴ�
    res=f_opendir(&tdir,(const TCHAR*)path); //��Ŀ¼ 
	if(res==FR_OK&&tfileinfo)
	{
		while(1)//��ѯ�ܵ���Ч�ļ���
		{
	        res=f_readdir(&tdir,tfileinfo);       			//��ȡĿ¼�µ�һ���ļ�
	        if(res!=FR_OK||tfileinfo->fname[0]==0)break;	//������/��ĩβ��,�˳�	 		 
			res=f_typetell((u8*)tfileinfo->fname);	
			if((res&0XF0)==0X50)//ȡ����λ,�����ǲ���ͼƬ�ļ�	
			{
				rval++;//��Ч�ļ�������1
			}	    
		}  
	}  
	myfree(SRAMIN,tfileinfo);//�ͷ��ڴ�
	return rval;
}

uint8_t get_picture(void)
{
	u8 res;
 	DIR wavdir;	 		//Ŀ¼
	FILINFO *picfileinfo;//�ļ���Ϣ 
	u32 temp;  
	while(f_opendir(&wavdir,"0:PICTURE"))//�������ļ���
 	{	    
		return 1;	  
	} 									  
	totwavnum=picture_get_tnum("0:PICTURE"); //�õ�����Ч�ļ���
  	while(totwavnum==NULL)//�����ļ�����Ϊ0		
 	{	    
		return 2;		  
	}										   
	picfileinfo=(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));	//�����ڴ�
 	picoffsettbl=mymalloc(SRAMIN,4*totwavnum);				//����4*totwavnum���ֽڵ��ڴ�,���ڴ�������ļ�off block����
 	while(!picfileinfo||!picoffsettbl)//�ڴ�������
 	{	    
		return 3;			
	} 	 
 	//��¼����
    res=f_opendir(&wavdir,"0:PICTURE"); //��Ŀ¼
	if(res==FR_OK)
	{
		curindex=0;//��ǰ����Ϊ0
		while(1)//ȫ����ѯһ��
		{						
			temp=wavdir.dptr;								//��¼��ǰindex 
	        res=f_readdir(&wavdir,picfileinfo);       		//��ȡĿ¼�µ�һ���ļ�
	        if(res!=FR_OK||picfileinfo->fname[0]==0)break;	//������/��ĩβ��,�˳� 		 
			res=f_typetell((u8*)picfileinfo->fname);	
			if((res&0XF0)==0X50)//ȡ����λ,�����ǲ���ͼƬ�ļ�	
			{
				picoffsettbl[curindex]=temp;//��¼����
				curindex++;
			}	    
		} 
	}
	curindex=0;
	myfree(SRAMIN,picfileinfo);			//�ͷ��ڴ�
	return 0;
}

/*********************************************************************

*	�� �� ��: show_picture
*	����˵��: ��ʾͼƬ
*	��    ��: mode:1������ͼƬapp��0�����ļ��д�ͼƬ
*	�� �� ֵ: ��
*/
void show_picture(uint8_t mode)
{
	u8 res;
 	DIR wavdir;	 		//Ŀ¼
	FILINFO *picfileinfo;//�ļ���Ϣ 	
	pname=mymalloc(SRAMIN,FF_MAX_LFN*2+1);					//Ϊ��·�����ļ��������ڴ�	
   	picfileinfo=(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));	//�����ڴ�
	memset(pname,0,FF_MAX_LFN*2+1);
	if(PictureShoe_Mode==1)
	{
		res=f_opendir(&wavdir,(const TCHAR*)"0:PICTURE"); 	//��Ŀ¼
		if(res==FR_OK)//�򿪳ɹ�
		{	
			dir_sdi(&wavdir,picoffsettbl[curindex]);				//�ı䵱ǰĿ¼����	   
			res=f_readdir(&wavdir,picfileinfo);       				//��ȡĿ¼�µ�һ���ļ�
	//        if(res!=FR_OK||picfileinfo->fname[0]==0)break;			//������/��ĩβ��,�˳�	
			if (picfileinfo->fattrib & AM_ARC)
			{
				res=f_typetell((u8*)picfileinfo->fname);
				strcpy((char*)pname,"0:PICTURE/");						//����·��(Ŀ¼)
				strcat((char*)pname,(const char*)picfileinfo->fname);	//���ļ������ں���
			}
		} 
	}
	else
	{
		res=f_typetell((uint8_t*)Now_Path);
		memcpy(pname,Now_Path,strlen(Now_Path));
	}
	switch(res)//"BMP","JPG","JPEG","GIF"
	{
		case 0x50:
			dispbmpex(pname,1,0,0,1,1);
			break;
		case 0x51:
		case 0x52:
			displayjpegex(pname,1,0,0,1,1);
			break;
		case 0x53:
			
			break;
		case 0x54:
			displaypngex((char*)pname,1,0,0);
			break;
	}
	myfree(SRAMIN,picfileinfo);			//�ͷ��ڴ�			    
	myfree(SRAMIN,pname);				//�ͷ��ڴ�			    	 
} 

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _picDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 480, 272, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 10, 105, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 418, 107, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 422, 227, 50, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 181, 9, 96, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void _cbButtonleft(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:				
			GUI_DrawBitmap(&bmleft, 9, 9);
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}
static void _cbButtonright(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_DrawBitmap(&bmright, 9, 9);
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}
static void _cbButtonreturn(WM_MESSAGE * pMsg) 
{
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_DrawBitmap(&bmreturn, 0, 9);
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}
/*********************************************************************
*
*       _cbDialog
*/long hide_time=0;
static void _cbpicDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	char text_buf[10];
	
	switch (pMsg->MsgId) 
	{
		case WM_DELETE:
		if(PictureShoe_Mode==1)	
			myfree(SRAMIN,picoffsettbl);		//�ͷ��ڴ�
		else
			Path_Prosses(Now_Path);
			break;
		case WM_INIT_DIALOG:
			hide_time=WM_CreateTimer(pMsg->hWin,0,2000,0);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);
			BUTTON_SetText(hItem, "��һ��");
			WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButtonleft);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);
			BUTTON_SetText(hItem, "��һ��");
			WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButtonright);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);
			BUTTON_SetText(hItem, "����");
			WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButtonreturn);
		
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetBkColor(hItem,GUI_RED);
			sprintf(text_buf,"%d/%d",curindex+1,totwavnum);
			TEXT_SetText(hItem, text_buf);
			break;
		case WM_TIMER:
			WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0));
			WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1));
			WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2));
			break;
		case WM_TOUCH:
			WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0));
			WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1));
			WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2));
			WM_RestartTimer(hide_time,2000);
			break;
		case WM_PAINT:
			GUI_SetBkColor(GUI_BLACK);
            GUI_Clear();
			memset(text_buf,0,sizeof(text_buf));
			sprintf(text_buf,"%d/%d",curindex+1,totwavnum);
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_0), text_buf);
			show_picture(PictureShoe_Mode);
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_1: // Notifications sent by 'Button'
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							
							break;
						case WM_NOTIFICATION_RELEASED:
							curindex++;
							if(curindex>totwavnum-1)
								curindex=0;
							WM_RestartTimer(hide_time,2000);
							WM_InvalidateWindow(pMsg -> hWin);
							break;
					}
					break;	
				case ID_BUTTON_0: // Notifications sent by 'Button'
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:

							break;
						case WM_NOTIFICATION_RELEASED:
							if(curindex==0)
							{
								curindex=totwavnum-1;
							}
							else
								curindex--;
							WM_RestartTimer(hide_time,2000);
							WM_InvalidateWindow(pMsg -> hWin);
							break;
					}
					break;	
				case ID_BUTTON_2: // Notifications sent by 'Button'
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							
							break;
						case WM_NOTIFICATION_RELEASED:
							GUI_EndDialog(pMsg->hWin, 0);
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
/*********************************************************************
*
*       CreatePICTURE
*
*	�� �� ��: CreatePICTURE
*	����˵��: ����ͼƬapp
*	��    ��: mode:1������ͼƬapp��0�����ļ��д�ͼƬ
*	�� �� ֵ: ��
*/
void CreatePICTURE(uint8_t mode,GUI_HWIN hwin) 
{
	uint8_t res=0;
	PictureShoe_Mode=mode;
	if(mode==1)
	{
		res=get_picture();
	}
	else
	{
		curindex=0;
		totwavnum=1;
		res=0;
	}
	switch(res)
	{
		case 0:
			GUI_CreateDialogBox(_picDialogCreate, GUI_COUNTOF(_picDialogCreate), _cbpicDialog, hwin, 0, 0);
			break;
		case 1:
			warnningTask("���SD��");
		break;
		case 2:
			warnningTask("��ͼƬ�ļ�");
		break;
		case 3:
			warnningTask("�ڴ�����ʧ��");
		break;
		default:break;
	}
}


