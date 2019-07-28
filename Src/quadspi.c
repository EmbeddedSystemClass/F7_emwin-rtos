///**
//  ******************************************************************************
//  * File Name          : QUADSPI.c
//  * Description        : This file provides code for the configuration
//  *                      of the QUADSPI instances.
//  ******************************************************************************
//  * @attention
//  *
//  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
//  * All rights reserved.</center></h2>
//  *
//  * This software component is licensed by ST under Ultimate Liberty license
//  * SLA0044, the "License"; You may not use this file except in compliance with
//  * the License. You may obtain a copy of the License at:
//  *                             www.st.com/SLA0044
//  *
//  ******************************************************************************
//  */

///* Includes ------------------------------------------------------------------*/
//#include "quadspi.h"

///* USER CODE BEGIN 0 */

///* USER CODE END 0 */

//QSPI_HandleTypeDef hqspi;

///* QUADSPI init function */
//void MX_QUADSPI_Init(void)
//{

//  hqspi.Instance = QUADSPI;
//  hqspi.Init.ClockPrescaler = 1;
//  hqspi.Init.FifoThreshold = 4;
//  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
//  hqspi.Init.FlashSize = POSITION_VAL(0X2000000)-1;  //SPI FLASH��С��W25Q256��СΪ32M�ֽ�;
//  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
//  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
//  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
//  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
//  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
//  {
//    Error_Handler();
//  }
//	
//}

//void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
//{

//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  if(qspiHandle->Instance==QUADSPI)
//  {
//  /* USER CODE BEGIN QUADSPI_MspInit 0 */

//  /* USER CODE END QUADSPI_MspInit 0 */
//    /* QUADSPI clock enable */
//    __HAL_RCC_QSPI_CLK_ENABLE();
//  
//    __HAL_RCC_GPIOF_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    /**QUADSPI GPIO Configuration    
//    PF6     ------> QUADSPI_BK1_IO3
//    PF7     ------> QUADSPI_BK1_IO2
//    PF8     ------> QUADSPI_BK1_IO0
//    PF9     ------> QUADSPI_BK1_IO1
//    PB2     ------> QUADSPI_CLK
//    PB6     ------> QUADSPI_BK1_NCS 
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
//    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
//    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_2;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_6;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /* USER CODE BEGIN QUADSPI_MspInit 1 */

//  /* USER CODE END QUADSPI_MspInit 1 */
//  }
//}

//void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
//{

//  if(qspiHandle->Instance==QUADSPI)
//  {
//  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

//  /* USER CODE END QUADSPI_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_QSPI_CLK_DISABLE();
//  
//    /**QUADSPI GPIO Configuration    
//    PF6     ------> QUADSPI_BK1_IO3
//    PF7     ------> QUADSPI_BK1_IO2
//    PF8     ------> QUADSPI_BK1_IO0
//    PF9     ------> QUADSPI_BK1_IO1
//    PB2     ------> QUADSPI_CLK
//    PB6     ------> QUADSPI_BK1_NCS 
//    */
//    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

//  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

//  /* USER CODE END QUADSPI_MspDeInit 1 */
//  }
//} 

///* USER CODE BEGIN 1 */
////QSPI��������
////instruction:Ҫ���͵�ָ��
////address:���͵���Ŀ�ĵ�ַ
////dummyCycles:��ָ��������
////	instructionMode:ָ��ģʽ;QSPI_INSTRUCTION_NONE,QSPI_INSTRUCTION_1_LINE,QSPI_INSTRUCTION_2_LINE,QSPI_INSTRUCTION_4_LINE  
////	addressMode:��ַģʽ; QSPI_ADDRESS_NONE,QSPI_ADDRESS_1_LINE,QSPI_ADDRESS_2_LINE,QSPI_ADDRESS_4_LINE
////	addressSize:��ַ����;QSPI_ADDRESS_8_BITS,QSPI_ADDRESS_16_BITS,QSPI_ADDRESS_24_BITS,QSPI_ADDRESS_32_BITS
////	dataMode:����ģʽ; QSPI_DATA_NONE,QSPI_DATA_1_LINE,QSPI_DATA_2_LINE,QSPI_DATA_4_LINE

