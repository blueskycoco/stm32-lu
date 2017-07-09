/*****************************************************************************************
��Ȩ����:        ---------------------
�汾��:            1.0.0
��������:        2009.09.10
�ļ���:            app_uart.h
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

#ifndef APP_UART_PRESENT
#define APP_UART_PRESENT

#ifdef  APP_UART_GLOBALS
    #define APP_UART_EXT
#else
    #define APP_UART_EXT    extern
#endif 




/*********************************************************************************************************
  �궨��
*********************************************************************************************************/
#define UART2_BUSY                      GPIO_Pin_1                      // BUSY - P0.20 
#define UART2_BUSY_PORT                 GPIOA
#define UART2_BUSY_PORT_CLK             RCC_AHBPeriph_GPIOA




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �ȼ�
����˵��:   ��
*****************************************************************************************/
#define USART1_TX                   GPIO_Pin_9                          // TX
#define USART1_RX                   GPIO_Pin_10                         // RX
#define USART1_COM_CLK              RCC_APB2Periph_USART1
#define USART1_PORT                 GPIOA
#define USART1_PORT_CLK             RCC_AHBPeriph_GPIOA
#define USART1_TX_SOURCE            GPIO_PinSource9
#define USART1_TX_AF                GPIO_AF_1
#define USART1_RX_SOURCE            GPIO_PinSource10
#define USART1_RX_AF                GPIO_AF_1

#define USART2_TX                   GPIO_Pin_2                          // TX
#define USART2_RX                   GPIO_Pin_3                          // RX
#define USART2_COM_CLK              RCC_APB1Periph_USART2
#define USART2_PORT                 GPIOA
#define USART2_PORT_CLK             RCC_AHBPeriph_GPIOA
#define USART2_TX_SOURCE            GPIO_PinSource2
#define USART2_TX_AF                GPIO_AF_1
#define USART2_RX_SOURCE            GPIO_PinSource3
#define USART2_RX_AF                GPIO_AF_1




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �ȼ�
����˵��:   ��
*****************************************************************************************/
#define F072RB_COM                      USART1
#define F072RB_COM_TX                   GPIO_Pin_9
#define F072RB_COM_RX                   GPIO_Pin_10
#define F072RB_COM_CLK                  RCC_APB2Periph_USART1
#define F072RB_COM_PORT                 GPIOA
#define F072RB_COM_PORT_CLK             RCC_AHBPeriph_GPIOA
#define F072RB_COM_TX_SOURCE            GPIO_PinSource9
#define F072RB_COM_TX_AF                GPIO_AF_1
#define F072RB_COM_RX_SOURCE            GPIO_PinSource10
#define F072RB_COM_RX_AF                GPIO_AF_1
#define F072RB_COM_IRQn                 USART1_IRQn




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.10
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_UART_EXT  void   UART1_IRQHandler(void);
APP_UART_EXT  void   UART2_IRQHandler(void);

APP_UART_EXT  void   USART2_BUSYStatus(uint8 status);

APP_UART_EXT  void   ConfigureUSART_BUSY(void);

APP_UART_EXT  void   ConfigureUSART1(uint32 baudrate);
APP_UART_EXT  void   ConfigureUSART2(uint32 baudrate);

APP_UART_EXT  void   USART_SendChar(USART_TypeDef* USART, uint8 c);
APP_UART_EXT  uint8  USART_RecvChar(USART_TypeDef* USART, uint8 *c);
    
APP_UART_EXT  uint8  DEBUG_GetChar(uint8 *c);
APP_UART_EXT  void   DEBUG_PutChar(uint8 c);
APP_UART_EXT  void   ConfigureDEBUG(uint32 baudrate);


#endif





