#ifndef __HZFONTUPDATA_H
#define __HZFONTUPDATA_H
#include "GUI.h"
#include "main.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//STemwin �ֿ���������    
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/3/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

uint32_t emwin_fupd_prog(uint32_t fsize,uint32_t pos); //EMWINʹ�õ���ʾ���½���
uint8_t emwin_updata_fontx(uint8_t *fxpath,uint8_t fx);//EMWINʹ�õĸ���ָ���ֿ⺯��
uint8_t emwin_update_font(uint8_t* src);    //EMWINʹ�õ��ֿ���º���
void HzFontupdataCreate(GUI_HWIN hwin);
#endif
