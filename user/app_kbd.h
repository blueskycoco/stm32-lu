/*****************************************************************************************
版权所有:        -----------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_kbd.h
作者:            影舞者
功能说明:        应用配置文件
其它说明:        Atmel AT91SAM3U4-EK Evaluation Board
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef APP_KBD_PRESENT
#define APP_KBD_PRESENT

#ifdef  APP_KBD_GLOBALS    
    #define APP_KBD_EXT
#else
    #define APP_KBD_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:        1.0.0
生成日期:    2009.09.11
功能说明:   按键的值
其它说明:   无
*****************************************************************************************/
#define KEY_HAL_POWER                 61                        // 电源
#define KEY_HAL_FEED                  62                        // 静音




/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define KEY_POWER                    GPIO_Pin_8                 // KEY1 - P0.7 
#define KEY_POWER_PORT               GPIOB
#define KEY_POWER_PORT_CLK           RCC_AHBPeriph_GPIOB  

#define KEY_FEED                     GPIO_Pin_15                // KEY2 - P0.14 
#define KEY_FEED_PORT                GPIOA
#define KEY_FEED_PORT_CLK            RCC_AHBPeriph_GPIOA  


#define FEED_Time                       (3)                     // 进纸时间
#define POWER_OffTime                   (6)                     // 关机时间
#define PrintTestPageTime               (4000)                  // 打印测试时间2秒




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2009.09.09
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_KBD_EXT  void    ConfigureKBD(void);

APP_KBD_EXT  void    KBD_Feed(void);
APP_KBD_EXT  void    KBD_GetPinValue(void);
APP_KBD_EXT  uint8   KBD_GetPinLevelValue(uint8 value);




#endif




