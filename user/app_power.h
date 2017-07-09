/*****************************************************************************************
��Ȩ����:        ---------------------
�汾��:            1.0.0
��������:        2009.09.09
�ļ���:            app_power.h
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

#ifndef APP_POWER_PRESENT
#define APP_POWER_PRESENT

#ifdef  APP_POWER_GLOBALS    
    #define APP_POWER_EXT
#else
    #define APP_POWER_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2005.1.1
����˵��:   ��Դ����
����˵��:   ��
*****************************************************************************************/
#define PM_POWER                    42                          // ϵͳ   ��Դ
#define PM_MOTOR                    43                          // Print  ��Դ
#define PM_BEEP                     44                          // beep   ��Դ




/*********************************************************************************************************
  �궨��
*********************************************************************************************************/
#define PW_PIN_POWER                GPIO_Pin_9                 // PW - P0.8
#define PW_PIN_POWER_PORT           GPIOB
#define PW_PIN_POWER_PORT_CLK       RCC_AHBPeriph_GPIOB  

#define PW_PIN_VH_EN                GPIO_Pin_4                 // PW - P0.9
#define PW_PIN_VH_EN_PORT           GPIOB
#define PW_PIN_VH_EN_PORT_CLK       RCC_AHBPeriph_GPIOB  

#define PW_PIN_BEEP                 GPIO_Pin_5                 // PW - P0.23
#define PW_PIN_BEEP_PORT            GPIOB
#define PW_PIN_BEEP_PORT_CLK        RCC_AHBPeriph_GPIOB  




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2009.09.09
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_POWER_EXT    void    ConfigurePOWER(void);

APP_POWER_EXT    uint8   POWER_StatusIO (uint8 type);
APP_POWER_EXT    void    POWER_Manager(uint8 type, uint8 status);




#endif




