/*****************************************************************************************
版权所有:        -----------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            app_adc.c
作者:            影舞者
功能说明:        应用层配置文件
其它说明:        Atmel AT91SAM9G45-EK Evaluation Board
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#define  APP_ADC_GLOBALS
#include "app_types.h"
#include "app_adc.h"
#include "app_power.h"



#if (ADC_SUPPORT == 1)



/*****************************************************************************************
版权所有:    影舞者
版本号:      1.0.0
生成日期:    2009.09.14
功能说明:    最新的数据
其它说明:    无
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
函数名称:    void    ADC_SysBatteryTrans(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    获取ADC的值 
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void ADC_SysBatteryTrans(void)
{
    uint16  battValue;
    
    // 电池的%比
    battValue = ADC_GetBatteryADC();
    if (battValue >= BATTRY_LOW_ADC_64V)
    {
        sys_battery_Pre = ((battValue - BATTRY_LOW_ADC_64V) * 100) / (BATTRY_MAX_ADC - BATTRY_LOW_ADC_64V);
        if (sys_battery_Pre > 100)
            sys_battery_Pre = 100;
    }
    
    // 电池电压
    sys_battery_voltage = (((BATTRY_MAX_V - BATTRY_MIN_V) * sys_battery_Pre) / 100) + BATTRY_MIN_V;
    if (sys_battery_voltage >= BATTRY_MAX_V)
        sys_battery_voltage = BATTRY_MAX_V;
}




/*****************************************************************************************
函数名称:    uint16    ADC_GetPaperADC(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    获取ADC的值 
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint16    ADC_GetPaperADC(void)
{
    return ADC_PAPER_Value;
}




/*****************************************************************************************
函数名称:    uint16    ADC_GetBatteryADC(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    获取ADC的值 
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint16    ADC_GetBatteryADC(void)
{
    return ADC_BATT_Value;
}




/*****************************************************************************************
函数名称:    uint16    ADC_GetTM_ADC(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    获取ADC的值 
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint16    ADC_GetTM_ADC(void)
{
    return ADC_TM_Value;
}




/*********************************************************************************************************
** Function name:        ADCStart
** Descriptions:         ADC软件启动
** parameters:           ucChannel:使能通道
** Returned value:       None
*********************************************************************************************************/
void ADCStart(uint8 adc_chn)
{
    uint16  ADCValue = 0;

    // 有数据有效
    if (ADC1->ISR & ADC_ISR_EOC)
    {
        ADCValue = ADC_GetConversionValue(ADC1);

        switch (ADC_OldCH)
        {
            case ADC_BATT:
                ADC_BATT_Value = ADCValue;
                ADC_SysBatteryTrans();                      // 转换ADC电池的百分比及电压
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
** Descriptions:         ADC软件启动
** parameters:           ucChannel:使能通道
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
函数名称:    void  ConfigureADC(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    初始化ADC
输入参数:    无
输出参数:    无
其它说明:    无
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

    ADC_DeInit(ADC1);                                       // 复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);    // 使能ADC1通道时钟	   

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

    /* 配置 ADC1 连续采集模式-12位精度 */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                          // 12位精度
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                              // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;     // 转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                          // 数据右对齐
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;                 // 后前:0--18通道
    ADC_Init(ADC1, &ADC_InitStructure); 
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // 启动电池采样
    //ADC_ChannelConfig(ADC1, ADC_TM_CH ,    ADC_SampleTime_239_5Cycles); 
    //ADC_ChannelConfig(ADC1, ADC_PAPER_CH , ADC_SampleTime_239_5Cycles); 
    //ADC_ChannelConfig(ADC1, ADC_BATT_CH ,  ADC_SampleTime_239_5Cycles); 

    ADC_GetCalibrationFactor(ADC1);                         // 开始ADC校准 
    ADC_Cmd(ADC1, ENABLE);                                  // 使能指定的ADC1 

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)) {;}      // 等待ADC准备好 0x01000001
    ADC_StartOfConversion(ADC1);                            // 开始电压采集
}



#endif



