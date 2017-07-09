/*****************************************************************************************
版权所有:        -------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_uart.c
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

#define  APP_UART_GLOBALS
#include "app_types.h"
#include "app_uart.h"
#include "app_usart.h"




/*****************************************************************************************
函数名称:    void USART1_IRQHandler(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    UART1中断服务程序
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART1_IRQHandler(void)
{
    uint8  USART_Data;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_Data = USART_ReceiveData(USART1);

       // APP_printf("\n\r u1:%c", USART_Data);

        USART1_PutPool(&USART_Data, 1);
    }

    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}




/*****************************************************************************************
函数名称:    void USART2_IRQHandler(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    UART2中断服务程序
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART2_IRQHandler(void)
{
    uint8  USART_Data;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_Data = USART_ReceiveData(USART2);

       // APP_printf("\n\r u2:%c", USART_Data);

        USART2_PutPool((uint8 *)&USART_Data, 1);
    }

    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}




/*****************************************************************************************
函数名称:    void ConfigureUSART1(uint32 baudrate)
版本号:        1.0.0
生成日期:    0009.09.08
作者:        影舞者
功能说明:    配置UART1参数
输入参数:    uint32 baudrate
输出参数:    无
其它说明:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115000 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureUSART1(uint32 baudrate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    USART_InitTypeDef  USART_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureUSART1...%d ", baudrate);
#endif

    // 初始化缓冲区    
    USART1_Initialize();

	USART_DeInit(USART1);
    
    // 初始化芯片
    RCC_AHBPeriphClockCmd(USART1_PORT_CLK, ENABLE);          // 使能GPIOB端口
    RCC_APB2PeriphClockCmd(USART1_COM_CLK, ENABLE);          // 使能串口2时钟

    GPIO_PinAFConfig(USART1_PORT ,USART1_TX_SOURCE, USART1_TX_AF);
    GPIO_PinAFConfig(USART1_PORT ,USART1_RX_SOURCE, USART1_RX_AF);

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = USART1_TX ;                 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(USART1_PORT, &GPIO_InitStructure); 

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = USART1_RX ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_Init(USART1_PORT , &GPIO_InitStructure); 

    USART_InitStructure.USART_BaudRate   = baudrate;                 		      
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                         
    USART_InitStructure.USART_Parity     = USART_Parity_No;                            
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
    USART_Init(USART1, &USART_InitStructure); 	    //串口配置
        
	// NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_Cmd(USART1, ENABLE);

    USART_ClearFlag(USART1, USART_FLAG_TC);  
}




/*****************************************************************************************
函数名称:    void ConfigureUSART2(uint32 baudrate)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    配置UART2参数
输入参数:    uint32 baudrate
输出参数:    无
其它说明:    Configures USART2 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115200 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureUSART2(uint32 baudrate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    USART_InitTypeDef  USART_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureUSART2...%d ", baudrate);
#endif

    // 初始化缓冲区    
    USART2_Initialize();

	USART_DeInit(USART2);
    
    // 初始化芯片
    RCC_AHBPeriphClockCmd(USART2_PORT_CLK, ENABLE);          // 使能GPIOB端口
    RCC_APB1PeriphClockCmd(USART2_COM_CLK, ENABLE);          // 使能串口2时钟

    GPIO_PinAFConfig(USART2_PORT ,USART2_TX_SOURCE, USART2_TX_AF);
    GPIO_PinAFConfig(USART2_PORT ,USART2_RX_SOURCE, USART2_RX_AF);

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = USART2_TX ;                 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(USART2_PORT, &GPIO_InitStructure); 

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = USART2_RX ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_Init(USART2_PORT , &GPIO_InitStructure); 

    USART_InitStructure.USART_BaudRate   = baudrate;                 		      
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                         
    USART_InitStructure.USART_Parity     = USART_Parity_No;                            
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
    USART_Init(USART2, &USART_InitStructure); 	    //串口配置
        
	// NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	USART_Cmd(USART2, ENABLE);

    USART_ClearFlag(USART2, USART_FLAG_TC);  
}




/*****************************************************************************************
函数名称:    void USART2_BUSYStatus(uint8 status)
版本号:        1.0.0
生成日期:    0009.09.08
作者:        影舞者
功能说明:    配置UART2参数
输入参数:    uint32 baudrate
输出参数:    无
其它说明:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115000 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void USART2_BUSYStatus(uint8 status)
{
#if (USART_USE_BUSY == 1)
    if (status == false)
        GPIO_WriteBit(UART2_BUSY_PORT, UART2_BUSY,   (BitAction)false);
    else
        GPIO_WriteBit(UART2_BUSY_PORT, UART2_BUSY,   (BitAction)true);
#endif
}




/*****************************************************************************************
函数名称:    void ConfigureUSART_BUSY(void)
版本号:        1.0.0
生成日期:    0009.09.08
作者:        影舞者
功能说明:    配置UART1参数
输入参数:    uint32 baudrate
输出参数:    无
其它说明:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115000 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureUSART_BUSY(void)
{
#if (USART_USE_BUSY == 1)
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureUSART_BUSY... ");
#endif

    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(UART2_BUSY_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = UART2_BUSY;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART2_BUSY_PORT , &GPIO_InitStructure);

    // 无效值
    USART2_BUSYStatus(false);
#endif
}




/*****************************************************************************************
函数名称:    void USART_SendChar(USART_TypeDef* USART, uint8 c)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    发数据
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void USART_SendChar(USART_TypeDef* USART, uint8 c)
{
    while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART, c);
}




/*****************************************************************************************
函数名称:    uint8 USART_RecvChar(USART_TypeDef* USART, uint8 *c)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    发数据
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8 USART_RecvChar(USART_TypeDef* USART, uint8 *c)
{    
    uint8 result = ERROR;

    if (USART_GetFlagStatus(USART, USART_FLAG_RXNE) != RESET)
    {
        *c = (uint8)(USART_ReceiveData(USART));
        result = SUCCESS;
    }

    return (result);    
}



#if (DEBUG_SUPPORT == 1)


/*******************************************************************************
* 函数名称: DEBUG_PutChar()
* 功能描述: 通过UART发送一个字符
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void DEBUG_PutChar(uint8 c)
{
    USART_SendChar(F072RB_COM, c);  
}


/*******************************************************************************
* 函数名称: DEBUG_GetChar()
* 功能描述: 通过UART接收一个字符
* 输入参数: void
* 返回参数: 无
********************************************************************************/ 
uint8 DEBUG_GetChar(uint8 *c)
{    
    return USART_RecvChar(F072RB_COM, c);    
}


