/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_sspi.c
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

#define  APP_SPI_GLOBALS
#include "app_types.h"
#include "app_debug.h"
#include "app_spi.h"
#include "app_wdt.h"

#include "MX25L1602Drv.h"
#include "updata.h"


#if (SPI_SUPPORT == 1)


/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
uint32_t GuiChipID = 0;

extern  uint8   flash_down_Flag;
extern  uint16  flash_down_timer;

extern  uint32  SysTimeTick;



/*****************************************************************************************
函数名称:    void ConfigureSSPI0(uint8 uart, uint32 baudrate)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    协议初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void ConfigureSPI(void)
{
#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureSPI... ");
#endif

    SSP_Init();

    //Flash_Read_ID();
    
#if 0
    MX25L1602_RdID(Jedec_ID, &GuiChipID);                               /* 读取Flash器件ID              */
    GuiChipID &= ~0xff000000;                                           /* 仅保留低24位数据             */
    if (GuiChipID != 0x00C22015)                                        /* GuiChipID的值是否0x00c22015  */
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r    GuiChipID != 0x00C22015 (0x%X) ",GuiChipID);
        #endif

        return;
    }  
#endif    
}



uint8  FONT_Erase(uint32 addr,  uint32 sizeLen)
{
    uint8   result;
    uint32  i, sector1, sector2;
    uint32  wdt_t1 = 0, wdt_t2 = 0;
    
    #if (DEBUG_SUPPORT == 1)
    //APP_printf("\n\r    FONT_Erase... ");
    #endif
    
    sector1 = addr / SEC_SIZE;
    sector2 = (addr + sizeLen - 1) / SEC_SIZE;

    #if (DEBUG_SUPPORT == 1)
    //APP_printf(": %d-%d: ", sector1, sector2);
    #endif

    for (i = sector1; i <= sector2; i++)
    {
        #if (DEBUG_SUPPORT == 10)
        //APP_printf("-%d", i);
        #endif

        wdt_t2 = SysTimeTick;
        if ((wdt_t2 - wdt_t1) >= WDT_DELAY)
        {
            #if (WDT_SUPPORT == 1) 
            WDTC_Clear();
            #endif

            wdt_t1 = wdt_t2;
        }

        #if (UPDATA_SUPPORT == 1)
        flash_down_Flag  = TRUE;                // 清定时器
        flash_down_timer = 0;

        if ((i %10) == 0)
            RequestFrameUPDATA(0xFFFF);         // 清上位机定时器
        #endif

        result = MX25L1602_Erase(i, i); 
        if (result == FALSE)
        {
            #if (DEBUG_SUPPORT == 1)
            //APP_printf("\n\r    MX25L1602_WR: %d-%d fail ", sector1, sector2);
            #endif
        }
    }

    return 1;
}


uint32 FONT_writebyte(uint32 addr, uint8 *buffer, uint16 len)
{
    uint8   result;
    
    #if (DEBUG_SUPPORT == 10)
    //APP_printf("\n\r FONT_writebyte...addr :%d(%d)", addr, len);
    #endif

    result = MX25L1602_WR(addr, buffer, len); 
    if (result == FALSE)
    {
        #if (DEBUG_SUPPORT == 1)
        //APP_printf("\n\r    MX25L1602_WR: 0x%x fail ", addr);
        #endif

        return 0;
    }

    return len;
}



uint32 FONT_readbyte (uint32 addr, uint8 *buffer, uint16 len)
{
    uint8  result;
    
    #if (DEBUG_SUPPORT == 10)
    //APP_printf("\n\r    FONT_readbyte...addr:%d,%d ", addr, len);
    #endif

    result = MX25L1602_RD(addr, buffer, len);
    if (result == FALSE)
    {
        #if (DEBUG_SUPPORT == 1)
        //APP_printf("\n\r    MX25L1602_RD: 0x%x fail ", addr);
        #endif

        return 0;
    }
        
    return len;
}



uint32 EEPROM_writebyte(uint32 addr, uint8 *buffer, uint16 len)
{
    uint8   result;
    uint32  sector1, sector2;
    
    #if (DEBUG_SUPPORT == 1)
    //APP_printf("\n\r    EEPROM_writebyte... ");
    #endif
    
    sector1 = addr / SEC_SIZE;
    sector2 = (addr + len - 1) / SEC_SIZE;

    #if (DEBUG_SUPPORT == 1)
    //APP_printf(": %d-%d", sector1, sector2);
    #endif

    result = MX25L1602_Erase(sector1, sector2); 
    if (result == FALSE)
    {
        #if (DEBUG_SUPPORT == 1)
        //APP_printf("\n\r    MX25L1602_WR: %d-%d fail ", sector1, sector2);
        #endif

        return 0;
    }

    result = MX25L1602_WR(addr, buffer, len); 
    if (result == FALSE)
    {
        #if (DEBUG_SUPPORT == 1)
        //APP_printf("\n\r    MX25L1602_WR: 0x%x fail ", addr);
        #endif

        return 0;
    }

    return len;
}



uint32 EEPROM_readbyte (uint32 addr, uint8 *buffer, uint16 len)
{
    uint8  result;
    
    #if (DEBUG_SUPPORT == 10)
    //APP_printf("\n\r    EEPROM_readbyte... ");
    #endif

    result = MX25L1602_RD(addr, buffer, len);
    if (result == FALSE)
    {
        #if (DEBUG_SUPPORT == 1)
        //APP_printf("\n\r    MX25L1602_RD: 0x%x fail ", addr);
        #endif

        return 0;
    }
        
    return len;
}


#endif



