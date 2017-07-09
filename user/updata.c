


#include "app_types.h"
#include "app_cmd.h"
#include "app_wdt.h"
#include "app_led.h"
#include "app_spi.h"
#include "app_usart.h"
#include "app_debug.h"

#include "main.h"
#include "updata.h"
#include "MX25L1602Drv.h"


#define SysFontNUM                  9                   // 支持三种字体

const  FONT_Address  SysFontInfo[SysFontNUM] = {
    /*  name:       address:         size       sectornum*/
    {"license",     SEC_SIZE * 0,    1024,        1 },       // 1024    占用 1
    {APP_NAME,      SEC_SIZE * 1,    122880,     30 },       // 120K    占用 32
    {"asc16.bin",   SEC_SIZE * 31,   4096,        1 },       // 4096    占用 1
    {"asc24.bin",   SEC_SIZE * 32,   4608,        2 },       // 8192    占用 2
    {"asc32.bin",   SEC_SIZE * 34,   6144,        2 },       // 8192    占用 2
    {"asc48.bin",   SEC_SIZE * 36,   13680,       4 },       // 16384   占用 4
    {"hzk16.bin",   SEC_SIZE * 40,   267616,     66 },       // 270336  占用 66
    {"hzk24.bin",   SEC_SIZE * 106,  588816,    144 },       // 589824  占用 144
    {"hzk32.bin",   SEC_SIZE * 250,  1046784,   256 },       // 1048576 占用 256
};


extern  uint16  APP_crc16(uint16 value, const uint8 *buffer, uint16 len);


uint32  getFontAddress(uint8 fontType)
{
    switch (fontType)
    {
        case LICESE_SN:
            return SysFontInfo[0].address;
            
        case UPDATE_APP:
            return SysFontInfo[1].address;

        case FONT_ASC16:
            return SysFontInfo[2].address;

        case FONT_ASC24:
            return SysFontInfo[3].address;
            
        case FONT_ASC32:
            return SysFontInfo[4].address;
            
        case FONT_ASC48:
            return SysFontInfo[5].address;
            
        case FONT_HZK16:
            return SysFontInfo[6].address;
            
        case FONT_HZK24:
            return SysFontInfo[7].address;
            
        case FONT_HZK32:
            return SysFontInfo[8].address;
    }

    return 0;
}


uint32  getFontSize(uint8 fontType)
{
    switch (fontType)
    {
        case LICESE_SN:
            return SysFontInfo[0].size;
            
        case UPDATE_APP:
            return SysFontInfo[1].size;
            
        case FONT_ASC16:
            return SysFontInfo[2].size;
            
        case FONT_ASC24:
            return SysFontInfo[3].size;
            
        case FONT_ASC32:
            return SysFontInfo[4].size;
            
        case FONT_ASC48:
            return SysFontInfo[5].size;
            
        case FONT_HZK16:
            return SysFontInfo[6].size;
            
        case FONT_HZK24:
            return SysFontInfo[7].size;
            
        case FONT_HZK32:
            return SysFontInfo[8].size;
    }

    return 0;
}


uint32  getNameAddress(char * filename)
{
    uint8  i;
    
    for (i = 0; i < SysFontNUM; i++)
    {
        if (APP_strcmp(SysFontInfo[i].name, filename) == 0)
        {
            return SysFontInfo[i].address;
        }
    }
    
    return 0;
}


uint32  getNameSize(char * filename)
{
    uint8  i;
    
    for (i = 0; i < SysFontNUM; i++)
    {
        if (APP_strcmp(SysFontInfo[i].name, filename) == 0)
        {
            return SysFontInfo[i].size;
        }
    }
    
    return 0;
}


#if (UPDATA_SUPPORT == 1)


/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   下载文件使用
其它说明:   无
*****************************************************************************************/
extern  uint8   HZPrintBuff[HZPrintSIZE]; 

