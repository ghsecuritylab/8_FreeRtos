/**
  ******************************************************************************
  * @file    bsp_tim.c
  * @author  zwx
  * @version V1.8.0
  * @date    2019-01-29
  * @brief
  ******************************************************************************
  */

#include "bsp_tim.h"


/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private struct  -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief
  * @param  None
  * @retval None
  */
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
    uint32_t rcc = 0;

    /*
        APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
        APB2 ��ʱ���� TIM1, TIM8 ,TIM9, TIM10, TIM11
    */
    if(TIMx == TIM1)
    {
        rcc = RCC_APB2Periph_TIM1;
    }
    else if(TIMx == TIM8)
    {
        rcc = RCC_APB2Periph_TIM8;
    }
    else if(TIMx == TIM9)
    {
        rcc = RCC_APB2Periph_TIM9;
    }
    else if(TIMx == TIM10)
    {
        rcc = RCC_APB2Periph_TIM10;
    }
    else if(TIMx == TIM11)
    {
        rcc = RCC_APB2Periph_TIM11;
    }
    /* ������ APB1ʱ�� */
    else if(TIMx == TIM2)
    {
        rcc = RCC_APB1Periph_TIM2;
    }
    else if(TIMx == TIM3)
    {
        rcc = RCC_APB1Periph_TIM3;
    }
    else if(TIMx == TIM4)
    {
        rcc = RCC_APB1Periph_TIM4;
    }
    else if(TIMx == TIM5)
    {
        rcc = RCC_APB1Periph_TIM5;
    }
    else if(TIMx == TIM6)
    {
        rcc = RCC_APB1Periph_TIM6;
    }
    else if(TIMx == TIM7)
    {
        rcc = RCC_APB1Periph_TIM7;
    }
    else if(TIMx == TIM12)
    {
        rcc = RCC_APB1Periph_TIM12;
    }
    else if(TIMx == TIM13)
    {
        rcc = RCC_APB1Periph_TIM13;
    }
    else if(TIMx == TIM14)
    {
        rcc = RCC_APB1Periph_TIM14;
    }

    return rcc;
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_TimInit(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    uint16_t usPeriod;
    uint16_t usPrescaler;
    uint32_t uiTIMxCLK;

    /* ʹ��TIMʱ�� */
    if((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
    {
        RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
    }

    if(_ulFreq == 0)
    {
        TIM_Cmd(TIMx, DISABLE);     /* �رն�ʱ��� */
        return;
    }

    /*-----------------------------------------------------------------------
        system_stm32f4xx.c �ļ��� void SetSysClock(void) ������ʱ�ӵ��������£�

        HCLK = SYSCLK / 1     (AHB1Periph)
        PCLK2 = HCLK / 2      (APB2Periph)
        PCLK1 = HCLK / 4      (APB1Periph)

        ��ΪAPB1 prescaler != 1, ���� APB1�ϵ�TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
        ��ΪAPB2 prescaler != 1, ���� APB2�ϵ�TIMxCLK = PCLK2 x 2 = SystemCoreClock;

        APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13,TIM14
        APB2 ��ʱ���� TIM1, TIM8 ,TIM9, TIM10, TIM11

    ----------------------------------------------------------------------- */
    if((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
    {
        /* APB2 ��ʱ�� */
        uiTIMxCLK = SystemCoreClock;
    }
    else    /* APB1 ��ʱ�� */
    {
        uiTIMxCLK = SystemCoreClock / 2;
    }

    if(_ulFreq < 100)
    {
        usPrescaler = 10000 - 1;                    /* ��Ƶ�� = 1000 */
        usPeriod = (uiTIMxCLK / 10000) / _ulFreq  - 1;      /* �Զ���װ��ֵ */
    }
    else if(_ulFreq < 3000)
    {
        usPrescaler = 100 - 1;                  /* ��Ƶ�� = 100 */
        usPeriod = (uiTIMxCLK / 100) / _ulFreq  - 1;        /* �Զ���װ��ֵ */
    }
    else    /* ����4K��Ƶ�ʣ������Ƶ */
    {
        usPrescaler = 0;                    /* ��Ƶ�� = 1 */
        usPeriod = uiTIMxCLK / _ulFreq - 1; /* �Զ���װ��ֵ */
    }

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = usPeriod;
    TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;       /* TIM1 �� TIM8 �������� */

    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

    TIM_ARRPreloadConfig(TIMx, ENABLE);

    /* TIM Interrupts enable */
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

    /* TIMx enable counter */
    TIM_Cmd(TIMx, ENABLE);

    /* ����TIM��ʱ�����ж� (Update) */
    {
        NVIC_InitTypeDef NVIC_InitStructure;    /* �жϽṹ���� misc.h �ж��� */
        uint8_t irq = 0;    /* �жϺ�, ������ stm32f4xx.h */

        if((TIMx == TIM1) || (TIMx == TIM10))
        {
            irq = TIM1_UP_TIM10_IRQn;
        }
        else if(TIMx == TIM2)
        {
            irq = TIM2_IRQn;
        }
        else if(TIMx == TIM3)
        {
            irq = TIM3_IRQn;
        }
        else if(TIMx == TIM4)
        {
            irq = TIM4_IRQn;
        }
        else if(TIMx == TIM5)
        {
            irq = TIM5_IRQn;
        }
        else if(TIMx == TIM6)
        {
            irq = TIM6_DAC_IRQn;
        }
        else if(TIMx == TIM7)
        {
            irq = TIM7_IRQn;
        }
        else if(TIMx == TIM7)
        {
            irq = TIM7_IRQn;
        }
        else if(TIMx == TIM7)
        {
            irq = TIM7_IRQn;
        }
        else if((TIMx == TIM8) || (TIMx == TIM13))
        {
            irq = TIM8_UP_TIM13_IRQn;
        }
        else if(TIMx == TIM9)
        {
            irq = TIM1_BRK_TIM9_IRQn;
        }
        else if(TIMx == TIM11)
        {
            irq = TIM1_TRG_COM_TIM11_IRQn;
        }
        else if(TIMx == TIM12)
        {
            irq = TIM8_BRK_TIM12_IRQn;
        }
        else if(TIMx == TIM12)
        {
            irq = TIM8_TRG_COM_TIM14_IRQn;
        }

        NVIC_InitStructure.NVIC_IRQChannel = irq;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    }
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_TimClose(TIM_TypeDef* TIMx)
{
    TIM_Cmd(TIMx, DISABLE);
    TIM_ITConfig(TIMx, TIM_IT_Update, DISABLE);
}


/****************** ��������Դ�Ƽ� http://www.bdrl.com.cn/ ********************/

