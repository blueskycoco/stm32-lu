/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:            1.0.0
��������:        2010.05.11
�ļ���:            app_cmd.c
����:            Ӱ����
����˵��:        debug�ļ�
����˵��:        ��
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#define  APP_CMD_GLOBALS
#include "app_types.h"
#include "app_cmd.h"
#include "app_adc.h"
#include "app_wdt.h"
#include "app_spi.h"
#include "app_pwm.h"
#include "app_debug.h"
#include "app_power.h"
#include "app_uart.h"
#include "app_usart.h"

#include "main.h"
#include "updata.h"
#include "config.h"
#include "MX25L1602Drv.h"




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2010.05.11
����˵��:   ����
����˵��:   ����Ӧ�ò㽨��Ӧ�ò�����
*****************************************************************************************/
extern  uint8    SYSTEM_read_key(uint8 * key);
extern  uint8    Motor_SendByte (INT8U *buffer, uint16 len);
extern  void     BEEP_Player(uint8 second);

extern  uint32   SysTimeTick;
extern  uint16   OpenRunDelay_COUNT;

extern  uint8    HZPrintBuff[HZPrintSIZE]; 




/*****************************************************************************************
��������:    uint8 TERMINAML_Paramer1_Opinion(uint8 type, char * str, uint8 number, uint32 rparamers)
�汾��:        1.0.0
��������:    2009.09.22
����:        Ӱ����
����˵��:    �������һ������
�������:    uint8 * str:  �����Ĳ����ַ���
            uint8 number:   �����ַ�������
            uint32 * rparamers: ���ز���ֵ
�������:    1: ����
            0: ��ȷ
����˵��:    10��������
*****************************************************************************************/
uint8 TERMINAML_Paramer1_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers)
{
    uint8  i;

    if (number == 0)
        return 1;

    * rparamers = 0;

    for (i = 0; i < number; i++)
    {
        if (type == 10)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                *rparamers = (*rparamers) * 10 + (str[i] - '0');
            else
                return 1;
        }
        else if (type == 16)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                    *rparamers = (*rparamers) * 16 + (str[i] - '0');
            else if ((str[i] >= 'A') && (str[i] <= 'F'))
                    *rparamers = (*rparamers) * 16 + (str[i] - 'A') + 10;
            else if ((str[i] >= 'a') && (str[i] <= 'f'))
                    *rparamers = (*rparamers) * 16 + (str[i] - 'a') + 10;
            else
                return 1;
        }
    }

    return 0;
}




/*****************************************************************************************
��������:    uint8 TERMINAML_Paramer2_Opinion(uint8 type, uint8 * str, uint8 number, uint32 * rparamers1, uint32 * rparamers)
�汾��:        1.0.0
��������:    2009.09.22
����:        Ӱ����
����˵��:    �������������
�������:    uint8 * str:  �����ַ���
            uint8 number:   �����ַ�������
            uint32 * rparamers1: ��һ������ֵ
            uint32 * rparamers2: �ڶ�������ֵ
�������:    1: ����
            0: ��ȷ
����˵��:    10��������
*****************************************************************************************/
uint8 TERMINAML_Paramer2_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2)
{
    uint8  i;

    if (number == 0)
        return 1;

    *rparamers1 = 0;
    *rparamers2 = 0;

    for (i = 0; i < number; i++)                                            // ��һ������
    {
        if (type == 10)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                *rparamers1 = (*rparamers1) * 10 + (str[i] - '0');
            else if (str[i] == ' ')
                break;
            else
                return 1;
        }
        else if (type == 16)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                *rparamers1 = (*rparamers1) * 16 + (str[i] - '0');
            else if ((str[i] >= 'A') && (str[i] <= 'F'))
                *rparamers1 = (*rparamers1) * 16 + (str[i] - 'A') + 10;
            else if ((str[i] >= 'a') && (str[i] <= 'f'))
                *rparamers1 = (*rparamers1) * 16 + (str[i] - 'a') + 10;
            else if (str[i] == ' ')
                break;
            else
                return 1;
        }
    }

    if (i == number)
        return 1;

    for (i = i + 1; i < number; i++)                                        // �ڶ�������
    {
        if (type == 10)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                *rparamers2 = (*rparamers2) * 10 + (str[i] - '0');
            else
                return 1;
        }
        else if (type == 16)
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
                    *rparamers2 = (*rparamers2) * 16 + (str[i] - '0');
            else if ((str[i] >= 'A') && (str[i] <= 'F'))
                    *rparamers2 = (*rparamers2) * 16 + (str[i] - 'A') + 10;
            else if ((str[i] >= 'a') && (str[i] <= 'f'))
                    *rparamers2 = (*rparamers2) * 16 + (str[i] - 'a') + 10;
            else
                return 1;
        }
    }

    return 0;
}


