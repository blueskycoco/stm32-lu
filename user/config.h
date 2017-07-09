/*****************************************************************************************
��Ȩ����:        ------------
�汾��:            1.0.0
��������:        2009.10.20
�ļ���:            config.h
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

#ifndef CONFIG_PRESENT
#define CONFIG_PRESENT

#ifdef  CONFIG_GLOBALS                                                    
    #define CONFIG_EXT                                                        
#else
    #define CONFIG_EXT    extern                                            
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:        1.0.0
��������:    2009.09.08
����˵��:   ƫ��λ��
����˵��:   ��
*****************************************************************************************/
#define MachineOffsetAddr               (0)                         // ����0��ʼ
#define AppOffsetAddr                   (SEC_SIZE)                  // ����1��ʼ




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2010.05.11
����˵��:   ���ݽṹ
����˵��:   ��
*****************************************************************************************/
typedef  struct  __machineconfiginfo {    
    uint32   MachineCODE;                    // ��Ʒ���к�
    uint16   hardversion;                    // Ӳ���汾
    uint8    LanguageType;                   // ��������

    uint8    WarmTime;
    uint16   ADC60Value;
    
    uint16   DataCrc16;                      // ȷ����������ȷ��
}__APP_PACKED(1)  MachineConfigInfo;




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2010.05.11
����˵��:   ���ݽṹ
����˵��:   ��
*****************************************************************************************/
typedef  struct  __appconfiginfo {
    char    dev_name[10];                    // �豸����
    
    uint8   LCD_Brightness;                  // LCD ����

    char    BT_PIN[5];
    uint8   BT_BR_BDA[6];
    uint8   BT_LE_BDA[6];
    uint8   BT_VERSION[22];

    uint16  DataCrc16;                       // ȷ����������ȷ��
}__APP_PACKED(1)  AppConfigInfo;




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:        1.0.0
��������:    2009.09.08
����˵��:   �����ṹ
����˵��:   ��
*****************************************************************************************/
CONFIG_EXT   MachineConfigInfo       MachineConfig;
CONFIG_EXT   AppConfigInfo           AppInfo;




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.10.20
����˵��:   �����ӿ�
����˵��:    ��
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




