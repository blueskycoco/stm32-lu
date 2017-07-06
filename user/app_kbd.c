/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:          1.0.0
��������:        2009.09.09
�ļ���:          app_kbd.c
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

#define  APP_KBD_GLOBALS
#include "app_types.h"
#include "app_kbd.h"
#include "app_led.h"
#include "app_wdt.h"
#include "app_power.h"



#if (KEY_SUPPORT == 1)




/*****************************************************************************************
��Ȩ����:    Ӱ����
�汾��:        1.0.0
��������:    2009.09.08
����˵��:    ����
����˵��:    ��
*****************************************************************************************/
uint8   KBD_ReloadCount = 0;                // ��ֹ�ظ�����
uint8   KBD_CountValue  = 0;                // ��ǰ����ֵ

uint8   KBD_LongPress_POWER = 0;
uint8   KBD_LongPress_POWER_Count = 0;      // ��Դ��������ʱ�ػ�

uint8   KBD_LongPress_FEED = 0;
uint8   KBD_LongPress_FEED_Count = 0;       // FEED��������ʱ�ػ�

uint8   KBD_PrinterTestFlag = false;
uint16  KBD_PrinterTestCount = 0;

extern  uint8    OpenBEEP_Flag;
extern  uint32   SysTimeTick;

extern  void     BEEP_Player(uint8 second);




/*****************************************************************************************
��������:    void  KBD_SetReloadCountValue(uint8 value)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    �����ؽ����ֵ
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  KBD_SetReloadCountValue(uint8 value)
{
    KBD_ReloadCount = value;
}




/*****************************************************************************************
��������:    uint8  KBD_GetPinLevelValue(uint16 value)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ��ȡ����ֵ
�������:    ��������
�������:    1����0�ɿ�
����˵��:    ��
*****************************************************************************************/
uint8  KBD_GetPinLevelValue(uint8 keyType)
{
    uint8  key_value = 0;

    switch (keyType)
    {
        case KEY_HAL_POWER:
            key_value = GPIO_ReadInputDataBit(KEY_POWER_PORT, KEY_POWER);
            if (key_value != 0)
                key_value = 1;
            break;

        case KEY_HAL_FEED:
            key_value = GPIO_ReadInputDataBit(KEY_FEED_PORT, KEY_FEED);
            if (key_value != 0)
                key_value = 1;
            break;

        default:
            key_value = 0;            // ��Ч����1
            break;
    }

    return key_value;
}




/*****************************************************************************************
��������:    void  KBD_GetPinValue(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    ���Ӱ���״̬
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  KBD_GetPinValue(void)
{
    uint32  key_value;
    uint32  wdt_t1 = 0, wdt_t2 = 0;

    // �������
    KBD_PrinterTestFlag = false;
    KBD_PrinterTestCount = 0;

    // ��������Ϊ0
    KBD_CountValue = 0;
    
    // ������ĵ�Դ����
    key_value = KBD_GetPinLevelValue(KEY_HAL_POWER);
    if (key_value == 1)
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r KEY_POWER");
        #endif
            
        KBD_CountValue = KBD_CountValue | KEY_HAL_POWER;
        KBD_LongPress_POWER = TRUE;
    }
    else
    {
        KBD_LongPress_POWER = FALSE;
    }

    // ɨ��Ӳ��
    key_value = KBD_GetPinLevelValue(KEY_HAL_FEED);
    if (key_value == 1)
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r KEY_FEED");
        #endif
        
        KBD_CountValue = KBD_CountValue | KEY_HAL_FEED;
        KBD_LongPress_FEED = TRUE;
    }
    else
    {
        KBD_LongPress_FEED = FALSE;
    }
    
    // ������Դ����, ǿ�йػ�
    if (KBD_LongPress_POWER == TRUE)
    {
        if (KBD_LongPress_POWER_Count <= POWER_OffTime)
            KBD_LongPress_POWER_Count++;
        
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r ǿ�� %d ", KBD_LongPress_POWER_Count);
        #endif

        // �������²�����ػ�
        if (KBD_LongPress_POWER_Count >= POWER_OffTime)             // 3 ��ػ�
        {
            #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r �ϵ�");
            #endif

            // ���Ƶ�Դ״̬
            #if (POWER_SUPPORT == 1)
                POWER_Manager(PM_POWER,  DEF_OFF);        // ��ϵͳ��Դ
                POWER_Manager(PM_MOTOR,  DEF_OFF);        // �ص����Դ

                // ��״̬
                #if (LED_SUPPORT == 1)
                    LED_Switch(RED_LED,    DEF_OFF);
                    LED_Switch(BLUE_LED,   DEF_OFF);
                #endif
            #endif

            while (1)
            {
                if (0)  break;

                #if (DEBUG_SUPPORT == 1)
                    DBG_printf("&");
                #endif
            }
        }
    }
    else
    {
        KBD_LongPress_POWER_Count = 0;
    }

    // ����FEED3����ֽ
    if (KBD_LongPress_FEED == TRUE)
    {
        if (KBD_LongPress_FEED_Count <= FEED_Time)
            KBD_LongPress_FEED_Count++;

        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r ��ֽ %d ", KBD_LongPress_FEED_Count);
        #endif
    }
    else
    {
        KBD_LongPress_FEED_Count = 0;
    }

    // �޼�����
    if (KBD_CountValue == 0)                    
    {
        KBD_ReloadCount = 0;
        return;
    }

    // ��ֹһֱ����
    if (KBD_ReloadCount == 1)
        return;

    // ��ֹһֱ����
    KBD_ReloadCount = 1;
}




/*****************************************************************************************
��������:    void  KBD_Feed(void)
�汾��:        1.0.0
��������:    2009.09.14
����:        Ӱ����
����˵��:    �ж����ٽ�ֽ
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void KBD_Feed(void)
{

}




/*****************************************************************************************
��������:    void ConfigureKBD(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ���̳�ʼ��
�������:    ��
�������:    ��
����˵��:    ��  
*****************************************************************************************/
void ConfigureKBD(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureKBD... ");
#endif

    // KEY1 power
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(KEY_POWER_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = KEY_POWER;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_POWER_PORT , &GPIO_InitStructure);

    // KEY2 feed
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(KEY_FEED_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = KEY_FEED;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_FEED_PORT , &GPIO_InitStructure);

    // ��ֹ��������
    KBD_SetReloadCountValue(1);
}


#endif