//void QSPI_Send_CMD(uint32_t instruction,uint32_t address,uint32_t dummyCycles,uint32_t instructionMode,uint32_t addressMode,uint32_t addressSize,uint32_t dataMode)
//{
//    QSPI_CommandTypeDef Cmdhandler;
//    
//    Cmdhandler.Instruction=instruction;                 	//ָ��
//    Cmdhandler.Address=address;                            	//��ַ
//    Cmdhandler.DummyCycles=dummyCycles;                     //���ÿ�ָ��������
//    Cmdhandler.InstructionMode=instructionMode;				//ָ��ģʽ
//    Cmdhandler.AddressMode=addressMode;   					//��ַģʽ
//    Cmdhandler.AddressSize=addressSize;   					//��ַ����
//    Cmdhandler.DataMode=dataMode;             				//����ģʽ
//    Cmdhandler.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;       	//ÿ�ζ�����ָ��
//    Cmdhandler.AlternateByteMode=QSPI_ALTERNATE_BYTES_NONE; //�޽����ֽ�
//    Cmdhandler.DdrMode=QSPI_DDR_MODE_DISABLE;           	//�ر�DDRģʽ
//    Cmdhandler.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;

//    HAL_QSPI_Command(&hqspi,&Cmdhandler,5000);
//}
////QSPI����ָ�����ȵ�����
////buf:�������ݻ������׵�ַ
////datalen:Ҫ��������ݳ���
////����ֵ:0,����
////    ����,�������
//uint8_t QSPI_Receive(uint8_t* buf,uint32_t datalen)
//{
//    hqspi.Instance->DLR=datalen-1;                           //�������ݳ���
//    if(HAL_QSPI_Receive(&hqspi,buf,5000)==HAL_OK) 
//		return 0;  //��������
//    else 
//		return 1;
//}

////QSPI����ָ�����ȵ�����
////buf:�������ݻ������׵�ַ
////datalen:Ҫ��������ݳ���
////����ֵ:0,����
////    ����,�������
//uint8_t QSPI_Transmit(uint8_t* buf,uint32_t datalen)
//{
//    hqspi.Instance->DLR=datalen-1;                            //�������ݳ���
//    if(HAL_QSPI_Transmit(&hqspi,buf,5000)==HAL_OK) return 0;  //��������
//    else return 1;
//}
///* USER CODE END 1 */

