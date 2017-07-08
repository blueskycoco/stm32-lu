/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_sspi.h
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

#ifndef APP_SPI_PRESENT
#define APP_SPI_PRESENT

#ifdef  APP_SPI_GLOBALS
    #define APP_SPI_EXT
#else
    #define APP_SPI_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_SPI_EXT  void    ConfigureSPI(void);

APP_SPI_EXT  uint32  EEPROM_writebyte(uint32 addr, uint8 *buffer, uint16 len);
APP_SPI_EXT  uint32  EEPROM_readbyte (uint32 addr, uint8 *buffer, uint16 len);

APP_SPI_EXT  uint8   FONT_Erase(uint32 addr,  uint32 sizeLen);
APP_SPI_EXT  uint32  FONT_writebyte(uint32 addr, uint8 *buffer, uint16 len);
APP_SPI_EXT  uint32  FONT_readbyte (uint32 addr, uint8 *buffer, uint16 len);



#endif





