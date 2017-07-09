/*****************************************************************************************
版权所有:        ------------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            app_debug.h
作者:            影舞者
功能说明:        debug文件
其它说明:        无
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef APP_DEBUG_PRESENT
#define APP_DEBUG_PRESENT

#ifdef  APP_DEBUG_GLOBALS    
    #define APP_DEBUG_EXT        
#else
    #define APP_DEBUG_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2010.05.11
功能说明:   键盘缓冲区
其它说明:   无
*****************************************************************************************/
#define TERMINAML_KB_SIZE                    20                           // 键盘缓冲区大小

APP_DEBUG_EXT  char   TERMINAML_KB_BUF[TERMINAML_KB_SIZE];                // 键盘缓冲区
APP_DEBUG_EXT  uint8  TERMINAML_KB_DATA_NUMBER;                           // TERMINAML_KB_BUF 个数

APP_DEBUG_EXT  char   TERMINAML_KB_BAK[TERMINAML_KB_SIZE];
APP_DEBUG_EXT  char   TERMINAML_KB_BAK_Flag;
APP_DEBUG_EXT  uint16 TERMINAML_KB_BAK_NUM;





/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2010.05.11
功能说明:   接口函数
其它说明:   无
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




