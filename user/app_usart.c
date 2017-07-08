/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:            1.0.0
��������:        2009.09.10
�ļ���:            app_usart.c
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

#define  APP_USART_GLOBALS
#include "app_types.h"
#include "app_uart.h"
#include "app_usart.h"




/*****************************************************************************************
��������:    void USART_SendBuffer(uint8 port, uint8 * ch, uint8 len)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    ������
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void USART1_PutPool(uint8 * uart_data, uint32 number)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART2�뻺����
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void USART2_PutPool(uint8 * uart_data, uint32 number)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART2�뻺����
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    uint8 USART1_GetBuffer(uint8 * uart_data)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART2��������
�������:    0: ������
             1: ������
�������:    ��
����˵��:    ��
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
��������:    uint8 USART2_GetBuffer(uint8 * uart_data)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART2��������
�������:    0: ������
            1: ������
�������:    ��
����˵��:    ��
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
��������:    void USART1_Initialize(void)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    Э���ʼ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void USART1_Initialize(void)
{
#if (USART1_SUPPORT == 1)
    USART1_input      = 0;
    USART1_output     = 0;
#endif
}




/*****************************************************************************************
��������:    void USART2_Initialize(void)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    Э���ʼ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void USART2_Initialize(void)
{
#if (USART2_SUPPORT == 1)
    USART2_input  = 0;
    USART2_output = 0;
#endif
}




/*****************************************************************************************
��������:    uint8 USART1_SendBuffer(uint8 * uart_data, uint32 len)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART1��������
�������:    uint8 * uart_data: ����
            uint32 len: ����
�������:    1: �ɹ�
            0: ʧ��
����˵��:    ��
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
��������:    uint8 USART2_SendBuffer(uint8 * uart_data, uint32 len)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    USART2��������
�������:    uint8 * uart_data: ����
            uint32 len: ����
�������:    1: �ɹ�
            0: ʧ��
����˵��:    ��
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




