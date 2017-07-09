

#include "app_types.h"
#include "app_wdt.h"
#include "MX25L1602Drv.h"


#if (SPI_SUPPORT == 1)

/*
 * 移植本软件包时需要修改以下的函数或宏 
 */
#define     SSEL0_EN        (0 << 16)
#define     SSEL1_EN        (0 << 17)
#define     SSEL2_EN        (0 << 18)
#define     SSEL3_EN        (0 << 19)
#define     SSEL0_DIS       (1 << 16)
#define     SSEL1_DIS       (1 << 17)
#define     SSEL2_DIS       (1 << 18)
#define     SSEL3_DIS       (1 << 19)
#define     EOT_EN          (1 << 20)
#define     EOT_DIS         (0 << 20)
#define     EOF_EN          (1 << 21)
#define     EOF_DIS         (0 << 21)
#define     RXIGNORE_EN     (1 << 22)
#define     RXIGNORE_DIS    (0 << 22)
#define     FLEN(n)         (((n) - 1) << 24)

#define     SPI_CLK_HZ      (18000000)              // (18000000)


extern  uint32  SysTimeTick;


/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define SPI_PORT                    SPI2      
#define SPI_CLK                     RCC_APB1ENR_SPI2EN
#define SPI_GPIO_CLK                RCC_AHBPeriph_GPIOB
#define SPI_GPIO_PORT               GPIOB                       /* GPIOB*/

//#define SPI_CS_PIN                  GPIO_Pin_12                 /* PB.3 */
//#define SPI_CS_SOURCE               GPIO_PinSource12
//#define SPI_CS_AF                   GPIO_AF_0

#define SPI_SCK_PIN                 GPIO_Pin_13                 /* PB.3 */
#define SPI_SCK_SOURCE              GPIO_PinSource13
#define SPI_SCK_AF                  GPIO_AF_0

#define SPI_MISO_PIN                GPIO_Pin_14                 /* PB.4 */
#define SPI_MISO_SOURCE             GPIO_PinSource14
#define SPI_MISO_AF                 GPIO_AF_0

#define SPI_MOSI_PIN                GPIO_Pin_15                 /* PB.5 */
#define SPI_MOSI_SOURCE             GPIO_PinSource15
#define SPI_MOSI_AF                 GPIO_AF_0

#define SPI_FLASH                   GPIO_Pin_12                 /* PB.3 */
#define SPI_FLASH_PORT              GPIOB
#define SPI_FLASH_PORT_CLK          RCC_AHBPeriph_GPIOB

#define SPI_LATCH                   GPIO_Pin_10                 // P0.3
#define SPI_LATCH_PORT              GPIOB
#define SPI_LATCH_PORT_CLK          RCC_AHBPeriph_GPIOB  


#define SPI_FLASH_CS                1
#define SPI_LATCH_CS                2



void SSP_EnableCS(uint8 type, uint8 enable);


#if 1

#define FLASH_ENABLE               SSP_EnableCS(SPI_FLASH_CS, DEF_ON)
#define FLASH_DISABLE              SSP_EnableCS(SPI_FLASH_CS, DEF_OFF)


//----------- Flash Operation Command Definition -------

#define SPI_Flash_Read_CMD	            0x03
#define SPI_Flash_Sector_Erase	        0x20
#define SPI_Flash_Block_Erase	        0xD8
#define SPI_Flash_Chip_Erase	        0x60
#define SPI_Flash_Page_Program	        0x02
#define SPI_Flash_Read_Status	        0x05
#define SPI_Flash_Write_Status	        0x01
#define SPI_Flash_Write_Enable	        0x06
#define SPI_Flash_Write_Disable	        0x04
#define SPI_Flash_Read_ID	            0x9F
#define SPI_Flash_Read	                0x03
#define SPI_Flash_Fast_Read	            0x0B
#define SPI_Flash_Power_Down	        0xB9
#define SPI_Flash_Release_DP	        0xAB
#define SPI_Flash_Enter_4K	            0xA5
#define SPI_Flash_Exit_4K	            0xB5
#define SPI_Flash_Read_ES	            0xAB
#define SPI_Flash_Read_EMS	            0x90
#define SPI_Flash_Parallel_Mode	        0x55

//----------- Flash Status Port Definition ----------

#define C_Flash_Busy	                0x01
#define C_Flash_WEL	                    0x02	    // Write Enable Latch
#define C_Flash_BP0	                    0x04
#define C_Flash_BP1	                    0x08
#define C_Flash_BP2	                    0x10
#define C_Flash_BP3	                    0x20
#define C_Flash_PEE	                    0x40	    // Program Erase Error
#define C_Flash_SRWP	                0x80	    // Status Register Write Protect
#define DummyData	                    0x00
#define SET	                            0x01
#define	RESET	                        0x00


