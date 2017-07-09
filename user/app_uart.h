/*****************************************************************************************
版权所有:        ---------------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_uart.h
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

#ifndef APP_UART_PRESENT
#define APP_UART_PRESENT

#ifdef  APP_UART_GLOBALS
    #define APP_UART_EXT
#else
    #define APP_UART_EXT    extern
#endif 




/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define UART2_BUSY                      GPIO_Pin_1                      // BUSY - P0.20 
#define UART2_BUSY_PORT                 GPIOA
#define UART2_BUSY_PORT_CLK             RCC_AHBPeriph_GPIOA




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   等级
其它说明:   无
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
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   等级
其它说明:   无
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
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   接口函数
其它说明:   无
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





