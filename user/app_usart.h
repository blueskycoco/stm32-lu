/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_usart.h
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

#ifndef APP_USART_PRESENT
#define APP_USART_PRESENT

#ifdef  APP_USART_GLOBALS
    #define APP_USART_EXT
#else
    #define APP_USART_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   USART缓冲区
其它说明:   无
*****************************************************************************************/
#define USART1_CACHE_SIZE                   (48 * 15)                   // USART1 缓冲大小
#define USART2_CACHE_SIZE                   (48 * 75)                   // USART2 缓冲大小




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   UART数据缓冲区
其它说明:   无
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
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   接口函数
其它说明:   无
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





