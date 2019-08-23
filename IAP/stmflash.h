#ifndef __STMFLASH_H
#define __STMFLASH_H
#include "mysys.h"

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
#define FLASH_WAITETIME  50000          //FLASH�ȴ���ʱʱ��

//STM32F767 FLASH ��������ʼ��ַ
#if defined(DUAL_BANK)
    #define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) //����0��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) //����1��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) //����2��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) //����3��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) //����4��ʼ��ַ, 64 Kbytes 
    #define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) //����5��ʼ��ַ, 128 Kbytes 
    #define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) //����6��ʼ��ַ, 128 Kbytes 
    #define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) //����7��ʼ��ַ, 128 Kbytes 
    
    #define ADDR_FLASH_SECTOR_12    ((uint32_t)0x08080000) //����0��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_13    ((uint32_t)0x08084000) //����0��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_14    ((uint32_t)0x08088000) //����0��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_15    ((uint32_t)0x0808C000) //����0��ʼ��ַ, 16 Kbytes 
    #define ADDR_FLASH_SECTOR_16    ((uint32_t)0x08090000) //����4��ʼ��ַ, 64 Kbytes 
    #define ADDR_FLASH_SECTOR_17    ((uint32_t)0x080A0000) //����5��ʼ��ַ, 128 Kbytes 
    #define ADDR_FLASH_SECTOR_18    ((uint32_t)0x080C0000) //����5��ʼ��ַ, 128 Kbytes 
    #define ADDR_FLASH_SECTOR_19    ((uint32_t)0x080E0000) //����5��ʼ��ַ, 128 Kbytes 
#else
    #define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) //����0��ʼ��ַ, 32 Kbytes  
    #define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08008000) //����1��ʼ��ַ, 32 Kbytes  
    #define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08010000) //����2��ʼ��ַ, 32 Kbytes  
    #define ADDR_FLASH_SECTOR_3     ((uint32_t)0x08018000) //����3��ʼ��ַ, 32 Kbytes  
    #define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08020000) //����4��ʼ��ַ, 128 Kbytes  
    #define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08040000) //����5��ʼ��ַ, 256 Kbytes  
    #define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08080000) //����6��ʼ��ַ, 256 Kbytes  
    #define ADDR_FLASH_SECTOR_7     ((uint32_t)0x080C0000) //����7��ʼ��ַ, 256 Kbytes  
#endif 


uint32_t STMFLASH_ReadWord(uint32_t faddr);		  	//������  
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

#endif