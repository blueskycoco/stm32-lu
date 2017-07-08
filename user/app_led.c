/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_led.c
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

#define  APP_LED_GLOBALS
#include "app_types.h"
#include "app_led.h"



#if (LED_SUPPORT == 1)




/*****************************************************************************************
版权所有:    影舞者
版本号:        1.0.0
生成日期:    2009.09.14
功能说明:    变量
其它说明:    无
*****************************************************************************************/
uint8    led_level_status;
uint8    flush_red_run_flag = false;

extern  uint8  BlueLinkOK;




/*****************************************************************************************
函数名称:    void LED_Switch(uint8 key, uint8 status)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    键盘LED控制
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void LED_Switch(uint8 key, uint8 status)
{
    switch (key)
    {
        case RED_LED:
            if (status == DEF_ON)
                GPIO_WriteBit(LED_RED_PORT, LED_RED_PIN, (BitAction)0);          // 点亮LED
            else
                GPIO_WriteBit(LED_RED_PORT, LED_RED_PIN, (BitAction)1);          // 熄灭LED
            break;

        case BLUE_LED:
            if (status == DEF_ON)
                GPIO_WriteBit(LED_BLUE_PORT, LED_BLUE_PIN, (BitAction)0);        // 点亮LED
            else
                GPIO_WriteBit(LED_BLUE_PORT, LED_BLUE_PIN, (BitAction)1);        // 熄灭LED
            break;

        default:
            break;
    };
}




/*****************************************************************************************
函数名称:    void  LED_FlushScanf(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    键盘LED控制, 50ms调用一次
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  LED_FlushScanf(void)
{
    // 状态翻转
    if (led_level_status == 0)
        led_level_status = 1;
    else
        led_level_status = 0;

    // 运行状态,蓝牙未连接蓝灯闪
    if (BlueLinkOK == false)
    {
        if (led_level_status == 0)
            LED_Switch(BLUE_LED, DEF_OFF);
        else
            LED_Switch(BLUE_LED, DEF_ON);
    }
    else
    {
        // 连接BT成功, 蓝灯长亮
        LED_Switch(BLUE_LED, DEF_ON);
    }

    // 低电压,红灯闪
    if (flush_red_run_flag == true)
    {
        if (led_level_status == 0)
            LED_Switch(RED_LED, DEF_OFF);
        else
            LED_Switch(RED_LED, DEF_ON);
    }
}




/*****************************************************************************************
函数名称:    void ConfigureLED(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    键盘LED初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void ConfigureLED(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureLED... ");
#endif

    // 红灯, 配置 LED灯端口 外部输出上拉模式
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(LED_RED_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED_RED_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_RED_PORT , &GPIO_InitStructure);


    // 蓝灯, 配置 LED灯端口 外部输出上拉模式
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(LED_BLUE_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED_BLUE_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_BLUE_PORT , &GPIO_InitStructure);

    //关闭LED
    LED_Switch(RED_LED,    DEF_OFF);
    LED_Switch(BLUE_LED,   DEF_OFF);
}


#endif



