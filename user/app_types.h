/*****************************************************************************************
版权所有:        ---------------
版本号:          1.0.0
生成日期:        2010.05.11
文件名:          app_compile.h
作者:            影舞者
功能说明:        变量类型配置文件
其它说明:        Evaluation Board
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef APP_COMPILE_PRESENT
#define APP_COMPILE_PRESENT




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.08
功能说明:   配置开关
其它说明:   无
*****************************************************************************************/
#define WDT_DELAY                       (200)                       // WDT 时间间隔

#define HD_VERSION                      (100)                       // 硬件版本 220 == H2.20
#define SF_VERSION                      (9774)                      // 软件版本 SVNxxxx
#define DT_DEVLOPER                     "2017-02-21"                // "DOTT: 2014 -11 -12"




/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define TICK_FREQ_MUL                   (20)                        // 预加热倍频
#define TICKRATE_HZ                     (2000)                      /* 2000 ticks per second */
#define ADCRATE_HZ                      (1000000)                   /* 1000000 HZ */




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.08
功能说明:   型号确认
其它说明:   无
*****************************************************************************************/
#ifdef  IFLASH_STM32F0_P1
    #include "app_p1.h"
    #define PRODUCT_NAME                  "MPT-II"
    #define APP_NAME                      "iflash_STM32F0_P1.bin"

    #define BLUE_SPP_NAME                 "MPT-II(SPP)"
    #define BLUE_BLE_NAME                 "MPT-II(BLE)"
#endif




/*****************************************************************************************
版权所有:   影舞者
版本号:        1.0.0
生成日期:    2009.09.08
功能说明:   配置开关
其它说明:   无
*****************************************************************************************/
#define LED_SUPPORT                         1                           // 是否加入LED指示灯
#define KEY_SUPPORT                         1                           // 是否加入KEY支持
#define WDT_SUPPORT                         1                           // 是否加入WDT支持
#define ADC_SUPPORT                         1                           // 是否加入ADC支持
#define IAP_SUPPORT                         1                           // 是否加入IAP支持
#define SPI_SUPPORT                         1                           // 是否加入SPI支持
#define MX25L1602_SUPORT                    0                           // 是否加入MX25L1602支持
#define PWM_SUPPORT                         0                           // 是否加入PWM支持
#define FLASH_SUPPORT                       1                           // 是否加入FLASH功能
#define POWER_SUPPORT                       1                           // 是否加入POWER功能
#define MOTOR_SUPPORT                       1                           // 是否加入MOTOR功能




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2010.05.11
功能说明:   编译器变量类型
其它说明:   无
*****************************************************************************************/
#define    uint8        unsigned   char                                 // 无符号 8位整型变量
#define    int8         signed     char                                 // 有符号 8位整型变量
#define    uint16       unsigned   short                                // 无符号16位整型变量
#define    int16        signed     short                                // 有符号16位整型变量 
#define    uint32       unsigned   int                                  // 无符号32位整型变量
#define    int32        signed     int                                  // 有符号32位整型变量
#define    uint64       unsigned   long long                            // 无符号64位整型变量
#define    int64        signed     long long                            // 有符号64位整型变量
#define    float32      float                                           // 单精度浮点数(32位长度)
#define    float64      double                                          // 双精度浮点数(64位长度)

#define    FALSE        0
#define    TRUE         1

#define    false        0
#define    true         1

#define    DEF_OFF      0
#define    DEF_ON       1




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.09.08
功能说明:   配置开关
其它说明:   无
*****************************************************************************************/
#define LOCAL_CODE                     (2014019999)                     // 4位年 + 2位月 + 4位编号
#define LOCAL_PASSWORD                 (2014019999)                     // 默认密码和序列号一样

#define PRINTER_XByte                   48                              // X轴字节数
#define PRINTER_XBit                    384                             // X轴点数据

#define UART1_BPS                       115200                          // 用户速度 
#define UART2_BPS                       115200                          // 蓝牙速度  




/*****************************************************************************************
版权所有:   影舞者
版本号:        1.0.0
生成日期:    2009.09.08
功能说明:   配置开关
其它说明:   无
*****************************************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"

#include "includes.h"




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.10.13
功能说明:   结构对齐
其它说明:   无
*****************************************************************************************/
#define __APP_PACKED(n)        __attribute__ ((packed, aligned(n)))            // 结构对齐 

extern  void  TICK_DisableIRQ(void);
extern  void  TICK_EnableIRQ(void);




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2009.10.04
功能说明:   系统函数
其它说明:   无
*****************************************************************************************/
#if (DEBUG_SUPPORT == 1)
    #define dprintf(fmt, args...)       printf(fmt, ##args)                // 信息打印
#endif
#if (DEBUG_SUPPORT == 0)
    #define dprintf(fmt, args...)
#endif

#define ENTER_CRITICAL()               // TICK_DisableIRQ()                  // 进入中断
#define EXIT_CRITICAL()                // TICK_EnableIRQ()                   // 退出中断

#define qprintf(fmt, args...)           dprintf(fmt, ##args)               // 打印
#define mprintf(fmt, args...)           dprintf(fmt, ##args)               // 打印
#define pprintf(fmt, args...)           dprintf(fmt, ##args)               // 打印
#define bprintf(fmt, args...)           dprintf(fmt, ##args)               // 打印
#define DBG_printf(fmt, args...)        dprintf(fmt, ##args)               // 打印
#define APP_printf(fmt, args...)        dprintf(fmt, ##args)               // 打印

#define APP_sprintf                     sprintf                            // 打印
#define APP_malloc(a)                   malloc(a)                          // 申请内存
#define APP_free(a)                     free(a)                            // 释放内存
#define APP_strlen(a)                   strlen(a)                          // 长度
#define APP_sizeof(a)                   sizeof(a)                          // 大小
#define APP_strcat(a, b)                strcat(a, b)                       // 连接
#define APP_strstr(a, b)                strstr(a, b)                       // 查找字条
#define APP_strchr(a, b)                strchr(a, b)                       // 查找字条
#define APP_strcmp(a, b)                strcmp(a, b)                       // 比较
#define APP_strncmp(a, b, n)            strncmp(a, b, n)                   // 比较
#define APP_strcpy(a, b)                strcpy(a, b)                       // 拷贝
#define APP_strncpy(a, b, n)            strncpy(a, b, n)                   // 拷贝
#define APP_abs(a)                      abs(a)                             // 绝对值
#define APP_fabs(a)                     fabs(a)                            // 绝对值
#define APP_atoi(a)                     atoi(a)                            // 字符串转整数
#define APP_atol(a)                     atol(a)                            // 字符串转整数
#define APP_atof(a)                     atof(a)                            // 字符串转整数
#define APP_memset(a, b, n)             memset(a, b, n)                    // 内存设置
#define APP_memcpy(a, b, n)             memcpy(a, b, n)                    // 内存拷贝
#define APP_memcmp(a, b, n)             memcmp(a, b, n)                    // 内存比较
#define APP_memmove(a, b, n)            memmove(a, b, n)                   // 内存移动




#endif