/*****************************************************************************************
函数名称:    void ConfigureDEBUG(uint32 baudrate)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    配置UART2参数
输入参数:    uint32 baudrate
输出参数:    无
其它说明:    Configures USART2 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115200 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureDEBUG(uint32 baudrate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    USART_InitTypeDef  USART_InitStructure;

	USART_DeInit(F072RB_COM);
    
    // 初始化芯片
    RCC_AHBPeriphClockCmd(F072RB_COM_PORT_CLK, ENABLE);         // 使能GPIOB端口
    RCC_APB2PeriphClockCmd(F072RB_COM_CLK, ENABLE);             // 使能串口2时钟

    GPIO_PinAFConfig(F072RB_COM_PORT ,F072RB_COM_TX_SOURCE, F072RB_COM_TX_AF);
    GPIO_PinAFConfig(F072RB_COM_PORT ,F072RB_COM_RX_SOURCE, F072RB_COM_RX_AF);

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = F072RB_COM_TX ;                 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(F072RB_COM_PORT, &GPIO_InitStructure); 

    // PA9==TX PA10-RX
    GPIO_InitStructure.GPIO_Pin   = F072RB_COM_RX ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
    GPIO_Init(F072RB_COM_PORT , &GPIO_InitStructure); 

    USART_InitStructure.USART_BaudRate   = baudrate;                 		      
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                         
    USART_InitStructure.USART_Parity     = USART_Parity_No;                            
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
    USART_Init(F072RB_COM, &USART_InitStructure); 	    //串口配置

	// NVIC
	NVIC_InitStructure.NVIC_IRQChannel = F072RB_COM_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(F072RB_COM, USART_IT_RXNE, DISABLE);
	USART_ITConfig(F072RB_COM, USART_IT_TXE, DISABLE);
	USART_Cmd(F072RB_COM, ENABLE);

    USART_ClearFlag(F072RB_COM, USART_FLAG_TC);  
}
#endif