#if (DEBUG_SUPPORT == 1)


/*****************************************************************************************
��������:    void BSP_printer(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ��λϵͳ
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
 format mask:0, level:0: 0x77C4
 format mask:1, level:0: 0x72F3
 format mask:2, level:0: 0x7DAA
 format mask:3, level:0: 0x789D
 format mask:4, level:0: 0x662F
 format mask:5, level:0: 0x6318
 format mask:6, level:0: 0x6C41
 format mask:0, level:1: 0x5412
 format mask:1, level:1: 0x5125
 format mask:2, level:1: 0x5E7C
 format mask:3, level:1: 0x5B4B
 format mask:4, level:1: 0x45F9
 format mask:5, level:1: 0x40CE
 format mask:6, level:1: 0x4F97
 format mask:0, level:2: 0x355F
 format mask:1, level:2: 0x3068
 format mask:2, level:2: 0x3F31
 format mask:3, level:2: 0x3A06
 format mask:4, level:2: 0x24B4
 format mask:5, level:2: 0x2183
 format mask:6, level:2: 0x2EDA
 format mask:0, level:3: 0x1689
 format mask:1, level:3: 0x13BE
 format mask:2, level:3: 0x1CE7
 format mask:3, level:3: 0x19D0
 format mask:4, level:3: 0x0762
 format mask:5, level:3: 0x0255
 format mask:6, level:3: 0x0D0C
*****************************************************************************************/
void BSP_printer(char *paramer, uint16 len)
{
 
}




/*****************************************************************************************
��������:    void BSP_systems(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����ϵͳ��Ϣ
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_systems(char *paramer, uint16 len)
{
    TERMINAML_Systems();
}




/*****************************************************************************************
��������:    void BSP_uart_echo(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����(deeploves@163.com)
����˵��:    ��uart��������
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_uart_echo(char *paramer, uint16 len)
{
    char    UART_EchoStr[100];
    uint32  number;

#if (DEBUG_SUPPORT == 1)
    if (paramer != NULL)
        APP_printf("\n\r echo paramer:%s, %d", paramer, len);
#endif

    if (TERMINAML_Paramer1_Opinion(10, paramer, len, &number) == 0)
    {
        switch (number)
        {
            case 1:
                #if (USART1_SUPPORT == 1)
                    APP_printf("\n\r ��uart1�����ַ�: 1-1234567890");
                    APP_strcpy(UART_EchoStr, "1-1234567890");
                    USART1_SendBuffer((uint8 *)&UART_EchoStr, APP_strlen(UART_EchoStr));
                #endif
                break;

            case 2:
                #if (USART2_SUPPORT == 1)
                    APP_printf("\n\r ��uart2�����ַ�: 2-1234567890");
                    APP_strcpy(UART_EchoStr, "2-1234567890");
                    USART2_SendBuffer((uint8 *)&UART_EchoStr, APP_strlen(UART_EchoStr));
                #endif
                break;

            default:
                APP_printf("\n\r ��������");
                break;
        }

        return;
    }

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ��������");
#endif
}




/*****************************************************************************************
��������:    void BSP_iap(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����(deeploves@163.com)
����˵��:    ��uart��������
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_iap(char *paramer, uint16 len)
{

}




/*****************************************************************************************
��������:    void BSP_adc(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����(deeploves@163.com)
����˵��:    ��uart��������
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_adc(char *paramer, uint16 len)
{
    uint32  number;

#if (DEBUG_SUPPORT == 1)
    if (paramer != NULL)
        APP_printf("\n\r adc paramer:%s, %d", paramer, len);
#endif

    if (TERMINAML_Paramer1_Opinion(10, paramer, len, &number) == 0)
    {
        switch (number)
        {
            case 0:
                ADC_ChannelConfig(ADC1, ADC_BATT_CH,  ADC_SampleTime_239_5Cycles); 
                break;

            case 1:
                ADC_ChannelConfig(ADC1, ADC_PAPER_CH, ADC_SampleTime_239_5Cycles); 
                break;

            case 8:
                ADC_ChannelConfig(ADC1, ADC_TM_CH,    ADC_SampleTime_239_5Cycles); 
                break;

            default:
                APP_printf("\n\r ��������");
                break;
        }

        return;
    }
}




/*****************************************************************************************
��������:    void BSP_reboot(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����ϵͳ��Ϣ
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_reboot(char *paramer, uint16 len)
{
    uint8 value;
    
    while (1)
        value = value;
}




/*****************************************************************************************
��������:    void BSP_nibpsave(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ��������
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    ��
*****************************************************************************************/
void BSP_machineInfo(char *paramer, uint16 len)
{
    uint32  number;

    if (TERMINAML_Paramer1_Opinion(10, paramer, len, &number) == 0)
    {
        DBG_printf("\n\r machine:%d", number);
        
        #if (FLASH_SUPPORT == 1)
        Set_MachineCODE(number);
        #endif
    }
}




