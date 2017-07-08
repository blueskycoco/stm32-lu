/*****************************************************************************************
��Ȩ����:        -----------------
�汾��:            1.0.0
��������:        2010.05.11
�ļ���:            app_adc.c
����:            Ӱ����
����˵��:        Ӧ�ò������ļ�
����˵��:        Atmel AT91SAM9G45-EK Evaluation Board
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#define  APP_ADC_GLOBALS
#include "app_types.h"
#include "app_adc.h"
#include "app_power.h"



#if (ADC_SUPPORT == 1)



/*****************************************************************************************
��Ȩ����:    Ӱ����
�汾��:      1.0.0
��������:    2009.09.14
����˵��:    ���µ�����
����˵��:    ��
*****************************************************************************************/
uint8   ADC_CH      = 0;
uint8   ADC_OldCH   = 0;

uint16  ADC_BATT_Value  = 0;
uint16  ADC_PAPER_Value = 0;
uint16  ADC_TM_Value    = 0;

uint8   sys_battery_Pre = 0;
uint8   sys_battery_voltage = 0;

extern  uint8   ADC_RunFlag;




/*****************************************************************************************
��������:    void    ADC_SysBatteryTrans(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ��ȡADC��ֵ 
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void ADC_SysBatteryTrans(void)
{
    uint16  battValue;
    
    // ��ص�%��
    battValue = ADC_GetBatteryADC();
    if (battValue >= BATTRY_LOW_ADC_64V)
    {
        sys_battery_Pre = ((battValue - BATTRY_LOW_ADC_64V) * 100) / (BATTRY_MAX_ADC - BATTRY_LOW_ADC_64V);
        if (sys_battery_Pre > 100)
            sys_battery_Pre = 100;
    }
    
    // ��ص�ѹ
    sys_battery_voltage = (((BATTRY_MAX_V - BATTRY_MIN_V) * sys_battery_Pre) / 100) + BATTRY_MIN_V;
    if (sys_battery_voltage >= BATTRY_MAX_V)
        sys_battery_voltage = BATTRY_MAX_V;
}




/*****************************************************************************************
��������:    uint16    ADC_GetPaperADC(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ��ȡADC��ֵ 
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint16    ADC_GetPaperADC(void)
{
    return ADC_PAPER_Value;
}




/*****************************************************************************************
��������:    uint16    ADC_GetBatteryADC(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ��ȡADC��ֵ 
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint16    ADC_GetBatteryADC(void)
{
    return ADC_BATT_Value;
}




/*****************************************************************************************
��������:    uint16    ADC_GetTM_ADC(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ��ȡADC��ֵ 
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint16    ADC_GetTM_ADC(void)
{
    return ADC_TM_Value;
}




/*********************************************************************************************************
** Function name:        ADCStart
** Descriptions:         ADC�������
** parameters:           ucChannel:ʹ��ͨ��
** Returned value:       None
*********************************************************************************************************/
void ADCStart(uint8 adc_chn)
{
    uint16  ADCValue = 0;

    // ��������Ч
    if (ADC1->ISR & ADC_ISR_EOC)
    {
        ADCValue = ADC_GetConversionValue(ADC1);

        switch (ADC_OldCH)
        {
            case ADC_BATT:
                ADC_BATT_Value = ADCValue;
                ADC_SysBatteryTrans();                      // ת��ADC��صİٷֱȼ���ѹ
                break;

            case ADC_PAPER:
                ADC_PAPER_Value = ADCValue;
                break;

            case ADC_TM:
                ADC_TM_Value = ADCValue;
                break;
        }
    }

#if 0
    APP_printf("\n\r %d(%d, %d): %d, %d, %d", 
                    ADCValue, ADC_OldCH, adc_chn,
                    ADC_GetBatteryADC(),
                    ADC_GetPaperADC(),
                    ADC_GetTM_ADC());
#endif

    switch (adc_chn)
    {
        case ADC_BATT:
            ADC_OldCH = ADC_BATT;
            ADC_ChannelConfig(ADC1, ADC_BATT_CH ,  ADC_SampleTime_239_5Cycles); 
            break;
            
        case ADC_PAPER:
            ADC_OldCH = ADC_PAPER;
            ADC_ChannelConfig(ADC1, ADC_PAPER_CH , ADC_SampleTime_239_5Cycles); 
            break;
            
        case ADC_TM:
            ADC_OldCH = ADC_TM;
            ADC_ChannelConfig(ADC1, ADC_TM_CH ,    ADC_SampleTime_239_5Cycles); 
            break;
    }
}




