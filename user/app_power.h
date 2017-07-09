/*****************************************************************************************
版权所有:        ---------------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_power.h
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

#ifndef APP_POWER_PRESENT
#define APP_POWER_PRESENT

#ifdef  APP_POWER_GLOBALS    
    #define APP_POWER_EXT
#else
    #define APP_POWER_EXT    extern
#endif 




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2005.1.1
功能说明:   电源管理
其它说明:   无
*****************************************************************************************/
#define PM_POWER                    42                          // 系统   电源
#define PM_MOTOR                    43                          // Print  电源
#define PM_BEEP                     44                          // beep   电源




/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define PW_PIN_POWER                GPIO_Pin_9                 // PW - P0.8
#define PW_PIN_POWER_PORT           GPIOB
#define PW_PIN_POWER_PORT_CLK       RCC_AHBPeriph_GPIOB  

#define PW_PIN_VH_EN                GPIO_Pin_4                 // PW - P0.9
#define PW_PIN_VH_EN_PORT           GPIOB
#define PW_PIN_VH_EN_PORT_CLK       RCC_AHBPeriph_GPIOB  

#define PW_PIN_BEEP                 GPIO_Pin_5                 // PW - P0.23
#define PW_PIN_BEEP_PORT            GPIOB
#define PW_PIN_BEEP_PORT_CLK        RCC_AHBPeriph_GPIOB  




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:    2009.09.09
功能说明:   接口函数
其它说明:   无
*****************************************************************************************/
APP_POWER_EXT    void    ConfigurePOWER(void);

APP_POWER_EXT    uint8   POWER_StatusIO (uint8 type);
APP_POWER_EXT    void    POWER_Manager(uint8 type, uint8 status);




#endif