typedef struct {
    uint8 MXIC_ID;	// Producer
    uint8 MemType_ID;	// FLASH type
    uint8 MemDensity_ID;	// indentify Size of the FLASH
}FLASH_ID;


#if 0
void SPI2_Init(void)
{
    RCC->APB2ENR |= RCC_APB2Periph_SPI2|RCC_APB2Periph_GPIOA;
    
    GPIOA->CRL = 0x99934444;
    SPI2->CR1 |= SPI_Direction_2Lines_FullDuplex;
    SPI2->CR1 |= SPI_Mode_Master;
    SPI2->CR1 |= SPI_DataSize_8b;
    SPI2->CR1 |= SPI_CPOL_Low;
    SPI2->CR1 |= SPI_CPHA_1Edge;
    SPI2->CR2 |= (1<<2);	//SSOE
    SPI2->CR1 |= SPI_FirstBit_MSB;
    SPI2->CR1 |= SPI_BaudRatePrescaler_32;

    FLASH_DISABLE;

    SPI2->CR1 |= (1<<6);
}
#endif

uint8 SPI2_WriteRead_Data(uint8 dat)
{
    while((SPI2->SR&SPI_I2S_FLAG_TXE) == RESET);	//TX Buffer is empty
    SPI2->DR = dat;	//sent the TX Buffer's data out

    while((SPI2->SR&SPI_I2S_FLAG_RXNE) == RESET); //RX Buffer is not empty
    return(SPI2->DR);	//return the RX Buffer's data

}

FLASH_ID Flash_Read_ID(void)
{
    FLASH_ID Flash_id;

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Read_ID);
    Flash_id.MXIC_ID = SPI2_WriteRead_Data(DummyData);
    Flash_id.MemType_ID = SPI2_WriteRead_Data(DummyData);
    Flash_id.MemDensity_ID = SPI2_WriteRead_Data(DummyData);

    FLASH_DISABLE;

    #if (DEBUG_SUPPORT == 1)
        APP_printf("\n\r    Flash_id.MXIC_ID:0x%X ", Flash_id.MXIC_ID);
        APP_printf("\n\r    Flash_id.MemType_ID:0x%X ", Flash_id.MemType_ID);
        APP_printf("\n\r    Flash_id.MemDensity_ID:0x%X ", Flash_id.MemDensity_ID);
    #endif

    return Flash_id;
}

void Flash_Write_Enable(void)
{
    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Write_Enable);

    FLASH_DISABLE;
}

void Flash_Write_Disable(void)
{
    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Write_Disable);

    FLASH_DISABLE;
}

uint8 Flash_Read_Status_Register(void)
{
    uint8 data;

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Read_Status);

    data = SPI2_WriteRead_Data(DummyData);

    FLASH_DISABLE;

    return data;
}

void Flash_Write_Status_Register(uint8 dat)
{
    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Write_Status);

    SPI2_WriteRead_Data(dat);

    FLASH_DISABLE;
}

void Flash_Sector_Erase(uint16 Sector_idx)
{
    uint8 Sector_Addr_H;
    uint8 Sector_Addr_M;
    uint8 Sector_Addr_L;

    Sector_Addr_H = (uint8)(((Sector_idx*0x1000)&0x00ff0000)>>16);
    Sector_Addr_M = (uint8)(((Sector_idx*0x1000)&0x0000ff00)>>8);
    Sector_Addr_L = 0x00;

    Flash_Write_Enable();

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Sector_Erase);
    SPI2_WriteRead_Data(Sector_Addr_H);
    SPI2_WriteRead_Data(Sector_Addr_M);
    SPI2_WriteRead_Data(Sector_Addr_L);

    FLASH_DISABLE;

    while(Flash_Read_Status_Register()&C_Flash_Busy != RESET);
}

void Flash_Block_Erase(uint16 Block_idx)
{
    uint8 Block_Addr_H;
    uint8 Block_Addr_M;
    uint8 Block_Addr_L;

    Block_Addr_H = (uint8)(((Block_idx*0x10000)&0x00ff0000)>>16);
    Block_Addr_M = 0x00;
    Block_Addr_L = 0x00;

    Flash_Write_Enable();

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Block_Erase);
    SPI2_WriteRead_Data(Block_Addr_H);
    SPI2_WriteRead_Data(Block_Addr_M);
    SPI2_WriteRead_Data(Block_Addr_L);

    FLASH_DISABLE;

    while(Flash_Read_Status_Register()&C_Flash_Busy != RESET);
}

void Flash_Chip_Erase(void)
{
    Flash_Write_Enable();

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Chip_Erase);

    FLASH_DISABLE;

    while(Flash_Read_Status_Register()&C_Flash_Busy != RESET);
}