/*********************************************************************************************************
** Function name:        ADC_FlushScanf
** Descriptions:         ADC�������
** parameters:           ucChannel:ʹ��ͨ��
** Returned value:       None
*********************************************************************************************************/
void  ADC_FlushScanf(void)
{
    if (ADC_RunFlag == FALSE)
        return;
    
    switch (ADC_CH)
    {
        case ADC_BATT:
            ADCStart(ADC_BATT);
            ADC_CH = ADC_PAPER;
            break;

        case ADC_PAPER:
            ADCStart(ADC_PAPER);
            ADC_CH = ADC_TM;
            break;

        case ADC_TM:
            ADCStart(ADC_TM);
            ADC_CH = ADC_BATT;
            break;

        default:
            ADC_CH = ADC_BATT;
            break;
    }
}




/*****************************************************************************************
��������:    void  ConfigureADC(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ��ʼ��ADC
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  ConfigureADC(void)
{
     ADC_InitTypeDef   ADC_InitStructure;
     GPIO_InitTypeDef  GPIO_InitStructure; 
	
#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureADC... ");
#endif

    ADC_BATT_Value  = 0; 
    ADC_PAPER_Value = 0;
    ADC_TM_Value    = 0;
    
    ADC_CH      = ADC_BATT;
    ADC_OldCH   = ADC_BATT;

    ADC_DeInit(ADC1);                                       // ��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);    // ʹ��ADC1ͨ��ʱ��	   

    ////////////////////////////////////////////////////////////////////////////////// 

    RCC_AHBPeriphClockCmd(ADC_BATT_PORT_CLK, ENABLE);   
    GPIO_InitStructure.GPIO_Pin   = ADC_BATT_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_BATT_PORT, &GPIO_InitStructure);
    
    RCC_AHBPeriphClockCmd(ADC_PAPER_PORT_CLK, ENABLE);   
    GPIO_InitStructure.GPIO_Pin   = ADC_PAPER_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_PAPER_PORT, &GPIO_InitStructure);
    
    RCC_AHBPeriphClockCmd(ADC_TM_PORT_CLK, ENABLE);   
    GPIO_InitStructure.GPIO_Pin   = ADC_TM_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_TM_PORT, &GPIO_InitStructure);

    ////////////////////////////////////////////////////////////////////////////////////	
    ADC_StructInit(&ADC_InitStructure); 

    /* ���� ADC1 �����ɼ�ģʽ-12λ���� */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                          // 12λ����
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                              // ����ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;     // ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                          // �����Ҷ���
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;                 // ��ǰ:0--18ͨ��
    ADC_Init(ADC1, &ADC_InitStructure); 
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // ������ز���
    //ADC_ChannelConfig(ADC1, ADC_TM_CH ,    ADC_SampleTime_239_5Cycles); 
    //ADC_ChannelConfig(ADC1, ADC_PAPER_CH , ADC_SampleTime_239_5Cycles); 
    //ADC_ChannelConfig(ADC1, ADC_BATT_CH ,  ADC_SampleTime_239_5Cycles); 

    ADC_GetCalibrationFactor(ADC1);                         // ��ʼADCУ׼ 
    ADC_Cmd(ADC1, ENABLE);                                  // ʹ��ָ����ADC1 

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)) {;}      // �ȴ�ADC׼���� 0x01000001
    ADC_StartOfConversion(ADC1);                            // ��ʼ��ѹ�ɼ�
}



#endif



