#ifndef document_H
#define document_H
#include "main.h"
#include "LISTVIEW.h"


typedef struct
{
	uint32_t ALL_File_Count;
	uint32_t File_Count;
	uint32_t Document_Count;
	DWORD	fsize;			/* File size */
	WORD	fdate;			/* Modified date */
	WORD	ftime;			/* Modified time */
	BYTE	fattrib;		/* File attribute */ //32 �ɼ��ɶ�д 33ֻ�� 34 ���� 35 ֻ������   16�ļ���	
	char *File_Name;
	char *File_Type;
}File_Dat;

extern File_Dat *File_Data;						//�ļ����
void FileListView_Init(LISTVIEW_Handle hobj);
FRESULT scan_files (char* path,LISTVIEW_Handle handle);
uint8_t Path_Prosses(char* source);
#endif