void Flash_WriteByte(uint32 data_addr, uint8 data)
{
    uint8 Data_Addr_H;
    uint8 Data_Addr_M;
    uint8 Data_Addr_L;

    Data_Addr_H = (uint8)(((data_addr*0x10000)&0x00ff0000)>>16);
    Data_Addr_M = (uint8)(((data_addr*0x10000)&0x0000ff00)>>8);
    Data_Addr_L = (uint8)((data_addr*0x10000)&0x000000ff);

    Flash_Write_Enable();

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Page_Program);
    SPI2_WriteRead_Data(Data_Addr_H);
    SPI2_WriteRead_Data(Data_Addr_M);
    SPI2_WriteRead_Data(Data_Addr_L);
    SPI2_WriteRead_Data(data);

    FLASH_DISABLE;

    while(Flash_Read_Status_Register()&C_Flash_Busy != RESET);
}

void Flash_WriteBytes(uint32 data_addr, uint8* ptdata, uint16 count)
{
    uint8 Data_Addr_H;
    uint8 Data_Addr_M;
    uint8 Data_Addr_L;

    Data_Addr_H = (uint8)(((data_addr*0x10000)&0x00ff0000)>>16);
    Data_Addr_M = (uint8)(((data_addr*0x10000)&0x0000ff00)>>8);
    Data_Addr_L = (uint8)((data_addr*0x10000)&0x000000ff);

    Flash_Write_Enable();

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Page_Program);
    SPI2_WriteRead_Data(Data_Addr_H);
    SPI2_WriteRead_Data(Data_Addr_M);
    SPI2_WriteRead_Data(Data_Addr_L);

    for(;count!=0;count--)
    {
        SPI2_WriteRead_Data(*(ptdata++));
    }

    FLASH_DISABLE;

    while(Flash_Read_Status_Register()&C_Flash_Busy != RESET);
}

void Flash_ReadBytes(uint32 data_addr,uint8* ptdata, uint16 count)
{
    uint8 Data_Addr_H;
    uint8 Data_Addr_M;
    uint8 Data_Addr_L;
	uint8 tmp;

    Data_Addr_H = (uint8)(((data_addr*0x10000)&0x00ff0000)>>16);
    Data_Addr_M = (uint8)(((data_addr*0x10000)&0x0000ff00)>>8);
    Data_Addr_L = (uint8)((data_addr*0x10000)&0x000000ff);
	Flash_Write_Disable();
    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Fast_Read);
    SPI2_WriteRead_Data(Data_Addr_H);
    SPI2_WriteRead_Data(Data_Addr_M);
    SPI2_WriteRead_Data(Data_Addr_L);
    SPI2_WriteRead_Data(DummyData);

    for(;count!=0;count--)
    {
        tmp = SPI2_WriteRead_Data(DummyData);
        //if (tmp != 0xff)
        //	APP_printf("GOT %x\r\n", tmp);
        *(ptdata++) = tmp;
    }

    FLASH_DISABLE;
}

uint8 Flash_ReadByte(uint32 data_addr)
{
    uint8 data;
    uint8 Data_Addr_H;
    uint8 Data_Addr_M;
    uint8 Data_Addr_L;

    Data_Addr_H = (uint8)(((data_addr*0x10000)&0x00ff0000)>>16);
    Data_Addr_M = (uint8)(((data_addr*0x10000)&0x0000ff00)>>8);
    Data_Addr_L = (uint8)((data_addr*0x10000)&0x000000ff);

    FLASH_ENABLE;

    SPI2_WriteRead_Data(SPI_Flash_Read);
    SPI2_WriteRead_Data(Data_Addr_H);
    SPI2_WriteRead_Data(Data_Addr_M);
    SPI2_WriteRead_Data(Data_Addr_L);

    data = SPI2_WriteRead_Data(DummyData);

    FLASH_DISABLE;

    return data;
}
#endif


#if 1

