#include "mysys.h"
#include "stmflash.h"
#include "iap.h" 


iapfun jump2app; 
uint32_t iapbuf[512]; 	//2K字节缓存  
//appxaddr:应用程序的起始地址
//appbuf:应用程序CODE.
//appsize:应用程序大小(字节).
void iap_write_appbin(uint32_t appxaddr,u8 *appbuf,uint32_t appsize)
{
	uint32_t t;
	uint16_t i=0;
	uint32_t temp;
	uint32_t fwaddr=appxaddr;//当前写入的地址
	uint8_t *dfu=appbuf;
	for(t=0;t<appsize;t+=4)
	{						   
		temp=(uint32_t)dfu[3]<<24;   
		temp|=(uint32_t)dfu[2]<<16;    
		temp|=(uint32_t)dfu[1]<<8;
		temp|=(uint32_t)dfu[0];	  
		dfu+=4;//偏移4个字节
		iapbuf[i++]=temp;	    
		if(i==512)
		{
			i=0; 
			STMFLASH_Write(fwaddr,iapbuf,512);
			fwaddr+=2048;//偏移2048  512*4=2048
		}
	} 
	if(i)STMFLASH_Write(fwaddr,iapbuf,i);//将最后的一些内容字节写进去.  
}

//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(uint32_t appxaddr)
{ 
	if(((*(vu32*)appxaddr)&0x2FF00000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(vu32*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
	}
}		 















