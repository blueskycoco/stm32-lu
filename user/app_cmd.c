/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            app_cmd.c
作者:            影舞者
功能说明:        debug文件
其它说明:        无
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
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
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2010.05.11
功能说明:   函数
其它说明:   调用应用层建立应用层任务
*****************************************************************************************/
extern  uint8    SYSTEM_read_key(uint8 * key);
extern  uint8    Motor_SendByte (INT8U *buffer, uint16 len);
extern  void     BEEP_Player(uint8 second);

extern  uint32   SysTimeTick;
extern  uint16   OpenRunDelay_COUNT;

extern  uint8    HZPrintBuff[HZPrintSIZE]; 




/*****************************************************************************************
函数名称:    uint8 TERMINAML_Paramer1_Opinion(uint8 type, char * str, uint8 number, uint32 rparamers)
版本号:        1.0.0
生成日期:    2009.09.22
作者:        影舞者
功能说明:    分离出第一个参数
输入参数:    uint8 * str:  命令后的参数字符串
            uint8 number:   参数字符串长度
            uint32 * rparamers: 返回参数值
输出参数:    1: 错误
            0: 正确
其它说明:    10进制数据
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
函数名称:    uint8 TERMINAML_Paramer2_Opinion(uint8 type, uint8 * str, uint8 number, uint32 * rparamers1, uint32 * rparamers)
版本号:        1.0.0
生成日期:    2009.09.22
作者:        影舞者
功能说明:    分离出二个参数
输入参数:    uint8 * str:  参数字符串
            uint8 number:   参数字符串长度
            uint32 * rparamers1: 第一个参数值
            uint32 * rparamers2: 第二个参数值
输出参数:    1: 错误
            0: 正确
其它说明:    10进制数据
*****************************************************************************************/
uint8 TERMINAML_Paramer2_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2)
{
    uint8  i;

    if (number == 0)
        return 1;

    *rparamers1 = 0;
    *rparamers2 = 0;

    for (i = 0; i < number; i++)                                            // 第一个参数
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

    for (i = i + 1; i < number; i++)                                        // 第二个参数
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
函数名称:    void BSP_printer(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    复位系统
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
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
函数名称:    void BSP_systems(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    操作系统信息
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
*****************************************************************************************/
void BSP_systems(char *paramer, uint16 len)
{
    TERMINAML_Systems();
}




/*****************************************************************************************
函数名称:    void BSP_uart_echo(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者(deeploves@163.com)
功能说明:    向uart发送数据
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
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
                    APP_printf("\n\r 向uart1发送字符: 1-1234567890");
                    APP_strcpy(UART_EchoStr, "1-1234567890");
                    USART1_SendBuffer((uint8 *)&UART_EchoStr, APP_strlen(UART_EchoStr));
                #endif
                break;

            case 2:
                #if (USART2_SUPPORT == 1)
                    APP_printf("\n\r 向uart2发送字符: 2-1234567890");
                    APP_strcpy(UART_EchoStr, "2-1234567890");
                    USART2_SendBuffer((uint8 *)&UART_EchoStr, APP_strlen(UART_EchoStr));
                #endif
                break;

            default:
                APP_printf("\n\r 参数错误");
                break;
        }

        return;
    }

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r 参数错误");
#endif
}




/*****************************************************************************************
函数名称:    void BSP_iap(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者(deeploves@163.com)
功能说明:    向uart发送数据
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
*****************************************************************************************/
void BSP_iap(char *paramer, uint16 len)
{

}




/*****************************************************************************************
函数名称:    void BSP_adc(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者(deeploves@163.com)
功能说明:    向uart发送数据
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
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
                APP_printf("\n\r 参数错误");
                break;
        }

        return;
    }
}




/*****************************************************************************************
函数名称:    void BSP_reboot(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    操作系统信息
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
*****************************************************************************************/
void BSP_reboot(char *paramer, uint16 len)
{
    uint8 value;
    
    while (1)
        value = value;
}




/*****************************************************************************************
函数名称:    void BSP_nibpsave(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    重新配置
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    无
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
函数名称:    void BSP_SetLanguage(char *paramer, uint16 len)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    设置机器编号
输入参数:    char *paramer: 命令行传递参数
            uint16 len: 参数长度
输出参数:    无
其它说明:    machinecode 2013020001
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
函数名称:    void System(const char *command)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    系统调用命令
输入参数:    char *command: 命令行传递参数
输出参数:    无
其它说明:    无
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
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2010.05.11
功能说明:   全局变量
其它说明:   无
*****************************************************************************************/
const  BSP_ComnandInfo    BSP_DBG_CMD[BSP_CMD_NUM] = {
    {"sysinfo",     "sysinfo      系统信息 \n\r",               &BSP_systems},
    {"echo",        "echo []      向usrt发送数据 \n\r",         &BSP_uart_echo},
    {"reboot",      "reboot       复位系统 \n\r",               &BSP_reboot},
    {"iap",         "iap          IAP切换 \n\r",                &BSP_iap},
    {"adc",         "adc          ADC切换 \n\r",                &BSP_adc},
    {"print",       "print        电机测试 \n\r",               &BSP_printer},
    {"language",    "language     设置语言 \n\r",               &BSP_SetLanguage},
    {"machine",     "machine      机器信息 \n\r",               &BSP_machineInfo}
};

#endif  