/*******************************************************************************
函数名称：SPI_Write_Byte()
功    能：向SPI总线发送一个数据
参    数：无
返回值  ：无
********************************************************************************/
uint8  SPI_WriteRead_Byte(uint8 txdat) 
{     
    /* 判断发送缓冲是否为空 */ 
    while((SPI_PORT->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
    SPI_SendData8(SPI_PORT, txdat);
    
    /* 判断接收缓冲是否为空*/
    while((SPI_PORT->SR & SPI_I2S_FLAG_RXNE) == (uint16_t)RESET);
    return SPI_ReceiveData8(SPI_PORT);   	  
}



/*******************************************************************************
* 函数名称: SSP_EnableCS()
* 功能描述: SPI2初始化--作为主设备实现
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void SSP_EnableCS(uint8 type, uint8 enable)
{  
    switch (type)
    {
        case SPI_FLASH_CS:
            if (enable == DEF_ON)
                GPIO_WriteBit(SPI_FLASH_PORT, SPI_FLASH, (BitAction)0);          // 
            else
                GPIO_WriteBit(SPI_FLASH_PORT, SPI_FLASH, (BitAction)1);          // 
            break;

        case SPI_LATCH_CS:
            if (enable == DEF_ON)
                GPIO_WriteBit(SPI_LATCH_PORT, SPI_LATCH, (BitAction)0);          // 
            else
                GPIO_WriteBit(SPI_LATCH_PORT, SPI_LATCH, (BitAction)1);          // 
            break;
    }
}


/*******************************2011-01-13******************************/  
/*功能:       SPI发送一个字节 
  *参数:       send_data:   待发送的字节 
  *返回:       无*/  
uint8 SpiFlashSendByte(uint8 send_data)  
{  
    /*检查Busy位，SPI的SR中的位7，SPI通信是否为忙，直到不忙跳出*/  
    //while( SET==SPI_I2S_GetFlagStatus(SPI_SELECT, SPI_I2S_FLAG_BSY));  
      
    /*检查TXE位，SPI的SR中的位1，发送缓冲器是否为空，直到空跳出*/  
    while( RESET==SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE));  
  
    SPI_SendData8(SPI2, send_data);                        /*发送一个字节*/  
      
    /*发送数据后再接收一个字节*/  
    while( RESET==SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) );  
    return( SPI_ReceiveData8(SPI2) );  
      
}  

/*******************************2011-01-13******************************/  
/*功能:       SPI接收flash的一个字节 
  *参数:       接收到的字节 
  *返回:       无*/  
uint8 SpiFlashReceiveByte(void)  
{  
    /*检查RXNE位，SPI的SR中位0，确定接收缓冲器是有数据的*/  
    return (SpiFlashSendByte(0xFF));  
}  


/*******************************************************************************
* 函数名称: SSP_Init()
* 功能描述: SPI2初始化--作为主设备实现
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void SSP_Init(void)
{  
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef   SPI_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r    SSP_Init... ");
#endif

    RCC_AHBPeriphClockCmd(SPI_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(SPI_CLK, ENABLE);

    // 配置SPI2: SCK    
    GPIO_InitStructure.GPIO_Pin   = SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(SPI_GPIO_PORT , &GPIO_InitStructure);

    // 配置SPI2: MISO   
    GPIO_InitStructure.GPIO_Pin   = SPI_MISO_PIN;
    GPIO_Init(SPI_GPIO_PORT , &GPIO_InitStructure);

    // 配置SPI2: MOSI   
    GPIO_InitStructure.GPIO_Pin   = SPI_MOSI_PIN;
    GPIO_Init(SPI_GPIO_PORT , &GPIO_InitStructure);

    // 片选
    //GPIO_InitStructure.GPIO_Pin   = SPI_CS_PIN;
    //GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    //GPIO_Init(SPI_CS_PIN , &GPIO_InitStructure);

    GPIO_PinAFConfig(SPI_GPIO_PORT, SPI_SCK_SOURCE , SPI_SCK_AF);
    GPIO_PinAFConfig(SPI_GPIO_PORT, SPI_MISO_SOURCE, SPI_MISO_AF);
    GPIO_PinAFConfig(SPI_GPIO_PORT, SPI_MOSI_SOURCE, SPI_MOSI_AF);	
    
    // SPI_FLASH 外部时钟使能
    RCC_AHBPeriphClockCmd(SPI_FLASH_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = SPI_FLASH;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_FLASH_PORT , &GPIO_InitStructure);
    SSP_EnableCS(SPI_FLASH_CS, DEF_OFF);
    
    // SPI_LATCH 外部时钟使能
    RCC_AHBPeriphClockCmd(SPI_LATCH_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = SPI_LATCH;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_LATCH_PORT , &GPIO_InitStructure);
    SSP_EnableCS(SPI_LATCH_CS, DEF_OFF);

    //SPI CONFIGURATION
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;      
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;          // SPI_BaudRatePrescaler_2
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
    SPI_InitStructure.SPI_CRCPolynomial = 7; 				
    SPI_Init(SPI_PORT, &SPI_InitStructure);

    //SPI_NSSInternalSoftwareConfig(SPI_PORT, SPI_NSSInternalSoft_Set);
    //SPI_RxFIFOThresholdConfig(SPI_PORT, SPI_RxFIFOThreshold_QF);

    SPI_Cmd(SPI_PORT, ENABLE); /* SPI enable */
}


