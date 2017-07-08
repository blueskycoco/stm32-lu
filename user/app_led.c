/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:            1.0.0
��������:        2009.09.09
�ļ���:            app_led.c
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

#define  APP_LED_GLOBALS
#include "app_types.h"
#include "app_led.h"



#if (LED_SUPPORT == 1)




/*****************************************************************************************
��Ȩ����:    Ӱ����
�汾��:        1.0.0
��������:    2009.09.14
����˵��:    ����
����˵��:    ��
*****************************************************************************************/
uint8    led_level_status;
uint8    flush_red_run_flag = false;

extern  uint8  BlueLinkOK;




/*****************************************************************************************
��������:    void LED_Switch(uint8 key, uint8 status)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����LED����
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void LED_Switch(uint8 key, uint8 status)
{
    switch (key)
    {
        case RED_LED:
            if (status == DEF_ON)
                GPIO_WriteBit(LED_RED_PORT, LED_RED_PIN, (BitAction)0);          // ����LED
            else
                GPIO_WriteBit(LED_RED_PORT, LED_RED_PIN, (BitAction)1);          // Ϩ��LED
            break;

        case BLUE_LED:
            if (status == DEF_ON)
                GPIO_WriteBit(LED_BLUE_PORT, LED_BLUE_PIN, (BitAction)0);        // ����LED
            else
                GPIO_WriteBit(LED_BLUE_PORT, LED_BLUE_PIN, (BitAction)1);        // Ϩ��LED
            break;

        default:
            break;
    };
}




/*****************************************************************************************
��������:    void  LED_FlushScanf(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����LED����, 50ms����һ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  LED_FlushScanf(void)
{
    // ״̬��ת
    if (led_level_status == 0)
        led_level_status = 1;
    else
        led_level_status = 0;

    // ����״̬,����δ����������
    if (BlueLinkOK == false)
    {
        if (led_level_status == 0)
            LED_Switch(BLUE_LED, DEF_OFF);
        else
            LED_Switch(BLUE_LED, DEF_ON);
    }
    else
    {
        // ����BT�ɹ�, ���Ƴ���
        LED_Switch(BLUE_LED, DEF_ON);
    }

    // �͵�ѹ,�����
    if (flush_red_run_flag == true)
    {
        if (led_level_status == 0)
            LED_Switch(RED_LED, DEF_OFF);
        else
            LED_Switch(RED_LED, DEF_ON);
    }
}




/*****************************************************************************************
��������:    void ConfigureLED(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����LED��ʼ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void ConfigureLED(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureLED... ");
#endif

    // ���, ���� LED�ƶ˿� �ⲿ�������ģʽ
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(LED_RED_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED_RED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_RED_PORT , &GPIO_InitStructure);


    // ����, ���� LED�ƶ˿� �ⲿ�������ģʽ
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(LED_BLUE_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED_BLUE_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_BLUE_PORT , &GPIO_InitStructure);

    //�ر�LED
    LED_Switch(RED_LED,    DEF_OFF);
    LED_Switch(BLUE_LED,   DEF_OFF);
}


#endif



