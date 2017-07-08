/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.10
文件名:            app_pwm.c
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

#define  APP_PWM_GLOBALS
#include "app_types.h"
#include "app_debug.h"
#include "app_pwm.h"
#include "app_wdt.h"


#if (PWM_SUPPORT == 1)


#define SCT_PWM_PIN_OUT         1		    /* COUT1 Generate square wave */
#define SCT_PWM_PIN_LED         0		    /* COUT0 [index 2] Controls LED */
#define SCT_PWM_OUT             1		    /* Index of OUT PWM */
#define SCT_PWM_LED             2		    /* Index of LED PWM */
#define SCT_PWM_RATE            10000		/* PWM frequency 10 KHz */




/*****************************************************************************************
函数名称:    void  PWMC_LevelCTRL(void)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    控制PWM
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  PWMC_LevelCTRL(uint8 type)
{
    return;
}




/*****************************************************************************************
函数名称:    void  ConfigurePWM(void)
版本号:        1.0.0
生成日期:    2009.09.10
作者:        影舞者
功能说明:    协议初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  ConfigurePWM(void)
{
#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigurePWM... ");
#endif
}


#endif