#endif


#if 1


INT8U Motor_SendByte (INT8U *buffer, uint16 len)
{
    INT8U   ucData = 0;

#if (MX25L1602_SUPORT == 0)
    uint16  i;
    uint32  wdt_t1 = 0, wdt_t2 = 0;

    for (i = 0; i < len; i++)
    {
        wdt_t2 = SysTimeTick;
        if ((wdt_t2 - wdt_t1) >= WDT_DELAY)
        {
            #if (WDT_SUPPORT == 1) 
            WDTC_Clear();
            #endif

            wdt_t1 = wdt_t2;
        }

      //  dprintf("\n\r Motor_SendByte: %d", i);

        ucData = SpiFlashSendByte(0x30);                                     /* 接收数据                     */
    }
#endif

#if (MX25L1602_SUPORT == 1)
    uint16  i, sNum;
    uint32  wdt_t1 = 0, wdt_t2 = 0;

    if (len <= 3)
    {
        // dprintf("\n\r Motor_SendByte <= 3");
        return ucData;
    }
    
    // ========================
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪                 */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOF_EN | SSEL0_DIS | SSEL1_EN | SSEL2_DIS | SSEL3_DIS | buffer[0];       /* 8 位，传输开始，帧结束       */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成                 */
    ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                         */

    // ============================
    sNum = (len - 1);
    for (i = 1; i < sNum; i++)
    {
        wdt_t2 = SysTimeTick;
        if ((wdt_t2 - wdt_t1) >= WDT_DELAY)
        {
            #if (WDT_SUPPORT == 1) 
            WDTC_Clear();
            #endif

            wdt_t1 = wdt_t2;
        }

      //  dprintf("\n\r Motor_SendByte: %d", i);
        
        while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
        LPC_SPI0->TXDATCTL = FLEN(8) | EOF_EN | SSEL0_DIS | SSEL1_EN | SSEL2_DIS | SSEL3_DIS | buffer[i];   /* 8 位，帧结束                 */    
        
        while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
        ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                     */
    }

    // ==============================
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪                 */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOT_EN | SSEL0_DIS | SSEL1_EN | SSEL2_DIS | SSEL3_DIS | buffer[len-1];   /* 8 位，传输结束               */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成                 */
    ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                         */
#endif

    return ucData;
}




/*********************************************************************************************************
** 函数名称: SendRecv_Byte
** 函数功能：一次传输内部的单字节帧发送与接收
** 输入参数: 数据线上发送出的数据
** 输出参数: 数据线上接收到的数据
** 返 回 值：无
*********************************************************************************************************/
INT8U SendRecv_Byte (INT8U ucData)
{
#if (MX25L1602_SUPORT == 1)
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOF_EN | SSEL0_EN | SSEL1_DIS | SSEL2_DIS | SSEL3_DIS | ucData;      /* 8 位，帧结束                 */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
    ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                     */
#endif

#if (MX25L1602_SUPORT == 0)
    ucData = SpiFlashSendByte(ucData);
#endif

    return ucData;
}



/*********************************************************************************************************
** 函数名称: SendRecv_Start
** 函数功能：一次传输起始的单字节帧发送与接收
** 输入参数: 数据线上发送出的数据
** 输出参数: 数据线上接收到的数据
** 返 回 值：无
*********************************************************************************************************/
INT8U SendRecv_Start (INT8U ucData)
{
#if (MX25L1602_SUPORT == 1)
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOF_EN | SSEL0_EN | SSEL1_DIS | SSEL2_DIS | SSEL3_DIS | ucData;      /* 8 位，传输开始，帧结束       */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
    ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                     */
#endif

#if (MX25L1602_SUPORT == 0)
    ucData = SpiFlashSendByte(ucData);
#endif

    return ucData;
}



/*********************************************************************************************************
** 函数名称: SendRecv_Stop
** 函数功能：一次传输结束的单字节帧发送与接收
** 输入参数: 数据线上发送出的数据
** 输出参数: 数据线上接收到的数据
** 返 回 值：无
*********************************************************************************************************/
INT8U SendRecv_Stop (INT8U ucData)
{
#if (MX25L1602_SUPORT == 1)
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOT_EN | SSEL0_EN | SSEL1_DIS | SSEL2_DIS | SSEL3_DIS | ucData;      /* 8 位，传输结束               */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
    ucData = LPC_SPI0->RXDAT;                                           /* 接收数据                     */
#endif

    return ucData;
}


