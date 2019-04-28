/**
  ******************************************************************************
  * @file    bsp_sram.c
  * @author  zwx
  * @version V1.8.0
  * @date    2019-01-29
  * @brief
  ******************************************************************************
  */

#include "bsp_sram.h"


/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private struct  -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//ʹ��NOR/SRAM�� Bank1.sector3,��ַλHADDR[27,26]=10
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_InitSram(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    FMC_NORSRAMInitTypeDef  FMC_NORSRAMInitStructure;
    FMC_NORSRAMTimingInitTypeDef  readWriteTiming;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��PD,PE,PF,PGʱ��
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC,ENABLE);//ʹ��FMCʱ��

    GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(0XFF<<8);//PD0,1,4,5,8~15 AF OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.GPIO_Pin = (3<<0)|(0X1FF<<7);//PE0,1,7~15,AF OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.GPIO_Pin = (0X3F<<0)|(0XF<<12);  //PF0~5,12~15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��

    GPIO_InitStructure.GPIO_Pin =(0X3F<<0)| GPIO_Pin_10;//PG0~5,10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��


    GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FMC);//PD0,AF12
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FMC);//PD1,AF12
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FMC);//PD15,AF12

    GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FMC);//PE7,AF12
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FMC);//PE15,AF12

    GPIO_PinAFConfig(GPIOF,GPIO_PinSource0,GPIO_AF_FMC);//PF0,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource1,GPIO_AF_FMC);//PF1,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource2,GPIO_AF_FMC);//PF2,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource3,GPIO_AF_FMC);//PF3,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource4,GPIO_AF_FMC);//PF4,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource5,GPIO_AF_FMC);//PF5,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FMC);//PF12,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource13,GPIO_AF_FMC);//PF13,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource14,GPIO_AF_FMC);//PF14,AF12
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource15,GPIO_AF_FMC);//PF15,AF12

    GPIO_PinAFConfig(GPIOG,GPIO_PinSource0,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource1,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource2,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource3,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource4,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource5,GPIO_AF_FMC);
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource10,GPIO_AF_FMC);


    readWriteTiming.FMC_AddressSetupTime = 0x00;    //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK 1/36M=27ns
    readWriteTiming.FMC_AddressHoldTime = 0x00;     //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
    readWriteTiming.FMC_DataSetupTime = 0x08;       ////���ݱ���ʱ�䣨DATAST��Ϊ9��HCLK 6*9=54ns
    readWriteTiming.FMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FMC_CLKDivision = 0x00;
    readWriteTiming.FMC_DataLatency = 0x00;
    readWriteTiming.FMC_AccessMode = FMC_AccessMode_A;     //ģʽA

    FMC_NORSRAMInitStructure.FMC_Bank = FMC_Bank1_NORSRAM3;//  ��������ʹ��NE3 ��Ҳ�Ͷ�ӦBTCR[4],[5]��
    FMC_NORSRAMInitStructure.FMC_DataAddressMux = FMC_DataAddressMux_Disable;
    FMC_NORSRAMInitStructure.FMC_MemoryType =FMC_MemoryType_SRAM;// FMC_MemoryType_SRAM;  //SRAM
    FMC_NORSRAMInitStructure.FMC_MemoryDataWidth = FMC_NORSRAM_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit
    FMC_NORSRAMInitStructure.FMC_BurstAccessMode =FMC_BurstAccessMode_Disable;// FMC_BurstAccessMode_Disable;
    FMC_NORSRAMInitStructure.FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low;
    FMC_NORSRAMInitStructure.FMC_AsynchronousWait=FMC_AsynchronousWait_Disable;
    FMC_NORSRAMInitStructure.FMC_WrapMode = FMC_WrapMode_Disable;
    FMC_NORSRAMInitStructure.FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState;
    FMC_NORSRAMInitStructure.FMC_WriteOperation = FMC_WriteOperation_Enable; //�洢��дʹ��
    FMC_NORSRAMInitStructure.FMC_WaitSignal = FMC_WaitSignal_Disable;
    FMC_NORSRAMInitStructure.FMC_ExtendedMode = FMC_ExtendedMode_Disable; // ��дʹ����ͬ��ʱ��
    FMC_NORSRAMInitStructure.FMC_WriteBurst = FMC_WriteBurst_Disable;
    FMC_NORSRAMInitStructure.FMC_ReadWriteTimingStruct = &readWriteTiming;
    FMC_NORSRAMInitStructure.FMC_WriteTimingStruct = &readWriteTiming; //��дͬ��ʱ��

    FMC_NORSRAMInit(&FMC_NORSRAMInitStructure);  //��ʼ��FMC����

    FMC_NORSRAMCmd(FMC_Bank1_NORSRAM3, ENABLE);  // ʹ��BANK1����3
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_SramWrite(u8* pBuffer,u32 WriteAddr,u32 n)
{
    for(; n!=0; n--)
    {
        *(vu8*)(Bank1_SRAM3_ADDR+WriteAddr)=*pBuffer;
        WriteAddr++;
        pBuffer++;
    }
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_SramRead(u8* pBuffer,u32 ReadAddr,u32 n)
{
    for(; n!=0; n--)
    {
        *pBuffer++=*(vu8*)(Bank1_SRAM3_ADDR+ReadAddr);
        ReadAddr++;
    }
}

/****************** ��������Դ�Ƽ� http://www.bdrl.com.cn/ ********************/