///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
#include "quadspi.h"
#include "mysys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������ 
//QSPI ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/7/18
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//�ȴ�״̬��־
//flag:��Ҫ�ȴ��ı�־λ
//sta:��Ҫ�ȴ���״̬
//wtime:�ȴ�ʱ��
//����ֵ:0,�ȴ��ɹ�.
//	     1,�ȴ�ʧ��.
u8 QSPI_Wait_Flag(u32 flag,u8 sta,u32 wtime)
{
	u8 flagsta=0;
	while(wtime)
	{
		flagsta=(QUADSPI->SR&flag)?1:0; 
		if(flagsta==sta)break;
		wtime--;
	}
	if(wtime)return 0;
	else return 1;
}
//GPIO��������
//GPIOx:GPIOA~GPIOI.
//BITx:0~15,����IO���ű��.
//AFx:0~15,����AF0~AF15.
//AF0~15�������(��������г����õ�,��ϸ�����429/746�����ֲ�,Table 12):
//AF0:MCO/SWD/SWCLK/RTC   		AF1:TIM1/TIM2;            		AF2:TIM3~5;               		AF3:TIM8~11
//AF4:I2C1~I2C4;          		AF5:SPI1~SPI6;            		AF6:SPI3/SAI1;            	 	AF7:SPI2/3/USART1~3/UART5/SPDIFRX;
//AF8:USART4~8/SPDIFRX/SAI2; 	AF9;CAN1~2/TIM12~14/LCD/QSPI; 	AF10:USB_OTG/USB_HS/SAI2/QSPI  	AF11:ETH
//AF12:FMC/SDMMC/OTG/HS   		AF13:DCIM                 		AF14:LCD;                  		AF15:EVENTOUT
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}   
//GPIOͨ������ 
//GPIOx:GPIOA~GPIOI.
//BITx:0X0000~0XFFFF,λ����,ÿ��λ����һ��IO,��0λ����Px0,��1λ����Px1,��������.����0X0101,����ͬʱ����Px0��Px8.
//MODE:0~3;ģʽѡ��,0,����(ϵͳ��λĬ��״̬);1,��ͨ���;2,���ù���;3,ģ������.
//OTYPE:0/1;�������ѡ��,0,�������;1,��©���.
//OSPEED:0~3;����ٶ�����,0,����;1,����;2,����;3,����. 
//PUPD:0~3:����������,0,����������;1,����;2,����;3,����.
//ע��:������ģʽ(��ͨ����/ģ������)��,OTYPE��OSPEED������Ч!!
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD)
{  
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//һ����λ��� 
		curpin=BITx&pos;//��������Ƿ�Ҫ����
		if(curpin==pos)	//��Ҫ����
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->MODER|=MODE<<(pinpos*2);	//�����µ�ģʽ 
			if((MODE==0X01)||(MODE==0X02))	//��������ģʽ/���ù���ģʽ
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//���ԭ��������
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//�����µ��ٶ�ֵ  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//���ԭ��������
				GPIOx->OTYPER|=OTYPE<<pinpos;		//�����µ����ģʽ
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//�����ԭ��������
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//�����µ�������
		}
	}
} 
//��ʼ��QSPI�ӿ�
//����ֵ:0,�ɹ�;
//       1,ʧ��;
u8 MX_QUADSPI_Init(void)
{
	u32 tempreg=0;
	RCC->AHB1ENR|=1<<1;    		//ʹ��PORTBʱ��	   
	RCC->AHB1ENR|=1<<5;    		//ʹ��PORTFʱ��	   
	RCC->AHB3ENR|=1<<1;   		//QSPIʱ��ʹ��
	GPIO_Set(GPIOB,1<<2,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB2���ù������	
	GPIO_Set(GPIOB,1<<6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB6���ù������	
	GPIO_Set(GPIOF,0XF<<6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PF6~9���ù������	
   	GPIO_AF_Set(GPIOB,2,9);		//PB2,AF9
 	GPIO_AF_Set(GPIOB,6,10);	//PB6,AF10
 	GPIO_AF_Set(GPIOF,6,9);		//PF6,AF9 
 	GPIO_AF_Set(GPIOF,7,9);		//PF7,AF9
 	GPIO_AF_Set(GPIOF,8,10);	//PF8,AF10
 	GPIO_AF_Set(GPIOF,9,10);	//PF9,AF10
	
	RCC->AHB3RSTR|=1<<1;		//��λQSPI
	RCC->AHB3RSTR&=~(1<<1);		//ֹͣ��λQSPI
	if(QSPI_Wait_Flag(1<<5,0,0XFFFF)==0)//�ȴ�BUSY����
	{
		tempreg=(3-1)<<24;		//����QSPIʱ��ΪAHBʱ�ӵ�1/3,��216M/3=72Mhz,13.8ns
		tempreg|=(4-1)<<8;		//����FIFO��ֵΪ4���ֽ�(���Ϊ31,��ʾ32���ֽ�)
		tempreg|=0<<7;			//ѡ��FLASH1
		tempreg|=0<<6;			//��ֹ˫����ģʽ
		tempreg|=1<<4;			//������λ�������(DDRģʽ��,��������Ϊ0)
		QUADSPI->CR=tempreg;	//����CR�Ĵ���
		tempreg=(25-1)<<16;		//����FLASH��СΪ2^25=32MB
		tempreg|=(4-1)<<8;		//Ƭѡ�ߵ�ƽʱ��Ϊ4��ʱ��(13.8*4=55.2ns),���ֲ������tSHSL����
		tempreg|=1<<0;			//Mode3,����ʱCLKΪ�ߵ�ƽ
		QUADSPI->DCR=tempreg;	//����DCR�Ĵ���
		QUADSPI->CR|=1<<0;		//ʹ��QSPI
	}else return 1;
	return 0;
}

//QSPI��������
//cmd:Ҫ���͵�ָ��
//addr:���͵���Ŀ�ĵ�ַ
//mode:ģʽ,��ϸλ��������:
//	mode[1:0]:ָ��ģʽ;00,��ָ��;01,���ߴ���ָ��;10,˫�ߴ���ָ��;11,���ߴ���ָ��.
//	mode[3:2]:��ַģʽ;00,�޵�ַ;01,���ߴ����ַ;10,˫�ߴ����ַ;11,���ߴ����ַ.
//	mode[5:4]:��ַ����;00,8λ��ַ;01,16λ��ַ;10,24λ��ַ;11,32λ��ַ.
//	mode[7:6]:����ģʽ;00,������;01,���ߴ�������;10,˫�ߴ�������;11,���ߴ�������.
//dmcycle:��ָ��������
void QSPI_Send_CMD(u8 cmd,u32 addr,u8 mode,u8 dmcycle)
{
	u32 tempreg=0;	
	u8 status;
	if(QSPI_Wait_Flag(1<<5,0,0XFFFF)==0)	//�ȴ�BUSY����
	{
		tempreg=0<<31;						//��ֹDDRģʽ
		tempreg|=0<<28;						//ÿ�ζ�����ָ��
		tempreg|=0<<26;						//���дģʽ
		tempreg|=((u32)mode>>6)<<24;		//��������ģʽ
		tempreg|=(u32)dmcycle<<18;			//���ÿ�ָ��������
		tempreg|=((u32)(mode>>4)&0X03)<<12;	//���õ�ַ����
		tempreg|=((u32)(mode>>2)&0X03)<<10;	//���õ�ַģʽ
		tempreg|=((u32)(mode>>0)&0X03)<<8;	//����ָ��ģʽ
		tempreg|=cmd;						//����ָ��
		QUADSPI->CCR=tempreg;				//����CCR�Ĵ���
		if(mode&0X0C)						//��ָ��+��ַҪ����
		{
			QUADSPI->AR=addr;				//���õ�ַ�Ĵ���
		} 
		if((mode&0XC0)==0)					//�����ݴ���,�ȴ�ָ������
		{
			status=QSPI_Wait_Flag(1<<1,1,0XFFFF);//�ȴ�TCF,���������
			if(status==0)
			{
				QUADSPI->FCR|=1<<1;			//���TCF��־λ 
			}
		}
	}	
}

//QSPI����ָ�����ȵ�����
//buf:�������ݻ������׵�ַ
//datalen:Ҫ��������ݳ���
//����ֵ:0,����
//    ����,�������
u8 QSPI_Receive(u8* buf,u32 datalen)
{
	u32 tempreg=QUADSPI->CCR;
	u32 addrreg=QUADSPI->AR; 	
	u8 status;
	vu32 *data_reg=&QUADSPI->DR;
	QUADSPI->DLR=datalen-1;					//�������ݴ��䳤��
	tempreg&=~(3<<26);						//���FMODEԭ��������
	tempreg|=1<<26;							//����FMODEΪ��Ӷ�ȡģʽ
	QUADSPI->FCR|=1<<1;						//���TCF��־λ
	QUADSPI->CCR=tempreg;					//��дCCR�Ĵ���
	QUADSPI->AR=addrreg;					//��дAR�Ĵ���,��������
	while(datalen)
	{
		status=QSPI_Wait_Flag(3<<1,1,0XFFFF);//�ȵ�FTF��TCF,�����յ�������
		if(status==0)						//�ȴ��ɹ�
		{
			*buf++=*(vu8 *)data_reg;
			datalen--;
		}else break;
	}
	if(status==0)
	{
		QUADSPI->CR|=1<<2;							//��ֹ���� 
		status=QSPI_Wait_Flag(1<<1,1,0XFFFF);		//�ȴ�TCF,�����ݴ������
		if(status==0)
		{
			QUADSPI->FCR|=1<<1;						//���TCF��־λ 
			status=QSPI_Wait_Flag(1<<5,0,0XFFFF);	//�ȴ�BUSYλ����
		}
	}
	return status;
} 

//QSPI����ָ�����ȵ�����
//buf:�������ݻ������׵�ַ
//datalen:Ҫ��������ݳ���
//����ֵ:0,����
//    ����,�������
u8 QSPI_Transmit(u8* buf,u32 datalen)
{
	u32 tempreg=QUADSPI->CCR;
	u32 addrreg=QUADSPI->AR; 
	u8 status;
	vu32 *data_reg=&QUADSPI->DR;
	QUADSPI->DLR=datalen-1;					//�������ݴ��䳤��
	tempreg&=~(3<<26);						//���FMODEԭ��������
	tempreg|=0<<26;							//����FMODEΪ���д��ģʽ
	QUADSPI->FCR|=1<<1;						//���TCF��־λ
	QUADSPI->CCR=tempreg;					//��дCCR�Ĵ��� 
	while(datalen)
	{
		status=QSPI_Wait_Flag(1<<2,1,0XFFFF);//�ȵ�FTF
		if(status!=0)						//�ȴ��ɹ�
		{
			break;
		}
		*(vu8 *)data_reg=*buf++;
		datalen--;
	}
	if(status==0)
	{
		QUADSPI->CR|=1<<2;							//��ֹ���� 
		status=QSPI_Wait_Flag(1<<1,1,0XFFFF);		//�ȴ�TCF,�����ݴ������
		if(status==0)
		{
			QUADSPI->FCR|=1<<1;						//���TCF��־λ 
			status=QSPI_Wait_Flag(1<<5,0,0XFFFF);	//�ȴ�BUSYλ����
		}
	}
	return status;
}




















