/*****************************************************************************************
版权所有:        ------------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            config.c
作者:            影舞者 
功能说明:        系统运行配置参数
其它说明:        无
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#define  CONFIG_GLOBALS    
#include "app_types.h"
#include "app_debug.h"
#include "app_spi.h"
#include "app_adc.h"

#include "MX25L1602Drv.h"

#include "main.h"
#include "config.h"


extern  uint16  ADC_60C_Value;


#if (FLASH_SUPPORT == 1)


uint16  APP_crc16(uint16 value, const uint8 *buffer, uint16 len)
{
    uint16  i;
    
    for (i = 0; i < len; i++)
        value = value + buffer[i];

    return value;
}




/*****************************************************************************************
函数名称:    void Read_AppInfoConfig(void)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    读取参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Read_AppInfoConfig(void)
{
    #if (MX25L1602_SUPORT == 1)
        EEPROM_readbyte (AppOffsetAddr, (uint8 *)&AppInfo, APP_sizeof(AppInfo));
    #endif

    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r Read_AppInfo");
    #endif
}




/*****************************************************************************************
函数名称:    void Write_AppInfoConfig(void)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    保存参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Write_AppInfoConfig(void)
{
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r Write_AppInfo");
    #endif
    
    #if (MX25L1602_SUPORT == 1)
        EEPROM_writebyte(AppOffsetAddr, (uint8 *)&AppInfo, APP_sizeof(AppInfo));
    #endif
}




/*****************************************************************************************
函数名称:    void Read_MachineInfoConfig(void)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    读取参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Read_MachineInfoConfig(void)
{
    #if (MX25L1602_SUPORT == 1)
        EEPROM_readbyte (MachineOffsetAddr, (uint8 *)&MachineConfig, APP_sizeof(MachineConfig));
    #endif

    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r Read_MachineInfo");
    #endif
}




/*****************************************************************************************
函数名称:    void Write_MachineInfoConfig(void)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    保存参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Write_MachineInfoConfig(void)
{
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r Write_MachineInfo");
    #endif

    #if (MX25L1602_SUPORT == 1)
        EEPROM_writebyte(MachineOffsetAddr, (uint8 *)&MachineConfig, APP_sizeof(MachineConfig));
    #endif
}




/*****************************************************************************************
函数名称:    void  Reset_AppInfoConfig(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    复位系统参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  Reset_AppInfoConfig(void)
{
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r    Reset_AppInfoConfig... ");
    #endif
    
    // 复位数据
    APP_memset((char *)&AppInfo, 0, APP_sizeof(AppInfo));

    // 机器名
    APP_strcpy(AppInfo.dev_name, PRODUCT_NAME);
    
    // LCD 亮度 0全亮, 1中等, 2暗亮
    AppInfo.LCD_Brightness = 0;

    // 数据 CRC16 纠正
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    
    #if (DEBUG_SUPPORT == 1)
        APP_printf("\n\r     Reset_App: 0x%X", AppInfo.DataCrc16);
    #endif
}




/*****************************************************************************************
函数名称:    void  Reset_MachineInfoConfig(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    产品参数, 无论程序怎么更新，这些参数始终不变化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  Reset_MachineInfoConfig(void)
{    
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r    Reset_MachineInfoConfig... ");
    #endif
    
    // 复位数据
    APP_memset((char *)&MachineConfig, 0, APP_sizeof(MachineConfig));
        
    // 产品系列号
    MachineConfig.MachineCODE = LOCAL_CODE;                       // 4位年 + 2位月 + 4位编号

    // 产品系列号
    MachineConfig.hardversion = HD_VERSION;                       // 硬件版本

    MachineConfig.LanguageType  = 0;

    MachineConfig.WarmTime = MOTOR_WARM_TICK;
    MachineConfig.ADC60Value = ADC_TM_60C;

    // 数据 CRC16 纠正
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    
    #if (DEBUG_SUPPORT == 1)
        APP_printf("\n\r     Reset_Machine: 0x%X", MachineConfig.DataCrc16);
    #endif
}




/*****************************************************************************************
函数名称:    void   InitConfig(void)
版本号:        1.0.0
生成日期:    2010.05.11
作者:        影舞者
功能说明:    配置系统参数
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void   InitConfig(void)
{
    uint16  crcCheckValue;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r InitConfig... ");
#endif

    // ----------------------------------------------
    // ----------------------------------------------
    // 配置信息
    APP_memset((char *)&AppInfo, 0, APP_sizeof(AppInfo));

    Read_AppInfoConfig();

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r");
    APP_printf("\n\r    AppInfo: ");
    APP_printf("\n\r    CRC: 0x%X-0x%X", AppInfo.DataCrc16, APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2));
#endif

    crcCheckValue = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    if ((AppInfo.DataCrc16 != crcCheckValue)
     || (AppInfo.DataCrc16 == 0)
     || (APP_strcmp(AppInfo.dev_name, PRODUCT_NAME) != 0))
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r    复位 AppInfo 参数...CRC: 0x%X(0x%X)(%s,%s) ", AppInfo.DataCrc16, crcCheckValue, AppInfo.dev_name, PRODUCT_NAME);
        #endif
    
        Reset_AppInfoConfig();            // 复位参数
        Write_AppInfoConfig();            // 写回保存
    }


    // ----------------------------------------------
    // ----------------------------------------------
    // 产品信息
    APP_memset((char *)&MachineConfig, 0, APP_sizeof(MachineConfig));

    Read_MachineInfoConfig();

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r");
    APP_printf("\n\r    MachineConfig: ");
    APP_printf("\n\r    CRC: 0x%X-0x%X", MachineConfig.DataCrc16, APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2));
#endif

    crcCheckValue = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    if ((MachineConfig.DataCrc16 != crcCheckValue)
     || (MachineConfig.DataCrc16 == 0)
     || (MachineConfig.MachineCODE == 0))
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r    复位 MachineConfig 参数...CRC: 0x%X(0x%X) ", MachineConfig.DataCrc16, crcCheckValue);
        #endif
                
        Reset_MachineInfoConfig();        // 复位参数
        Write_MachineInfoConfig();        // 写回保存
    }

    if ((MachineConfig.WarmTime > (MOTOR_WARM_TICK + 20))
       || (MachineConfig.WarmTime < (MOTOR_WARM_TICK - 20)))
        Set_WarmTime(MOTOR_WARM_TICK);

    if ((MachineConfig.ADC60Value > (ADC_TM_60C + 200))    
       || (MachineConfig.ADC60Value < (ADC_TM_60C - 200)))
        Set_ADC60Value(ADC_TM_60C);

    ADC_60C_Value = Get_ADC60Value();        // 60度标准值  3000文本

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r");
#endif
}




/*****************************************************************************************
函数名称:    void Save_BlueParams(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    设置屏保时间
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Save_BlueParams(void)
{
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    Write_AppInfoConfig();
}




/*****************************************************************************************
函数名称:    uint32 Get_MachineCODE(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    获取屏保时间
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint32 Get_MachineCODE(void)
{
    return MachineConfig.MachineCODE;
}




/*****************************************************************************************
函数名称:    void Set_MachineCODE(uint32 value)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    设置屏保时间
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Set_MachineCODE(uint32 value)
{
    MachineConfig.MachineCODE = value;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}




/*****************************************************************************************
函数名称:    uint16 Get_HardVersion(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    获取屏保时间
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint16 Get_HardVersion(void)
{
    return MachineConfig.hardversion;
}




/*****************************************************************************************
函数名称:    void Set_HardVersion(uint16 value)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    设置屏保时间
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Set_HardVersion(uint16 value)
{
    MachineConfig.hardversion = value;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}



uint8 Get_WarmTime(void)
{
    return MachineConfig.WarmTime;
}



void  Set_WarmTime(uint8 value)
{
    MachineConfig.WarmTime = value;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}



uint16 Get_ADC60Value(void)
{
    return MachineConfig.ADC60Value;
}



void  Set_ADC60Value(uint16 value)
{
    MachineConfig.ADC60Value = value;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}



/*****************************************************************************************
函数名称:    uint8 Get_LanguageType(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    获取触摸屏方式
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8 Get_LanguageType(void)
{
    return MachineConfig.LanguageType;
}




/*****************************************************************************************
函数名称:    void Set_LanguageType(uint8 value)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    设置触摸屏方式
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void Set_LanguageType(uint8 language)
{
    MachineConfig.LanguageType = language;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}




/*****************************************************************************************
函数名称:    uint8  Get_LCD_Brightness(void)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    脉率报警低限
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8  Get_LCD_Brightness(void)
{
    return AppInfo.LCD_Brightness;
}




/*****************************************************************************************
函数名称:    void  Set_LCD_Brightness(uint8 value)
版本号:        1.0.0
生成日期:    2009.10.20
作者:        影舞者
功能说明:    脉率报警低限
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  Set_LCD_Brightness(uint8 value)
{
    AppInfo.LCD_Brightness = value;
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    Write_AppInfoConfig();
}



#endif