INT8U SendRecv_SizeByte (INT8U *buffer, uint16 len)
{
#if (MX25L1602_SUPORT == 1)
    uint16  i, sNum;
    uint32  wdt_t1 = 0, wdt_t2 = 0;

    // ====================================
    sNum = (len - 1);
    for (i = 0; i < sNum; i++) 
    {
        wdt_t2 = SysTimeTick;
        if ((wdt_t2 - wdt_t1) >= WDT_DELAY)
        {
            #if (WDT_SUPPORT == 1) 
            WDTC_Clear();
            #endif

            wdt_t1 = wdt_t2;
        }

       // dprintf("\n\r SendRecv_SizeByte: %d", i);

        while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
        LPC_SPI0->TXDATCTL = FLEN(8) | EOF_EN | SSEL0_EN | SSEL1_DIS | SSEL2_DIS | SSEL3_DIS | 0xFF;        /* 8 位，帧结束                 */    
        
        while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
        buffer[i] = LPC_SPI0->RXDAT;                                           /* 接收数据                  */
    
    }

    // ===================================
    while (!(LPC_SPI0->STAT & (1 << 1)));                               /* 等待发送准备就绪             */
    LPC_SPI0->TXDATCTL = FLEN(8) | EOT_EN | SSEL0_EN | SSEL1_DIS | SSEL2_DIS | SSEL3_DIS | 0xFF;        /* 8 位，传输结束               */    
    
    while (!(LPC_SPI0->STAT & (1 << 0)));                               /* 等待接收数据完成             */
    buffer[i] = LPC_SPI0->RXDAT;                                           /* 接收数据                  */
#endif

    return 0;
}

#endif



/*********************************************************************************************************
** 用户接口层
** 以下函数在移植时无需修改
*********************************************************************************************************/
/*********************************************************************************************************
** 函数名称:MX25L1602_RD
** 函数功能:MX25L1602的读函数,可选择读ID和读数据操作
** 输入参数:
**          INT32U Dst：目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**          INT32U NByte:  要读取的数据字节数
**          INT8U* RcvBufPt:接收缓存的指针
** 输出参数:操作成功则返回OK,失败则返回FALSE
** 特殊说明:若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
**********************************************************************************************************/
INT8U MX25L1602_RD(INT32U Dst, INT8U* RcvBufPt, INT32U NByte)
{
//  INT32U i = 0;

    if ((Dst+NByte > MAX_ADDR)||(NByte == 0))  return (FALSE);            /*  检查入口参数                */

    SendRecv_Start(0x0B);                                                 /* 发送读命令                   */  

    SendRecv_Byte(((Dst & 0xFFFFFF) >> 16));                              /* 发送地址信息:该地址为3个字节 */
    SendRecv_Byte(((Dst & 0xFFFF) >> 8));
    SendRecv_Byte(Dst & 0xFF);
    SendRecv_Byte(0xFF);                                                  /* 发送哑字，以便读取数据       */

#if 1
    SendRecv_SizeByte (RcvBufPt, NByte);
#endif

#if 0
    for (i = 0; i < NByte; i++) 
    {
        if (i == (NByte - 1))
        {
            RcvBufPt[i] = SendRecv_Stop(0xFF);
        } 
        else 
        {
            RcvBufPt[i] = SendRecv_Byte(0xFF);
        }
    }
#endif

    return (TRUE);
}



/*********************************************************************************************************
** 函数名称:MX25L1602_RdID
** 函数功能:MX25L1602的读ID函数,可选择读ID和读数据操作
** 输入参数:
**          idtype IDType:ID类型。用户可在Jedec_ID,Dev_ID,Manu_ID三者里选择
**          INT32U* RcvbufPt:存储ID变量的指针
** 输出参数:操作成功则返回OK,失败则返回FALSE
** 特殊说明:若填入的参数不符合要求，则返回FALSE
*********************************************************************************************************/
INT8U MX25L1602_RdID(idtype IDType, INT32U* RcvbufPt)
{
    INT32U temp = 0;
    
    if (IDType == Jedec_ID) {
        SSP_EnableCS(SPI_FLASH_CS, DEF_ON);
        SendRecv_Start(0x9F);                                           /* 开始：发送读ID命令(9Fh)      */
        temp = (temp | SendRecv_Byte(0xFF)) << 8;                       /* 接收数据第 1 个字节          */
        temp = (temp | SendRecv_Byte(0xFF)) << 8;                       /* 接收数据第 2 个字节          */
        temp = (temp | SendRecv_Stop(0xFF));                            /* 接收数据第 3 个字节：结束    */
        *RcvbufPt = temp;
        SSP_EnableCS(SPI_FLASH_CS, DEF_OFF);
        
        #if (DEBUG_SUPPORT == 10)
            APP_printf("\n\r    MX25L1602_RdID 1:0x%X ", temp);
        #endif

        return (TRUE);
    }
    if ((IDType == Manu_ID) || (IDType == Dev_ID)) {
        SSP_EnableCS(SPI_FLASH_CS, DEF_ON);
        SendRecv_Start(0x90);                                           /* 开始：发送读ID命令(90h)      */
        SendRecv_Byte(0x00);                                            /* 发送地址                     */
        SendRecv_Byte(0x00);                                            /* 发送地址                     */
        SendRecv_Byte(IDType);                                          /* 发送地址 - 不是00H就是01H    */ 
        temp = SendRecv_Stop(0xFF);                                     /* 接收获取的数据字节：结束     */
        *RcvbufPt = temp;
        SSP_EnableCS(SPI_FLASH_CS, DEF_OFF);

        #if (DEBUG_SUPPORT == 10)
            APP_printf("\n\r    MX25L1602_RdID 2:0x%X ", temp);
        #endif

        return (TRUE);
    } 

    return (FALSE);
}



