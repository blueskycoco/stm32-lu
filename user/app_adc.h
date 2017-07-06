/*****************************************************************************************
版权所有:        -------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_adc.h
作者:            影舞者
功能说明:        应用配置文件
其它说明:        Atmel AT91SAM3U4-EK Evaluation Board
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef APP_ADC_PRESENT
#define APP_ADC_PRESENT

#ifdef  APP_ADC_GLOBALS    
    #define APP_ADC_EXT
#else
    #define APP_ADC_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   等级
其它说明:   无
#define BATTRY_MAX_ADC                  850                                // 最高电压 ADC 值
#define BATTRY_LOW_ADC                  700                                // 最低电压 ADC 值
*****************************************************************************************/
#define ADC_BATT_PIN                GPIO_Pin_0                              // 电池 通道 ADC0
#define ADC_BATT_PORT               GPIOA
#define ADC_BATT_PORT_CLK           RCC_AHBPeriph_GPIOA

#define ADC_PAPER_PIN               GPIO_Pin_0                              // 打印纸 通道 ADC8
#define ADC_PAPER_PORT              GPIOB
#define ADC_PAPER_PORT_CLK          RCC_AHBPeriph_GPIOB

#define ADC_TM_PIN                  GPIO_Pin_1                              // 打印头 通道 ADC9
#define ADC_TM_PORT                 GPIOB
#define ADC_TM_PORT_CLK             RCC_AHBPeriph_GPIOB

#define ADC_BATT_CH                 ADC_Channel_8
#define ADC_PAPER_CH                ADC_Channel_9
#define ADC_TM_CH                   ADC_Channel_0


#define BATTRY_MAX_V                  (84)                                  // 最高电压 8.4V
#define BATTRY_MIN_V                  (68)                                  // 最低电压 6.8V

#define BATTRY_MAX_ADC                (1686)                                // 最高电压 ADC 值 8.4V 1686(7.7==1611)
#define BATTRY_LOW_ADC_68V            (1375)                                // 最低电压 ADC 值 6.8V 1375
#define BATTRY_LOW_ADC_64V            (1284)                                // 最低电压 ADC 值 6.4V 1284

#define ADC_TM_60C                    (2800)                                // 60度标准值  3000文本

#define ADC_TM_MIN                    (2600)                                // 过热
#define ADC_PAPER_MIN                 (2000)                                // 无纸




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   等级
其它说明:   无
*****************************************************************************************/
#define ADC_BATT                    (0)                             // 电池 通道 ADC0
#define ADC_PAPER                   (8)                             // 打印纸 通道 ADC8
#define ADC_TM                      (9)                             // 打印头 通道 ADC9




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2009.09.09
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_ADC_EXT  void     ConfigureADC(void);

APP_ADC_EXT  void     ADCStart(uint8 adc_chn);

APP_ADC_EXT  void     ADC_FlushScanf(void);

APP_ADC_EXT  uint16   ADC_GetPaperADC(void);
APP_ADC_EXT  uint16   ADC_GetTM_ADC(void);
APP_ADC_EXT  uint16   ADC_GetBatteryADC(void);




#endif





