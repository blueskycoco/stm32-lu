/*****************************************************************************************
��Ȩ����:        ----------------
�汾��:            1.0.0
��������:        2009.09.10
�ļ���:            app_sspi.h
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

#ifndef APP_SPI_PRESENT
#define APP_SPI_PRESENT

#ifdef  APP_SPI_GLOBALS
    #define APP_SPI_EXT
#else
    #define APP_SPI_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.10
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_SPI_EXT  void    ConfigureSPI(void);

APP_SPI_EXT  uint32  EEPROM_writebyte(uint32 addr, uint8 *buffer, uint16 len);
APP_SPI_EXT  uint32  EEPROM_readbyte (uint32 addr, uint8 *buffer, uint16 len);

APP_SPI_EXT  uint8   FONT_Erase(uint32 addr,  uint32 sizeLen);
APP_SPI_EXT  uint32  FONT_writebyte(uint32 addr, uint8 *buffer, uint16 len);
APP_SPI_EXT  uint32  FONT_readbyte (uint32 addr, uint8 *buffer, uint16 len);



#endif





