/*****************************************************************************************
版权所有:        ------------
版本号:            1.0.0
生成日期:        2009.10.20
文件名:            config.h
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

#ifndef CONFIG_PRESENT
#define CONFIG_PRESENT

#ifdef  CONFIG_GLOBALS                                                    
    #define CONFIG_EXT                                                        
#else
    #define CONFIG_EXT    extern                                            
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:        1.0.0
生成日期:    2009.09.08
功能说明:   偏移位置
其它说明:   无
*****************************************************************************************/
#define MachineOffsetAddr               (0)                         // 扇区0开始
#define AppOffsetAddr                   (SEC_SIZE)                  // 扇区1开始




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2010.05.11
功能说明:   数据结构
其它说明:   无
*****************************************************************************************/
typedef  struct  __machineconfiginfo {    
    uint32   MachineCODE;                    // 产品序列号
    uint16   hardversion;                    // 硬件版本
    uint8    LanguageType;                   // 语言类型

    uint8    WarmTime;
    uint16   ADC60Value;
    
    uint16   DataCrc16;                      // 确保参数的正确性
}__APP_PACKED(1)  MachineConfigInfo;




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2010.05.11
功能说明:   数据结构
其它说明:   无
*****************************************************************************************/
typedef  struct  __appconfiginfo {
    char    dev_name[10];                    // 设备名字
    
    uint8   LCD_Brightness;                  // LCD 亮度

    char    BT_PIN[5];
    uint8   BT_BR_BDA[6];
    uint8   BT_LE_BDA[6];
    uint8   BT_VERSION[22];

    uint16  DataCrc16;                       // 确保参数的正确性
}__APP_PACKED(1)  AppConfigInfo;




/*****************************************************************************************
版权所有:   影舞者
版本号:        1.0.0
生成日期:    2009.09.08
功能说明:   参数结构
其它说明:   无
*****************************************************************************************/
CONFIG_EXT   MachineConfigInfo       MachineConfig;
CONFIG_EXT   AppConfigInfo           AppInfo;




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.10.20
功能说明:   函数接口
其它说明:    无
*****************************************************************************************/
CONFIG_EXT    void    InitConfig(void);

CONFIG_EXT    void    Save_BlueParams(void);

CONFIG_EXT    void    Read_AppInfoConfig(void);
CONFIG_EXT    void    Write_AppInfoConfig(void);

CONFIG_EXT    void    Read_MachineInfoConfig(void);
CONFIG_EXT    void    Write_MachineInfoConfig(void);

CONFIG_EXT    uint8   Get_WarmTime(void);
CONFIG_EXT    void    Set_WarmTime(uint8 value);

CONFIG_EXT    uint16  Get_ADC60Value(void);
CONFIG_EXT    void    Set_ADC60Value(uint16 value);

CONFIG_EXT    uint8   Get_LanguageType(void);
CONFIG_EXT    void    Set_LanguageType(uint8 language);

CONFIG_EXT    uint16  Get_BaterryMaxADC(void);
CONFIG_EXT    void    Set_BaterryMaxADC(uint16 value);

CONFIG_EXT    uint16  Get_BaterryMinADC(void);
CONFIG_EXT    void    Set_BaterryMinADC(uint16 value);

CONFIG_EXT    uint32  Get_MachineCODE(void);
CONFIG_EXT    void    Set_MachineCODE(uint32 value);

CONFIG_EXT    uint16  Get_HardVersion(void);
CONFIG_EXT    void    Set_HardVersion(uint16 value);

CONFIG_EXT    uint8   Get_LCD_Brightness(void);
CONFIG_EXT    void    Set_LCD_Brightness(uint8 value);




#endif




