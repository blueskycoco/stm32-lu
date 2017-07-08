/*****************************************************************************************
版权所有:        ----------------
版本号:          1.0.0
生成日期:        2009.09.09
文件名:          app_kbd.c
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

#define  APP_KBD_GLOBALS
#include "app_types.h"
#include "app_kbd.h"
#include "app_led.h"
#include "app_wdt.h"
#include "app_power.h"



#if (KEY_SUPPORT == 1)




/*****************************************************************************************
版权所有:    影舞者
版本号:        1.0.0
生成日期:    2009.09.08
功能说明:    变量
其它说明:    无
*****************************************************************************************/
uint8   KBD_ReloadCount = 0;                // 防止重复进入
uint8   KBD_CountValue  = 0;                // 当前按键值

uint8   KBD_LongPress_POWER = 0;
uint8   KBD_LongPress_POWER_Count = 0;      // 电源按键长按时关机

uint8   KBD_LongPress_FEED = 0;
uint8   KBD_LongPress_FEED_Count = 0;       // FEED按键长按时关机

uint8   KBD_PrinterTestFlag = false;
uint16  KBD_PrinterTestCount = 0;

extern  uint8    OpenBEEP_Flag;
extern  uint32   SysTimeTick;

extern  void     BEEP_Player(uint8 second);




/*****************************************************************************************
函数名称:    void  KBD_SetReloadCountValue(uint8 value)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    设置重进入的值
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  KBD_SetReloadCountValue(uint8 value)
{
    KBD_ReloadCount = value;
}




/*****************************************************************************************
函数名称:    uint8  KBD_GetPinLevelValue(uint16 value)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    获取按键值
输入参数:    按键类型
输出参数:    1按下0松开
其它说明:    无
*****************************************************************************************/
uint8  KBD_GetPinLevelValue(uint8 keyType)
{
    uint8  key_value = 0;

    switch (keyType)
    {
        case KEY_HAL_POWER:
            key_value = GPIO_ReadInputDataBit(KEY_POWER_PORT, KEY_POWER);
            if (key_value != 0)
                key_value = 1;
            break;

        case KEY_HAL_FEED:
            key_value = GPIO_ReadInputDataBit(KEY_FEED_PORT, KEY_FEED);
            if (key_value != 0)
                key_value = 1;
            break;

        default:
            key_value = 0;            // 无效返回1
            break;
    }

    return key_value;
}




/*****************************************************************************************
函数名称:    void  KBD_GetPinValue(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    监视按键状态
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  KBD_GetPinValue(void)
{
    uint32  key_value;
    uint32  wdt_t1 = 0, wdt_t2 = 0;

    // 清计数器
    KBD_PrinterTestFlag = false;
    KBD_PrinterTestCount = 0;

    // 必须设置为0
    KBD_CountValue = 0;
    
    // 最上面的电源按键
    key_value = KBD_GetPinLevelValue(KEY_HAL_POWER);
    if (key_value == 1)
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r KEY_POWER");
        #endif
            
        KBD_CountValue = KBD_CountValue | KEY_HAL_POWER;
        KBD_LongPress_POWER = TRUE;
    }
    else
    {
        KBD_LongPress_POWER = FALSE;
    }

    // 扫描硬件
    key_value = KBD_GetPinLevelValue(KEY_HAL_FEED);
    if (key_value == 1)
    {
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r KEY_FEED");
        #endif
        
        KBD_CountValue = KBD_CountValue | KEY_HAL_FEED;
        KBD_LongPress_FEED = TRUE;
    }
    else
    {
        KBD_LongPress_FEED = FALSE;
    }
    
    // 长按电源按键, 强行关机
    if (KBD_LongPress_POWER == TRUE)
    {
        if (KBD_LongPress_POWER_Count <= POWER_OffTime)
            KBD_LongPress_POWER_Count++;
        
        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r 强关 %d ", KBD_LongPress_POWER_Count);
        #endif

        // 锁按键下不允许关机
        if (KBD_LongPress_POWER_Count >= POWER_OffTime)             // 3 秒关机
        {
            #if (DEBUG_SUPPORT == 1)
                APP_printf("\n\r 断电");
            #endif

            // 控制电源状态
            #if (POWER_SUPPORT == 1)
                POWER_Manager(PM_POWER,  DEF_OFF);        // 关系统电源
                POWER_Manager(PM_MOTOR,  DEF_OFF);        // 关电机电源

                // 灭状态
                #if (LED_SUPPORT == 1)
                    LED_Switch(RED_LED,    DEF_OFF);
                    LED_Switch(BLUE_LED,   DEF_OFF);
                #endif
            #endif

            while (1)
            {
                if (0)  break;

                #if (DEBUG_SUPPORT == 1)
                    DBG_printf("&");
                #endif
            }
        }
    }
    else
    {
        KBD_LongPress_POWER_Count = 0;
    }

    // 长按FEED3秒后进纸
    if (KBD_LongPress_FEED == TRUE)
    {
        if (KBD_LongPress_FEED_Count <= FEED_Time)
            KBD_LongPress_FEED_Count++;

        #if (DEBUG_SUPPORT == 1)
            APP_printf("\n\r 进纸 %d ", KBD_LongPress_FEED_Count);
        #endif
    }
    else
    {
        KBD_LongPress_FEED_Count = 0;
    }

    // 无键按下
    if (KBD_CountValue == 0)                    
    {
        KBD_ReloadCount = 0;
        return;
    }

    // 防止一直重入
    if (KBD_ReloadCount == 1)
        return;

    // 防止一直重入
    KBD_ReloadCount = 1;
}




/*****************************************************************************************
函数名称:    void  KBD_Feed(void)
版本号:        1.0.0
生成日期:    2009.09.14
作者:        影舞者
功能说明:    中断匀速进纸
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void KBD_Feed(void)
{

}




/*****************************************************************************************
函数名称:    void ConfigureKBD(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    键盘初始化
输入参数:    无
输出参数:    无
其它说明:    无  
*****************************************************************************************/
void ConfigureKBD(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigureKBD... ");
#endif

    // KEY1 power
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(KEY_POWER_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = KEY_POWER;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_POWER_PORT , &GPIO_InitStructure);

    // KEY2 feed
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(KEY_FEED_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = KEY_FEED;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_FEED_PORT , &GPIO_InitStructure);

    // 防止开机重入
    KBD_SetReloadCountValue(1);
}


#endif



