/*****************************************************************************************
版权所有:        ----------------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_power.c
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

#define  APP_POWER_GLOBALS
#include "app_types.h"
#include "app_power.h"



#if (POWER_SUPPORT == 1)



/*****************************************************************************************
函数名称:    void  POWER_Manager (uint8 type, uint8 status) 
版本号:        1.0.1
生成日期:    2008.07.30
作者:        影舞者
功能说明:    设备电源管理
输入参数:    uint8 type:   设备
            uint8 on_off: 电源状态
输出参数:    无
其它说明:    无
*****************************************************************************************/
void  POWER_Manager (uint8 type, uint8 status) 
{
    switch(type)
    {
        case PM_POWER:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_POWER_PORT, PW_PIN_POWER, (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_POWER_PORT, PW_PIN_POWER, (BitAction)0);
                break;

        case PM_MOTOR:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN, (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN, (BitAction)0);
                break;

        #if (PWM_SUPPORT == 0)
        case PM_BEEP:
                if (status == DEF_ON)
                    GPIO_WriteBit(PW_PIN_BEEP_PORT,  PW_PIN_BEEP,  (BitAction)1);
                else
                    GPIO_WriteBit(PW_PIN_BEEP_PORT,  PW_PIN_BEEP,  (BitAction)0);
                break;
        #endif
    }
}




/*****************************************************************************************
函数名称:    uint8  POWER_StatusIO (uint8 type) 
版本号:        1.0.1
生成日期:    2008.07.30
作者:        影舞者
功能说明:    设备电源管理
输入参数:    uint8 type:   设备
            uint8 on_off: 电源状态
输出参数:    无
其它说明:    无
*****************************************************************************************/
uint8  POWER_StatusIO (uint8 type) 
{
    switch(type)
    {
        case PM_POWER:
            return  GPIO_ReadOutputDataBit(PW_PIN_POWER_PORT, PW_PIN_POWER);
            
        case PM_MOTOR:
            return  GPIO_ReadOutputDataBit(PW_PIN_VH_EN_PORT, PW_PIN_VH_EN);
            
        case PM_BEEP:
            return  GPIO_ReadOutputDataBit(PW_PIN_BEEP_PORT, PW_PIN_BEEP);
    }

    return 0;
}




/*****************************************************************************************
函数名称:    void ConfigurePOWER(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    初始化电源控制引脚 
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void ConfigurePOWER(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r ConfigurePOWER... ");
#endif
    
    // POWER电源开关
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(PW_PIN_POWER_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_POWER;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_POWER_PORT , &GPIO_InitStructure);

    // VH_EN电源控制
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(PW_PIN_VH_EN_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_VH_EN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_VH_EN_PORT , &GPIO_InitStructure);

#if (PWM_SUPPORT == 0)
    // BEEP电源控制
    // GPIOE 外部时钟使能
    RCC_AHBPeriphClockCmd(PW_PIN_BEEP_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PW_PIN_BEEP;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PW_PIN_BEEP_PORT , &GPIO_InitStructure);
#endif

    // 打开基本的电源  
    POWER_Manager(PM_POWER,  DEF_OFF);                  // 关闭 系统 电源
    POWER_Manager(PM_MOTOR,  DEF_OFF);                  // 关闭 电机 电源  
    POWER_Manager(PM_BEEP,   DEF_OFF);                  // 关闭 声音 电源
}


#endif



