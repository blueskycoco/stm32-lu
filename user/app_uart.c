/*****************************************************************************************
��Ȩ����:        -------------
�汾��:            1.0.0
��������:        2009.09.10
�ļ���:            app_uart.c
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

#define  APP_UART_GLOBALS
#include "app_types.h"
#include "app_uart.h"
#include "app_usart.h"




/*****************************************************************************************
��������:    void USART1_IRQHandler(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    UART1�жϷ������
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void USART2_IRQHandler(void)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    UART2�жϷ������
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void ConfigureUSART1(uint32 baudrate)
�汾��:        1.0.0
��������:    0009.09.08
����:        Ӱ����
����˵��:    ����UART1����
�������:    uint32 baudrate
�������:    ��
����˵��:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
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

    // ��ʼ��������    
    USART1_Initialize();

	USART_DeInit(USART1);
    
    // ��ʼ��оƬ
    RCC_AHBPeriphClockCmd(USART1_PORT_CLK, ENABLE);          // ʹ��GPIOB�˿�
    RCC_APB2PeriphClockCmd(USART1_COM_CLK, ENABLE);          // ʹ�ܴ���2ʱ��

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
    USART_Init(USART1, &USART_InitStructure); 	    //��������
        
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
��������:    void ConfigureUSART2(uint32 baudrate)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����UART2����
�������:    uint32 baudrate
�������:    ��
����˵��:    Configures USART2 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
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

    // ��ʼ��������    
    USART2_Initialize();

	USART_DeInit(USART2);
    
    // ��ʼ��оƬ
    RCC_AHBPeriphClockCmd(USART2_PORT_CLK, ENABLE);          // ʹ��GPIOB�˿�
    RCC_APB1PeriphClockCmd(USART2_COM_CLK, ENABLE);          // ʹ�ܴ���2ʱ��

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
    USART_Init(USART2, &USART_InitStructure); 	    //��������
        
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
��������:    void USART2_BUSYStatus(uint8 status)
�汾��:        1.0.0
��������:    0009.09.08
����:        Ӱ����
����˵��:    ����UART2����
�������:    uint32 baudrate
�������:    ��
����˵��:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
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
��������:    void ConfigureUSART_BUSY(void)
�汾��:        1.0.0
��������:    0009.09.08
����:        Ӱ����
����˵��:    ����UART1����
�������:    uint32 baudrate
�������:    ��
����˵��:    Configures USART1 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115000 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureUSART_BUSY(void)
{
#if (USART_USE_BUSY == 1)
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureUSART_BUSY... ");
#endif

    // GPIOE �ⲿʱ��ʹ��
    RCC_AHBPeriphClockCmd(UART2_BUSY_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = UART2_BUSY;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART2_BUSY_PORT , &GPIO_InitStructure);

    // ��Чֵ
    USART2_BUSYStatus(false);
#endif
}




/*****************************************************************************************
��������:    void USART_SendChar(USART_TypeDef* USART, uint8 c)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    ������
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void USART_SendChar(USART_TypeDef* USART, uint8 c)
{
    while (USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART, c);
}




/*****************************************************************************************
��������:    uint8 USART_RecvChar(USART_TypeDef* USART, uint8 *c)
�汾��:        1.0.0
��������:    2009.09.10
����:        Ӱ����
����˵��:    ������
�������:    ��
�������:    ��
����˵��:    ��
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
* ��������: DEBUG_PutChar()
* ��������: ͨ��UART����һ���ַ�
* �������: void
* ���ز���: ��
********************************************************************************/
void DEBUG_PutChar(uint8 c)
{
    USART_SendChar(F072RB_COM, c);  
}


/*******************************************************************************
* ��������: DEBUG_GetChar()
* ��������: ͨ��UART����һ���ַ�
* �������: void
* ���ز���: ��
********************************************************************************/ 
uint8 DEBUG_GetChar(uint8 *c)
{    
    return USART_RecvChar(F072RB_COM, c);    
}


/*****************************************************************************************
��������:    void ConfigureDEBUG(uint32 baudrate)
�汾��:        1.0.0
��������:    2009.09.08
����:        Ӱ����
����˵��:    ����UART2����
�������:    uint32 baudrate
�������:    ��
����˵��:    Configures USART2 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
            bit, no parity, 115200 bauds and enables its transmitter and receiver.
*****************************************************************************************/
void ConfigureDEBUG(uint32 baudrate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    USART_InitTypeDef  USART_InitStructure;

	USART_DeInit(F072RB_COM);
    
    // ��ʼ��оƬ
    RCC_AHBPeriphClockCmd(F072RB_COM_PORT_CLK, ENABLE);         // ʹ��GPIOB�˿�
    RCC_APB2PeriphClockCmd(F072RB_COM_CLK, ENABLE);             // ʹ�ܴ���2ʱ��

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
    USART_Init(F072RB_COM, &USART_InitStructure); 	    //��������

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