/*********************************************************************************************************
** 函数名称:MX25L1602_WR
** 函数功能:MX25L1602的写函数，可写1个和多个数据到指定地址
** 输入参数:
**          INT32U Dst：目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**          INT8U* SndbufPt:发送缓存区指针
**          INT32U NByte:要写的数据字节数
** 输出参数:操作成功则返回OK,失败则返回FALSE
** 特殊说明:若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
*********************************************************************************************************/
INT8U MX25L1602_WR(INT32U Dst, INT8U* SndbufPt, INT32U NByte)
{
    INT32U temp = 0,i = 0,StatRgVal = 0;
    
    if (( (Dst+NByte-1 > MAX_ADDR)||(NByte == 0) )) {
        return (FALSE);                                                     /*  检查入口参数                */
    }

    SendRecv_Start(0x05);                                                 /* 开始：发送读SR命令(0x05)     */
    temp = SendRecv_Stop(0xFF);                                           /* 保存读得的SR值：结束         */

    SendRecv_Stop(0x50);                                                  /* 使能写状态寄存器命令(0x50)   */

    SendRecv_Start(0x01);                                                 /* 开始：发送写SR命令(0x01)     */
    SendRecv_Stop(0x00);                                                  /* 清0BPx位，使Flash芯片全区可写*/

    for(i = 0; i < NByte; i++) {
        SendRecv_Stop(0x06);                                                /* 发送写使能命令               */

        SendRecv_Start(0x02);                                               /* 发送字节数据烧写命令         */
        SendRecv_Byte((((Dst+i) & 0xFFFFFF) >> 16));                        /* 发送3个字节的地址信息        */
        SendRecv_Byte((((Dst+i) & 0xFFFF) >> 8));
        SendRecv_Byte((Dst+i) & 0xFF);
        SendRecv_Stop(SndbufPt[i]);                                         /* 发送被烧写的数据             */

        do {
            SendRecv_Start(0x05);                                           /* 开始：发送读SR命令(0x05)     */
            StatRgVal = SendRecv_Stop(0xFF);                                /* 保存读得的SR值：结束         */
        } while (StatRgVal == 0x03);                                        /* 一直等待，直到芯片空闲       */
    }

    SendRecv_Stop(0x06);                                                /* 发送写使能命令               */
    SendRecv_Stop(0x50);                                                /* 使能写状态寄存器命令(0x50)   */

    SendRecv_Start(0x01);                                               /* 发送写状态寄存器指令         */
    SendRecv_Stop(temp);                                                /* 恢复状态寄存器设置信息       */

    return (TRUE);
}



