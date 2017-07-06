/*****************************************************************************************
版权所有:        ---------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            app_cmd.h
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

#ifndef APP_CMD_PRESENT
#define APP_CMD_PRESENT

#ifdef  APP_CMD_GLOBALS    
    #define APP_CMD_EXT        
#else
    #define APP_CMD_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2009.10.13
功能说明:   debug命令结构
其它说明:    无
*****************************************************************************************/
typedef  struct __BSP_ComnandInfo {
    char        * Cmd;
    char        * Info;
    void        (* Command)(char * paramer, uint16 size);
} BSP_ComnandInfo;




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2010.05.11
功能说明:   全局变量
其它说明:   无
*****************************************************************************************/
#define BSP_CMD_NUM                    8                        // 命令个数;

APP_CMD_EXT     const   BSP_ComnandInfo    BSP_DBG_CMD[BSP_CMD_NUM];




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2009.09.09
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_CMD_EXT  void      System(const char *command);

APP_CMD_EXT  uint8     TERMINAML_long_Opinion(uint8 type, char * str, uint8 number, uint64 * rparamers);
APP_CMD_EXT  uint8     TERMINAML_Paramer1_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers);
APP_CMD_EXT  uint8     TERMINAML_Paramer2_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2);
APP_CMD_EXT  uint8     TERMINAML_Paramer3_Opinion(uint8 type, char * str, uint8 number, uint32 * rparamers1, uint32 * rparamers2, uint32 * rparamers3);




#endif




