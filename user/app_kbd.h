/*****************************************************************************************
��Ȩ����:        -----------------
�汾��:            1.0.0
��������:        2009.09.09
�ļ���:            app_kbd.h
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

#ifndef APP_KBD_PRESENT
#define APP_KBD_PRESENT

#ifdef  APP_KBD_GLOBALS    
    #define APP_KBD_EXT
#else
    #define APP_KBD_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:        1.0.0
��������:    2009.09.11
����˵��:   ������ֵ
����˵��:   ��
*****************************************************************************************/
#define KEY_HAL_POWER                 61                        // ��Դ
#define KEY_HAL_FEED                  62                        // ����




/*********************************************************************************************************
  �궨��
*********************************************************************************************************/
#define KEY_POWER                    GPIO_Pin_8                 // KEY1 - P0.7 
#define KEY_POWER_PORT               GPIOB
#define KEY_POWER_PORT_CLK           RCC_AHBPeriph_GPIOB  

#define KEY_FEED                     GPIO_Pin_15                // KEY2 - P0.14 
#define KEY_FEED_PORT                GPIOA
#define KEY_FEED_PORT_CLK            RCC_AHBPeriph_GPIOA  


#define FEED_Time                       (3)                     // ��ֽʱ��
#define POWER_OffTime                   (6)                     // �ػ�ʱ��
#define PrintTestPageTime               (4000)                  // ��ӡ����ʱ��2��




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2009.09.09
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_KBD_EXT  void    ConfigureKBD(void);

APP_KBD_EXT  void    KBD_Feed(void);
APP_KBD_EXT  void    KBD_GetPinValue(void);
APP_KBD_EXT  uint8   KBD_GetPinLevelValue(uint8 value);




#endif




