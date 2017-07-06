/*****************************************************************************************
��Ȩ����:        ------------------
�汾��:            1.0.0
��������:        2010.05.11
�ļ���:            config.c
����:            Ӱ���� 
����˵��:        ϵͳ�������ò���
����˵��:        ��
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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
��������:    void Read_AppInfoConfig(void)
�汾��:        1.0.0
��������:    2010.05.11
����:        Ӱ����
����˵��:    ��ȡ����
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void Write_AppInfoConfig(void)
�汾��:        1.0.0
��������:    2010.05.11
����:        Ӱ����
����˵��:    �������
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void Read_MachineInfoConfig(void)
�汾��:        1.0.0
��������:    2010.05.11
����:        Ӱ����
����˵��:    ��ȡ����
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void Write_MachineInfoConfig(void)
�汾��:        1.0.0
��������:    2010.05.11
����:        Ӱ����
����˵��:    �������
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    void  Reset_AppInfoConfig(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��λϵͳ����
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  Reset_AppInfoConfig(void)
{
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r    Reset_AppInfoConfig... ");
    #endif
    
    // ��λ����
    APP_memset((char *)&AppInfo, 0, APP_sizeof(AppInfo));

    // ������
    APP_strcpy(AppInfo.dev_name, PRODUCT_NAME);
    
    // LCD ���� 0ȫ��, 1�е�, 2����
    AppInfo.LCD_Brightness = 0;

    // ���� CRC16 ����
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    
    #if (DEBUG_SUPPORT == 1)
        APP_printf("\n\r     Reset_App: 0x%X", AppInfo.DataCrc16);
    #endif
}




/*****************************************************************************************
��������:    void  Reset_MachineInfoConfig(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��Ʒ����, ���۳�����ô���£���Щ����ʼ�ղ��仯
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  Reset_MachineInfoConfig(void)
{    
    #if (DEBUG_SUPPORT == 10)
        //APP_printf("\n\r    Reset_MachineInfoConfig... ");
    #endif
    
    // ��λ����
    APP_memset((char *)&MachineConfig, 0, APP_sizeof(MachineConfig));
        
    // ��Ʒϵ�к�
    MachineConfig.MachineCODE = LOCAL_CODE;                       // 4λ�� + 2λ�� + 4λ���

    // ��Ʒϵ�к�
    MachineConfig.hardversion = HD_VERSION;                       // Ӳ���汾

    MachineConfig.LanguageType  = 0;

    MachineConfig.WarmTime = MOTOR_WARM_TICK;
    MachineConfig.ADC60Value = ADC_TM_60C;

    // ���� CRC16 ����
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    
    #if (DEBUG_SUPPORT == 1)
        APP_printf("\n\r     Reset_Machine: 0x%X", MachineConfig.DataCrc16);
    #endif
}




/*****************************************************************************************
��������:    void   InitConfig(void)
�汾��:        1.0.0
��������:    2010.05.11
����:        Ӱ����
����˵��:    ����ϵͳ����
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void   InitConfig(void)
{
    uint16  crcCheckValue;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r InitConfig... ");
#endif

    // ----------------------------------------------
    // ----------------------------------------------
    // ������Ϣ
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
            APP_printf("\n\r    ��λ AppInfo ����...CRC: 0x%X(0x%X)(%s,%s) ", AppInfo.DataCrc16, crcCheckValue, AppInfo.dev_name, PRODUCT_NAME);
        #endif
    
        Reset_AppInfoConfig();            // ��λ����
        Write_AppInfoConfig();            // д�ر���
    }


    // ----------------------------------------------
    // ----------------------------------------------
    // ��Ʒ��Ϣ
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
            APP_printf("\n\r    ��λ MachineConfig ����...CRC: 0x%X(0x%X) ", MachineConfig.DataCrc16, crcCheckValue);
        #endif
                
        Reset_MachineInfoConfig();        // ��λ����
        Write_MachineInfoConfig();        // д�ر���
    }

    if ((MachineConfig.WarmTime > (MOTOR_WARM_TICK + 20))
       || (MachineConfig.WarmTime < (MOTOR_WARM_TICK - 20)))
        Set_WarmTime(MOTOR_WARM_TICK);

    if ((MachineConfig.ADC60Value > (ADC_TM_60C + 200))    
       || (MachineConfig.ADC60Value < (ADC_TM_60C - 200)))
        Set_ADC60Value(ADC_TM_60C);

    ADC_60C_Value = Get_ADC60Value();        // 60�ȱ�׼ֵ  3000�ı�

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r");
#endif
}




/*****************************************************************************************
��������:    void Save_BlueParams(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��������ʱ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void Save_BlueParams(void)
{
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    Write_AppInfoConfig();
}




/*****************************************************************************************
��������:    uint32 Get_MachineCODE(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��ȡ����ʱ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint32 Get_MachineCODE(void)
{
    return MachineConfig.MachineCODE;
}




/*****************************************************************************************
��������:    void Set_MachineCODE(uint32 value)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��������ʱ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void Set_MachineCODE(uint32 value)
{
    MachineConfig.MachineCODE = value;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}




/*****************************************************************************************
��������:    uint16 Get_HardVersion(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��ȡ����ʱ��
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint16 Get_HardVersion(void)
{
    return MachineConfig.hardversion;
}




/*****************************************************************************************
��������:    void Set_HardVersion(uint16 value)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��������ʱ��
�������:    ��
�������:    ��
����˵��:    ��
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
��������:    uint8 Get_LanguageType(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ��ȡ��������ʽ
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint8 Get_LanguageType(void)
{
    return MachineConfig.LanguageType;
}




/*****************************************************************************************
��������:    void Set_LanguageType(uint8 value)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ���ô�������ʽ
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void Set_LanguageType(uint8 language)
{
    MachineConfig.LanguageType = language;
    MachineConfig.DataCrc16 = APP_crc16(0, (const uint8 *)&MachineConfig, APP_sizeof(MachineConfig) - 2);
    Write_MachineInfoConfig();
}




/*****************************************************************************************
��������:    uint8  Get_LCD_Brightness(void)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ���ʱ�������
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
uint8  Get_LCD_Brightness(void)
{
    return AppInfo.LCD_Brightness;
}




/*****************************************************************************************
��������:    void  Set_LCD_Brightness(uint8 value)
�汾��:        1.0.0
��������:    2009.10.20
����:        Ӱ����
����˵��:    ���ʱ�������
�������:    ��
�������:    ��
����˵��:    ��
*****************************************************************************************/
void  Set_LCD_Brightness(uint8 value)
{
    AppInfo.LCD_Brightness = value;
    AppInfo.DataCrc16 = APP_crc16(0, (const uint8 *)&AppInfo, APP_sizeof(AppInfo) - 2);
    Write_AppInfoConfig();
}



#endif


