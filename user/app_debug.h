/*****************************************************************************************
��Ȩ����:        ------------------
�汾��:            1.0.0
��������:        2010.05.11
�ļ���:            app_debug.h
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

#ifndef APP_DEBUG_PRESENT
#define APP_DEBUG_PRESENT

#ifdef  APP_DEBUG_GLOBALS    
    #define APP_DEBUG_EXT        
#else
    #define APP_DEBUG_EXT    extern
#endif 




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2010.05.11
����˵��:   ���̻�����
����˵��:   ��
*****************************************************************************************/
#define TERMINAML_KB_SIZE                    20                           // ���̻�������С

APP_DEBUG_EXT  char   TERMINAML_KB_BUF[TERMINAML_KB_SIZE];                // ���̻�����
APP_DEBUG_EXT  uint8  TERMINAML_KB_DATA_NUMBER;                           // TERMINAML_KB_BUF ����

APP_DEBUG_EXT  char   TERMINAML_KB_BAK[TERMINAML_KB_SIZE];
APP_DEBUG_EXT  char   TERMINAML_KB_BAK_Flag;
APP_DEBUG_EXT  uint16 TERMINAML_KB_BAK_NUM;





/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:    2010.05.11
����˵��:   �ӿں���
����˵��:   ��
*****************************************************************************************/
APP_DEBUG_EXT  void   TERMINAML_Initialize(void);
APP_DEBUG_EXT  void   TERMINAML_Systems(void);
APP_DEBUG_EXT  void   TERMINAML_Operation(void);
APP_DEBUG_EXT  void   TERMINAML_Interface(void);

APP_DEBUG_EXT  void   DebugLinBin(uint8 * message, uint32 len);
APP_DEBUG_EXT  void   DebugBin(uint8 * message, uint32 number, uint8 line, uint8 lineDot);
APP_DEBUG_EXT  void   DebugRoleBin(uint8 * message, uint32 row, uint8 line, uint8 lineDot);

APP_DEBUG_EXT  void   DebugMessage(uint8 * message, uint32 number);

APP_DEBUG_EXT  uint8  SYSTEM_for_string(uint8 * str, uint8 * number);
APP_DEBUG_EXT  uint8  SYSTEM_for_command(char * str, uint8 number);




#endif