/*********************************************************************************************************
** 函数名称:MX25L1602_Erase
** 函数功能:根据指定的扇区号选取最高效的算法擦除
** 输入参数:
**          INT32U sec1：起始扇区号,范围(0~499)
**          INT32U sec2：终止扇区号,范围(0~499)
** 输出参数:操作成功则返回OK,失败则返回FALSE
*********************************************************************************************************/
INT8U MX25L1602_Erase(INT32U sec1, INT32U sec2)
{
    INT8U  temp1 = 0,temp2 = 0,StatRgVal = 0;
    INT32U SecnHdAddr = 0;
    INT32U no_SecsToEr = 0;                                               /* 要擦除的扇区数目             */
    INT32U CurSecToEr = 0;                                                /* 当前要擦除的扇区号           */

    /*
    *  检查入口参数
    */
    if ((sec1 > SEC_MAX)||(sec2 > SEC_MAX)) {
        return (FALSE);
    }

    SendRecv_Start(0x05);                                                 /* 开始：发送读SR命令(0x05)     */
    temp1 = SendRecv_Stop(0xFF);                                          /* 保存读得的SR值：结束         */

    SendRecv_Stop(0x50);                                                  /* 使能写状态寄存器命令(0x50)   */

    SendRecv_Start(0x01);                                                 /* 开始：发送写SR命令(0x01)     */
    SendRecv_Stop(0x00);                                                  /* 清0BPx位，使Flash芯片全区可写*/

    SendRecv_Stop(0x06);                                                  /* 发送写使能命令：结束         */

    /*
    * 如果用户输入的起始扇区号大于终止扇区号，则在内部作出调整
    */
    if (sec1 > sec2)
    {
        temp2 = sec1;
        sec1  = sec2;
        sec2  = temp2;
    }
    
    /*
    * 若起止扇区号相等则擦除单个扇区
    */
    if (sec1 == sec2)
    {
        SecnHdAddr = SEC_SIZE * sec1;                                       /* 计算扇区的起始地址           */
        SendRecv_Start(0x20);                                               /* 开始：发送扇区擦除指令       */
        SendRecv_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                     /* 发送3个字节的地址信息        */
        SendRecv_Byte(((SecnHdAddr & 0xFFFF) >> 8));  
        SendRecv_Stop(SecnHdAddr & 0xFF);
        do {
            SendRecv_Start(0x05);                                           /* 开始：发送读SR命令(0x05)     */
            StatRgVal = SendRecv_Stop(0xFF);                                /* 保存读得的SR值：结束         */
        } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲       */

        return (TRUE);
    }

    /*
    * 根据起始扇区和终止扇区间距调用最快速的擦除功能
    */

    if (sec2 - sec1 == SEC_MAX) {
        SendRecv_Stop(0x60);                                                /* 发送芯片擦除指令(60h or C7h) */
        do {
            SendRecv_Start(0x05);                                           /* 开始：发送读SR命令(0x05)     */
            StatRgVal = SendRecv_Stop(0xFF);                                /* 保存读得的SR值：结束         */
        } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲       */

        return (TRUE);
    }

    no_SecsToEr = sec2 - sec1 +1;                                         /* 获取要擦除的扇区数目         */
    CurSecToEr  = sec1;                                                   /* 从起始扇区开始擦除           */

    /*
    * 若两个扇区之间的间隔够大，则采取16扇区擦除算法
    */
    while (no_SecsToEr >= 16)
    {
        SendRecv_Stop(0x06);                                                /* 发送允许写命令               */

        SecnHdAddr = SEC_SIZE * CurSecToEr;                                 /* 计算扇区的起始地址           */
        SendRecv_Start(0xD8);                                               /* 发送64KB块擦除指令           */
        SendRecv_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                     /* 发送3个字节的地址信息        */
        SendRecv_Byte(((SecnHdAddr & 0xFFFF) >> 8));
        SendRecv_Stop(SecnHdAddr & 0xFF);
        do {        
            SendRecv_Start(0x05);                                           /* 开始：发送读SR命令(0x05)     */
            StatRgVal = SendRecv_Stop(0xFF);                                /* 保存读得的SR值：结束         */
        } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲       */
        CurSecToEr  += 16;                                                  /* 计算擦除了16个扇区后和擦除区 */
                                                                            /* 域相邻的待擦除扇区号         */
        no_SecsToEr -=  16;                                                 /* 对需擦除的扇区总数作出调整   */
    }

    /*
    * 采用扇区擦除算法擦除剩余的扇区
    */
    while (no_SecsToEr >= 1) {
        SendRecv_Stop(0x06);                                                /* 发送允许写命令               */

        SecnHdAddr = SEC_SIZE * CurSecToEr;                                 /* 计算扇区的起始地址           */
        SendRecv_Start(0x20);                                               /* 开始：发送扇区擦除指令       */
        SendRecv_Byte(((SecnHdAddr & 0xFFFFFF) >> 16));                     /* 发送3个字节的地址信息        */
        SendRecv_Byte(((SecnHdAddr & 0xFFFF) >> 8));  
        SendRecv_Stop(SecnHdAddr & 0xFF);
        do {
            SendRecv_Start(0x05);                                           /* 开始：发送读SR命令(0x05)     */
            StatRgVal = SendRecv_Stop(0xFF);                                /* 保存读得的SR值：结束         */
        } while (StatRgVal & 0x01);                                         /* 一直等待，直到芯片空闲       */
        CurSecToEr  += 1;
        no_SecsToEr -=  1;
    }

    /*
    * 擦除结束,恢复状态寄存器信息
    */
    SendRecv_Stop(0x06);                                                  /* 发送允许写命令               */
    SendRecv_Stop(0x50);                                                  /* 使状态寄存器可写             */

    SendRecv_Start(0x01);                                                 /* 发送写状态寄存器指令         */
    SendRecv_Stop(temp1);                                                 /* 恢复状态寄存器设置信息       */ 

    return (TRUE);
}


#endif



