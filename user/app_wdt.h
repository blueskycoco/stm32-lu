/*****************************************************************************************
版权所有:        ---------------
版本号:            1.0.0
生成日期:        2010.05.11
文件名:            app_wdt.h
作者:            影舞者
功能说明:        应用层配置文件
其它说明:        Atmel AT91SAM9G45-EK Evaluation Board
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef APP_WDT_PRESENT
#define APP_WDT_PRESENT

#ifdef  APP_WDT_GLOBALS    
    #define APP_WDT_EXT    
#else
    #define APP_WDT_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   宏定义
其它说明:   无
*****************************************************************************************/
#define WDT_TIMEOUT                (6000000 * 6)                        // WDT复位,在2秒




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.10
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_WDT_EXT    void     WDTC_Clear(void);

APP_WDT_EXT    void     WDTC_Message(char *message);

APP_WDT_EXT    void     ConfigureWDTC(void);




#endif


