/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_usart.c
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

#define  APP_USART_GLOBALS
#include "app_types.h"
#include "app_uart.h"
#include "app_usart.h"




/*****************************************************************************************
函数名称:    void USART_SendBuffer(uint8 port, uint8 * ch, uint8 len)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    发数据
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8 USART_SendBuffer(uint8 port, uint8 * ch, uint32 len)
{
    uint16  i;

    switch (port)
    {
        case 1:
            #if (USART1_SUPPORT == 1)
            for (i = 0; i < len; i++)
                USART_SendChar(USART1, ch[i]);
            #endif
            break;

        case 2:
            #if (USART2_SUPPORT == 1)
            for (i = 0; i < len; i++)
                USART_SendChar(USART2, ch[i]);
            #endif
            break;
    }

    return 0;
}




/*****************************************************************************************
函数名称:    void USART1_PutPool(uint8 * uart_data, uint32 number)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART2入缓冲区
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART1_PutPool(uint8 * uart_data, uint32 number)
{
#if (USART1_SUPPORT == 1)
    uint32  i;

    for (i = 0; i < number; i++)
    {
        if (USART1_input >= USART1_CACHE_SIZE)
            USART1_input = 0;

        USART1_BUFFERs[USART1_input] = uart_data[i];

        USART1_input++;
    }
#endif
}




/*****************************************************************************************
函数名称:    void USART2_PutPool(uint8 * uart_data, uint32 number)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART2入缓冲区
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART2_PutPool(uint8 * uart_data, uint32 number)
{
#if (USART2_SUPPORT == 1)
    uint32  i;
   
    for (i = 0; i < number; i++)
    {
        if (USART2_input >= USART2_CACHE_SIZE)
            USART2_input = 0;

        USART2_BUFFERs[USART2_input] = uart_data[i];

        USART2_input++;
    }
#endif
}




/*****************************************************************************************
函数名称:    uint8 USART1_GetBuffer(uint8 * uart_data)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART2出缓冲区
输入参数:    0: 有数据
             1: 无数据
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8 USART1_GetBuffer(uint8 * uart_data)
{
#if (USART1_SUPPORT == 0)
    return 1;
#endif

#if (USART1_SUPPORT == 1)
    if (USART1_output == USART1_input)
    {
        return 1;
    }

    if (USART1_output >= USART1_CACHE_SIZE)
        USART1_output = 0;

    *uart_data = USART1_BUFFERs[USART1_output];

    USART1_output++;

    return 0;
#endif
}




/*****************************************************************************************
函数名称:    uint8 USART2_GetBuffer(uint8 * uart_data)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART2出缓冲区
输入参数:    0: 有数据
            1: 无数据
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8 USART2_GetBuffer(uint8 * uart_data)
{
#if (USART2_SUPPORT == 0)
    return 1;
#endif

#if (USART2_SUPPORT == 1)
    if (USART2_output == USART2_input)
    {
        return 1;
    }

    if (USART2_output >= USART2_CACHE_SIZE)
        USART2_output = 0;

    *uart_data = USART2_BUFFERs[USART2_output];

    USART2_output++;

    return 0;
#endif
}




/*****************************************************************************************
函数名称:    void USART1_Initialize(void)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    协议初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART1_Initialize(void)
{
#if (USART1_SUPPORT == 1)
    USART1_input      = 0;
    USART1_output     = 0;
#endif
}




/*****************************************************************************************
函数名称:    void USART2_Initialize(void)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    协议初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART2_Initialize(void)
{
#if (USART2_SUPPORT == 1)
    USART2_input  = 0;
    USART2_output = 0;
#endif
}




/*****************************************************************************************
函数名称:    uint8 USART1_SendBuffer(uint8 * uart_data, uint32 len)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART1发送数据
输入参数:    uint8 * uart_data: 数据
            uint32 len: 长度
输出参数:    1: 成功
            0: 失败
其它说明:    无
*****************************************************************************************/
uint8 USART1_SendBuffer(uint8 * uart_data, uint32 len)
{
#if (USART1_SUPPORT == 0)
    return 0;
#endif

#if (USART1_SUPPORT == 1)
    USART_SendBuffer(1, uart_data, len);
    return 1;
#endif
}




/*****************************************************************************************
函数名称:    uint8 USART2_SendBuffer(uint8 * uart_data, uint32 len)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    USART2发送数据
输入参数:    uint8 * uart_data: 数据
            uint32 len: 长度
输出参数:    1: 成功
            0: 失败
其它说明:    无
*****************************************************************************************/
uint8 USART2_SendBuffer(uint8 * uart_data, uint32 len)
{
#if (USART2_SUPPORT == 0)
    return 0;
#endif

#if (USART2_SUPPORT == 1)
    USART_SendBuffer(2, uart_data, len);
    return 1;
#endif
}