/*****************************************************************************************
��������:    void BSP_SetLanguage(char *paramer, uint16 len)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ���û������
�������:    char *paramer: �����д��ݲ���
            uint16 len: ��������
�������:    ��
����˵��:    machinecode 2013020001
*****************************************************************************************/
void BSP_SetLanguage(char *paramer, uint16 len)
{
    uint32  number;

    if (TERMINAML_Paramer1_Opinion(10, paramer, len, &number) == 0)
    {
        DBG_printf("\n\r language:%d", number);
        
        #if (FLASH_SUPPORT == 1)
        Set_LanguageType(number);
        #endif
    }
}




/*****************************************************************************************
��������:    void System(const char *command)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ϵͳ��������
�������:    char *command: �����д��ݲ���
�������:    ��
����˵��:    ��
*****************************************************************************************/
void System(const char *command)
{
    char  i, len, cmdstr[100];
    uint8 cmdlen;
    
    cmdlen = APP_strlen(command);

    if (cmdlen >= 100)
        return;

    APP_strcpy(cmdstr, command);
        
    if (SYSTEM_for_string((uint8 *)cmdstr, &cmdlen) == 0)
        return;

    for (i = 0; i < BSP_CMD_NUM; i++)        // (APP_sizeof(BSP_DBG_CMD) / APP_sizeof(BSP_ComnandInfo))
    {
        if (SYSTEM_for_command(cmdstr, APP_strlen(cmdstr)) != 0)
        {
            if (SYSTEM_for_command(cmdstr, APP_strlen(cmdstr)) > APP_strlen(BSP_DBG_CMD[i].Cmd))
                len = SYSTEM_for_command(cmdstr, APP_strlen(cmdstr));
            else
                len = APP_strlen(BSP_DBG_CMD[i].Cmd);
            
            if (APP_strncmp(BSP_DBG_CMD[i].Cmd, cmdstr, len) == 0)
            {
                len = SYSTEM_for_command(cmdstr, APP_strlen(cmdstr));

                if (APP_strlen(cmdstr) > len)
                    BSP_DBG_CMD[i].Command(&cmdstr[len + 1],  APP_strlen(cmdstr) - len - 1);
                else
                    BSP_DBG_CMD[i].Command(NULL,  0);

                return;
            }
        }
    }
}        




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2010.05.11
����˵��:   ȫ�ֱ���
����˵��:   ��
*****************************************************************************************/
const  BSP_ComnandInfo    BSP_DBG_CMD[BSP_CMD_NUM] = {
    {"sysinfo",     "sysinfo      ϵͳ��Ϣ \n\r",               &BSP_systems},
    {"echo",        "echo []      ��usrt�������� \n\r",         &BSP_uart_echo},
    {"reboot",      "reboot       ��λϵͳ \n\r",               &BSP_reboot},
    {"iap",         "iap          IAP�л� \n\r",                &BSP_iap},
    {"adc",         "adc          ADC�л� \n\r",                &BSP_adc},
    {"print",       "print        ������� \n\r",               &BSP_printer},
    {"language",    "language     �������� \n\r",               &BSP_SetLanguage},
    {"machine",     "machine      ������Ϣ \n\r",               &BSP_machineInfo}
};

#endif  



