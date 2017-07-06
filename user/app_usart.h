/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:            1.0.0
��������:        2009.09.10
�ļ���:            app_usart.h
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

#ifndef APP_USART_PRESENT
#define APP_USART_PRESENT

#ifdef  APP_USART_GLOBALS
    #define APP_USART_EXT
#else
    #define APP_USART_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.10
����˵��:   USART������
����˵��:   ��
*****************************************************************************************/
#define USART1_CACHE_SIZE                   (48 * 15)                   // USART1 �����С
#define USART2_CACHE_SIZE                   (48 * 75)                   // USART2 �����С




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.10
����˵��:   UART���ݻ�����
����˵��:   ��
*****************************************************************************************/
#if (USART1_SUPPORT == 1)
    APP_USART_EXT  uint8   USART1_BUFFERs[USART1_CACHE_SIZE];
    APP_USART_EXT  uint16  USART1_input;
    APP_USART_EXT  uint16  USART1_output;
#endif

#if (USART2_SUPPORT == 1)
    APP_USART_EXT  uint8   USART2_BUFFERs[USART2_CACHE_SIZE];
    APP_USART_EXT  uint16  USART2_input;
    APP_USART_EXT  uint16  USART2_output;
#endif




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.10
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_USART_EXT  void   USART1_Initialize(void);
APP_USART_EXT  void   USART2_Initialize(void);

APP_USART_EXT  void   USART1_PutPool(uint8 * uart_data, uint32 number);
APP_USART_EXT  void   USART2_PutPool(uint8 * uart_data, uint32 number);

APP_USART_EXT  uint8  USART1_GetBuffer(uint8 * uart_data);
APP_USART_EXT  uint8  USART2_GetBuffer(uint8 * uart_data);

APP_USART_EXT  uint8  USART1_SendBuffer(uint8 * uart_data, uint32 len);
APP_USART_EXT  uint8  USART2_SendBuffer(uint8 * uart_data, uint32 len);




#endif





