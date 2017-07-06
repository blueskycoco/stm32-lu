/*****************************************************************************************
��Ȩ����:        -------------
�汾��:            1.0.0
��������:        2009.09.09
�ļ���:            app_adc.h
����:            Ӱ����
����˵��:        Ӧ�������ļ�
����˵��:        Atmel AT91SAM3U4-EK Evaluation Board
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#ifndef APP_ADC_PRESENT
#define APP_ADC_PRESENT

#ifdef  APP_ADC_GLOBALS    
    #define APP_ADC_EXT
#else
    #define APP_ADC_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �ȼ�
����˵��:   ��
#define BATTRY_MAX_ADC                  850                                // ��ߵ�ѹ ADC ֵ
#define BATTRY_LOW_ADC                  700                                // ��͵�ѹ ADC ֵ
*****************************************************************************************/
#define ADC_BATT_PIN                GPIO_Pin_0                              // ��� ͨ�� ADC0
#define ADC_BATT_PORT               GPIOA
#define ADC_BATT_PORT_CLK           RCC_AHBPeriph_GPIOA

#define ADC_PAPER_PIN               GPIO_Pin_0                              // ��ӡֽ ͨ�� ADC8
#define ADC_PAPER_PORT              GPIOB
#define ADC_PAPER_PORT_CLK          RCC_AHBPeriph_GPIOB

#define ADC_TM_PIN                  GPIO_Pin_1                              // ��ӡͷ ͨ�� ADC9
#define ADC_TM_PORT                 GPIOB
#define ADC_TM_PORT_CLK             RCC_AHBPeriph_GPIOB

#define ADC_BATT_CH                 ADC_Channel_8
#define ADC_PAPER_CH                ADC_Channel_9
#define ADC_TM_CH                   ADC_Channel_0


#define BATTRY_MAX_V                  (84)                                  // ��ߵ�ѹ 8.4V
#define BATTRY_MIN_V                  (68)                                  // ��͵�ѹ 6.8V

#define BATTRY_MAX_ADC                (1686)                                // ��ߵ�ѹ ADC ֵ 8.4V 1686(7.7==1611)
#define BATTRY_LOW_ADC_68V            (1375)                                // ��͵�ѹ ADC ֵ 6.8V 1375
#define BATTRY_LOW_ADC_64V            (1284)                                // ��͵�ѹ ADC ֵ 6.4V 1284

#define ADC_TM_60C                    (2800)                                // 60�ȱ�׼ֵ  3000�ı�

#define ADC_TM_MIN                    (2600)                                // ����
#define ADC_PAPER_MIN                 (2000)                                // ��ֽ




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �ȼ�
����˵��:   ��
*****************************************************************************************/
#define ADC_BATT                    (0)                             // ��� ͨ�� ADC0
#define ADC_PAPER                   (8)                             // ��ӡֽ ͨ�� ADC8
#define ADC_TM                      (9)                             // ��ӡͷ ͨ�� ADC9




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2009.09.09
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_ADC_EXT  void     ConfigureADC(void);

APP_ADC_EXT  void     ADCStart(uint8 adc_chn);

APP_ADC_EXT  void     ADC_FlushScanf(void);

APP_ADC_EXT  uint16   ADC_GetPaperADC(void);
APP_ADC_EXT  uint16   ADC_GetTM_ADC(void);
APP_ADC_EXT  uint16   ADC_GetBatteryADC(void);




#endif