uint8   * flash_buffer = HZPrintBuff;
uint32  flash_buff_count = 0;
uint32  flash_pack_len   = 0;
uint32  flash_file_addr  = 0;
uint32  flash_file_size  = 0;
uint32  flash_file_frame = 0;
uint32  flash_cur_frame  = 0;

uint8   data_comeform_com = 0;

uint8   flash_down_Flag  = FALSE;
uint8   flash_request_flag = FALSE;
uint16  flash_down_timer = 0;


// 0xA5 0xA5 0xA5 0xA5 0xA5 包长度(2byte), 包类型, (帧数(2byte) + CRC16)
void RequestFrameUPDATA(uint16 frame)
{
    uint8  buff[12];
    uint16  crcValue;

    buff[0] = 0xA5;
    buff[1] = 0xA5;
    buff[2] = 0xA5;
    buff[3] = 0xA5;
    buff[4] = 0xA5;
    
    buff[5] = 12;    
    buff[6] = 0;

    buff[7] = 0x15;         // 包类型, 下载文件类型
    
    buff[8] = frame & 0xFF;    
    buff[9] = (frame >> 8) & 0xFF;

    crcValue = APP_crc16(0, buff, 10);

    buff[10] = crcValue & 0xFF;    
    buff[11] = (crcValue >> 8) & 0xFF;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r RequestFrame:%d(%d): ", frame, data_comeform_com);
  //  DebugMessage(buff, 12);
#endif

#if (USART1_SUPPORT == 1)
    if (data_comeform_com == COM1)              // 数据来源串口
        USART1_SendBuffer(buff,  12);
#endif

#if (USART2_SUPPORT == 1)
    if (data_comeform_com == COM2)              // 数据来源串口
        USART2_SendBuffer(buff,  12);
#endif
}


void RequestFrameTIMER(void)
{    
    if (flash_down_Flag == TRUE)
    {
        flash_down_timer++;
        if(flash_down_timer >= 8000)
        {
            #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r pack over time(%d<%d)", flash_buff_count, flash_pack_len);
            #endif

            // 数据来源串口
            data_comeform_com = 0;
            
            flash_down_Flag  = FALSE;
            flash_down_timer = 0;
            
            flash_request_flag = FALSE;

            flash_buff_count = 0;
            flash_pack_len   = 0;
            flash_file_addr  = 0;
            flash_file_frame = 0;
            flash_cur_frame  = 0;
        }
    }
}




