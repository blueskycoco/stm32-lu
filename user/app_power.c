/*****************************************************************************************
��Ȩ����:        ----------------------
�汾��:            1.0.0
��������:        2009.09.09
�ļ���:            app_power.c
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

#define  APP_POWER_GLOBALS
#include "app_types.h"
#include "app_power.h"



#if (POWER_SUPPORT == 1)



/*****************************************************************************************
��������:    void  POWER_Manager (uint8 type, uint8 status) 
�汾��:        1.0.1
��������:    2008.07.30
����:        Ӱ����
����˵��:    �豸��Դ����
�������:    uint8 type:   �豸
            uint8 on_off: ��Դ״̬
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  POWER_Manager (uint8 type, uint8 status) 
{
    switch(type)
    {
        case PM_POWER:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_POWER_PORT, PW_PIN_POWER, (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_POWER_PORT, PW_PIN_POWER, (BitAction)0);
                break;

        case PM_MOTOR:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN, (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN, (BitAction)0);
                break;

        #if (PWM_SUPPORT == 0)
        case PM_BEEP:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_BEEP_PORT,  PW_PIN_BEEP,  (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_BEEP_PORT,  PW_PIN_BEEP,  (BitAction)0);
                break;
        #endif
    }
}




/*****************************************************************************************
��������:    uint8  POWER_StatusIO (uint8 type) 
�汾��:        1.0.1
��������:    2008.07.30
����:        Ӱ����
����˵��:    �豸��Դ����
�������:    uint8 type:   �豸
            uint8 on_off: ��Դ״̬
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint8  POWER_StatusIO (uint8 type) 
{
    switch(type)
    {
        case PM_POWER:
            return  GPIO_ReadOutputDataBit(PW_PIN_POWER_PORT, PW_PIN_POWER);
            
        case PM_MOTOR:
            return  GPIO_ReadOutputDataBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN);
            
        case PM_BEEP:
            return  GPIO_ReadOutputDataBit(PW_PIN_BEEP_PORT, PW_PIN_BEEP);
    }

    return 0;
}




/*****************************************************************************************
��������:    void ConfigurePOWER(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ��ʼ����Դ�������� 
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void ConfigurePOWER(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigurePOWER... ");
#endif
    
    // POWER��Դ����
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(PW_PIN_POWER_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_POWER;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_POWER_PORT , &GPIO_InitStructure);

    // VH_EN��Դ����
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(PW_PIN_VH_EN_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_VH_EN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_VH_EN_PORT , &GPIO_InitStructure);

#if (PWM_SUPPORT == 0)
    // BEEP��Դ����
    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(PW_PIN_BEEP_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_BEEP;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_BEEP_PORT , &GPIO_InitStructure);
#endif

    // �򿪻����ĵ�Դ  
    POWER_Manager(PM_POWER,  DEF_OFF);                  // �ر� ϵͳ ��Դ
    POWER_Manager(PM_MOTOR,  DEF_OFF);                  // �ر� ��� ��Դ  
    POWER_Manager(PM_BEEP,   DEF_OFF);                  // �ر� ���� ��Դ
}


#endif



