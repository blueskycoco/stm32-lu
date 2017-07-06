/*****************************************************************************************
��Ȩ����:        ---------------
�汾��:            1.0.0
��������:        2010.05.11
�ļ���:            app_cmd.h
����:            Ӱ����
����˵��:        debug�ļ�
����˵��:        ��
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#ifndef APP_CMD_PRESENT
#define APP_CMD_PRESENT

#ifdef  APP_CMD_GLOBALS    
    #define APP_CMD_EXT        
#else
    #define APP_CMD_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2009.10.13
����˵��:   debug����ṹ
����˵��:    ��
*****************************************************************************************/
typedef  struct __BSP_ComnandInfo {
    char        * Cmd;
    char        * Info;
    void        (* Command)(char * paramer, uint16 size);
} BSP_ComnandInfo;




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2010.05.11
����˵��:   ȫ�ֱ���
����˵��:   ��
*****************************************************************************************/
#define BSP_CMD_NUM                    8                        // �������;

APP_CMD_EXT     const   BSP_ComnandInfo    BSP_DBG_CMD[BSP_CMD_NUM];




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2009.09.09
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_CMD_EXT  void      System(const char *command);

APP_CMD_EXT  uint8     TERMINAML_long_Opinion(uint8 type, char * str, uint8 number, uint64 * rparamers);
APP_CMD_EXT  uint8     TERMINAML_Paramer1_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers);
APP_CMD_EXT  uint8     TERMINAML_Paramer2_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2);
APP_CMD_EXT  uint8     TERMINAML_Paramer3_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2, uint32 * rparamers3);




#endif