/*****************************************************************************************
函数名称:    void  Updata_Unpack(uint8 value, uint8 comType)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    网络下载文件包处理
输入参数:    无
输出参数:    无
其它说明:    PC机主动发起
// 0xA5 0xA5 0xA5 0xA5 0xA5 包长度(2byte), 包类型, (帧数(2byte)+文件名   + CRC16)
// 0xA5 0xA5 0xA5 0xA5 0xA5 包长度(2byte), 包类型, (帧数(2byte)+字体数据 + CRC16)
*****************************************************************************************/
void  Updata_Unpack(uint8 value, uint8 comType)
{
    uint8   filename[32];
    uint32  addr_offset;
    uint16  crcValue, crcPack, frameValue;

    addr_offset = addr_offset;

    if (flash_buff_count <= 4)
    {
        if (value == 0xA5)
        {
            // 清定时器
            flash_down_Flag  = TRUE;
            flash_down_timer = 0;
            
            #if (DEBUG_SUPPORT == 10)
            APP_printf("=");
            #endif

            // 数据区
            flash_buffer[flash_buff_count] = value;
            flash_buff_count++;
        }
        else
        {
            flash_buff_count = 0;
        }
        return;
    }
    else if (flash_buff_count == 5)
    {
        // 清定时器
        flash_down_Flag  = TRUE;
        flash_down_timer = 0;
            
        #if (DEBUG_SUPPORT == 10)
        APP_printf("&");
        #endif

        // 数据区
        flash_buffer[flash_buff_count] = value;
        flash_buff_count++;

        // 包长低位
        flash_pack_len = value;
        return;
    }
    else if (flash_buff_count == 6)
    {
        // 清定时器
        flash_down_Flag  = TRUE;
        flash_down_timer = 0;
            
        #if (DEBUG_SUPPORT == 10)
        APP_printf("*");
        #endif

        // 数据区
        flash_buffer[flash_buff_count] = value;
        flash_buff_count++;

        // 包长度
        flash_pack_len = flash_pack_len + (value << 8);
        
        #if (DEBUG_SUPPORT == 10)
        APP_printf("\n\r flash_pack_len:%d \n\r", flash_pack_len);
        #endif
            
        if (flash_pack_len > (PKG_REQUEST_SIZE+12))
        {
            // 包长度出错
            #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r pack len error \n\r");
            #endif

            // 清定时器
            flash_down_Flag  = FALSE;
            flash_down_timer = 0;
            
            #if (DEBUG_SUPPORT == 1)
            APP_printf("+");
            #endif

            flash_buff_count = 0;
            flash_pack_len   = 0;
            flash_file_addr  = 0;
            flash_file_frame = 0;
            flash_cur_frame  = 0;
        }
        return;
    }
    else
    {
        // 清定时器
        flash_down_Flag  = TRUE;
        flash_down_timer = 0;
            
        #if (DEBUG_SUPPORT == 10)
        APP_printf("|");
        #endif

        // 数据区
        flash_buffer[flash_buff_count] = value;
        flash_buff_count++;
        if (flash_buff_count < flash_pack_len)
        {
            return;
        }

        // 收到完整的一包数据
        if (flash_buff_count >= flash_pack_len)
        {
            // 数据来源串口
            data_comeform_com = comType;

            if (flash_buffer[7] == 0x01)
            {
                // 上位机请求CPU ID表

                #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r CPUID pack(%d)", flash_buff_count);
                #endif
            }
            else if (flash_buffer[7] == 0x02)
            {
                // 上位机发送License表

                #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r LICENSE pack(%d)", flash_buff_count);
                #endif
            }
            else if (flash_buff_count == (PKG_REQUEST_SIZE+12))
            {
                #if (DEBUG_SUPPORT == 10)
                APP_printf("\n\r data pack(%d)", flash_buff_count);
                #endif
                    
                crcValue = APP_crc16(0, flash_buffer, flash_pack_len - 2);
                crcPack = flash_buffer[flash_pack_len - 2] + (flash_buffer[flash_pack_len - 1] << 8);

                #if (DEBUG_SUPPORT == 10)
                APP_printf("\n\r crcValue:%x(%x) \n\r", crcValue, crcPack);
                #endif

                if (crcValue == crcPack)
                {
                    frameValue = flash_buffer[8] + (flash_buffer[9] << 8);

                    #if (DEBUG_SUPPORT == 10)
                    APP_printf("\n\r frameValue:%d, flash_cur_frame:%d", frameValue, flash_cur_frame);
                    #endif

                    // 是不是有效的处理数据
                    if ((flash_request_flag == TRUE)
                     && (frameValue == (flash_cur_frame - 1)))
                    {
                        // 固化数据
                        addr_offset = frameValue * PKG_REQUEST_SIZE;
                        
                        #if (SPI_SUPPORT == 1)
                        FONT_writebyte(flash_file_addr + addr_offset, &flash_buffer[10], PKG_REQUEST_SIZE);
                        #endif

                        #if (DEBUG_SUPPORT == 10)
                            APP_printf("\n\r =%d,%d,%d,%d \n\r", frameValue, addr_offset, flash_file_addr, flash_cur_frame);
                        #endif

                        #if (DEBUG_SUPPORT == 10)
                            APP_printf("=%d", flash_cur_frame);
                        #endif

                        // 请求数据包
                        RequestFrameUPDATA(flash_cur_frame);
                        flash_cur_frame++;

                        // 下载结束
                        if ((flash_cur_frame - 1) >= flash_file_frame)
                        {
                            #if (DEBUG_SUPPORT == 1)
                                APP_printf("\n\r down over \n\r");
                            #endif

                            // 清定时器
                            flash_down_Flag  = FALSE;
                            flash_down_timer = 0;
                            
                            flash_request_flag = FALSE;

                            flash_buff_count = 0;
                            flash_pack_len   = 0;
                            flash_file_addr  = 0;
                            flash_file_frame = 0;
                            flash_cur_frame  = 0;
                            return;
                        }
                    }
                }
            }
            else
            {
                // A5 A5 A5 A5 A5 A5 15 00 01 00 61 73 63 31 32 2E 62 69 6E F1 DF
                #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r register pack \n\r");
                #endif

                crcValue = APP_crc16(0, flash_buffer, flash_pack_len - 2);
                crcPack = flash_buffer[flash_pack_len - 2] + (flash_buffer[flash_pack_len - 1] << 8);

                #if (DEBUG_SUPPORT == 10)
                APP_printf("\n\r crcValue:%x(%x) \n\r", crcValue, crcPack);
                #endif

                flash_file_frame = flash_buffer[8] + (flash_buffer[9] << 8);

                #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r flash_file_frame:%d \n\r", flash_file_frame);
                #endif

                // 提取文件名
                APP_memset(filename, 0, APP_sizeof(filename));
                APP_memcpy(filename, &flash_buffer[10], flash_pack_len - 8 - 2 - 2);

                #if (DEBUG_SUPPORT == 10)
                APP_printf("\n\r filename:%s== ", filename);
                APP_printf("\n\r getNameAddress: 0x%x ", getNameAddress((char *)filename));
                APP_printf("\n\r getNameSize: %d ", getNameSize((char *)filename));
                #endif

                flash_file_addr = getNameAddress((char *)filename);
                flash_file_size = getNameSize((char *)filename);
                if ((crcValue == crcPack)
                 && (flash_file_addr != 0) 
                 && (flash_file_size != 0))
                {
                    #if (DEBUG_SUPPORT == 1)
                    APP_printf("\n\r flash_file_addr 1 :%d(%d) \n\r", flash_file_addr, flash_file_size);
                    #endif
            
                    // 擦除字库
                    #if (SPI_SUPPORT == 1)
                    FONT_Erase(flash_file_addr, flash_file_size);
                    #endif
                    
                    #if (DEBUG_SUPPORT == 10)
                    APP_printf("\n\r flash_file_addr 2 :%d(%d) \n\r", flash_file_addr, flash_file_size);
                    #endif
            
                    // 第一帧为0
                    flash_cur_frame = 0;
                    flash_request_flag = TRUE;

                    #if (DEBUG_SUPPORT == 10)
                    APP_printf("--%d", flash_cur_frame);
                    #endif
    
                    // 请求数据包
                    RequestFrameUPDATA(flash_cur_frame);
                    flash_cur_frame++;
                }
            }

            #if (DEBUG_SUPPORT == 10)
            APP_printf("\n\r pack:%d(%d) \n\r", flash_pack_len, flash_buff_count);
            #endif
                
            // 清包处理
            flash_buff_count = 0;
            flash_pack_len   = 0;
        }
    }
}




/*****************************************************************************************
函数名称:    void ConfigureUPDATA(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    Timer 配置
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void ConfigureUPDATA(void)
{
#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureUPDATA... ");
#endif

    // 清定时器
    flash_down_Flag  = FALSE;
    flash_down_timer = 0;

    flash_buff_count = 0;
    flash_pack_len   = 0;
    flash_file_addr  = 0;
    flash_file_frame = 0;
    flash_cur_frame  = 0;
}




#endif




