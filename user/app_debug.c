/*****************************************************************************************
版权所有:        ----------------
版本号:            1.0.0
生成日期:        2009.09.09
文件名:            app_debug.c
作者:            影舞者
功能说明:        应用配置文件
其它说明:        无
所属文件关系:    本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#define  APP_DEBUG_GLOBALS
#include "app_types.h"
#include "app_cmd.h"
#include "app_adc.h"
#include "app_wdt.h"
#include "app_debug.h"
#include "app_uart.h"
#include "app_usart.h"

#include "config.h"



extern  uint32    GuiChipID;
extern  uint32    SystemCoreClock;


#if (DEBUG_SUPPORT == 1)


void DebugMessage(uint8 * message, uint32 number)
{
    uint32 i;

    for (i = 0; i < number; i++)
    {
        if ((i % 16) == 0)
            DBG_printf("\r\n");
            
        DBG_printf(" 0x%02X", message[i]);
    }
    
    DBG_printf("\r\n");
}


void DebugLinBin(uint8 * message, uint32 len)
{
    uint8   k, value;
    uint32  i;

    for (i = 0; i < len; i++)
    {
        #if (WDT_SUPPORT == 1) 
        WDTC_Clear();
        #endif

        value = message[i];
        for (k = 8; k > 0; k--) 
        {                
            if ((value >> (k - 1)) & 0x01)
            {
                DBG_printf("1");
            }
            else
            {
                DBG_printf("-");
            }
        }
    }

    DBG_printf("\r\n");
}


void DebugBin(uint8 * message, uint32 row, uint8 line, uint8 lineDot)
{
    uint8   k, value, dotCount = 0;
    uint32  i, h;

    row = row / line;
    
    DBG_printf("\r\n row: %d, line:%d \n\r", row, line);

    for (i = 0; i < row; i++)
    {        
        #if (WDT_SUPPORT == 1) 
        WDTC_Clear();
        #endif

        dotCount = 0;

        DBG_printf("\r\n (%02d) ", i);

        for (h = 0; h < line; h++)
        {
            if (dotCount >= lineDot)
                break;

            value = message[i*line + h];
            for (k = 8; k > 0; k--) 
            {
                if (dotCount >= lineDot)
                    break;

                dotCount++;

                if ((value >> (k - 1)) & 0x01)
                {
                    DBG_printf("1");
                }
                else
                {
                    DBG_printf("-");
                }
            }
        }
    }
    
    DBG_printf("\r\n");
}


void DebugRoleBin(uint8 * message, uint32 row, uint8 line, uint8 lineDot)
{
    uint8   k, value, dotCount = 0;
    uint32  i, h, offset;

    row = row / line;
    offset = row;
    
    DBG_printf("\r\n row: %d, line:%d, offset:%d \n\r", row, line, offset);

    for (i = 0; i < row; i++)
    {        
        #if (WDT_SUPPORT == 1) 
        WDTC_Clear();
        #endif

        dotCount = 0;

        DBG_printf("\r\n (%02d) ", i);

        for (h = 0; h < line; h++)
        {
            if (dotCount >= lineDot)
                break;

            value = message[h * offset + i];
            for (k = 8; k > 0; k--) 
            {
                if (dotCount >= lineDot)
                    break;

                dotCount++;

                if ((value >> (k - 1)) & 0x01)
                {
                    DBG_printf("1");
                }
                else
                {
                    DBG_printf("-");
                }
            }
        }
    }
    
    DBG_printf("\r\n");
}




/*****************************************************************************************
函数名称:    void TERMINAML_Interface(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    终端界面
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void TERMINAML_Interface(void)
{
#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r --------------------------------------------------------------");
    APP_printf("\n\r    j&=        y+ y*         jv+        yy-v         v &      ");
    APP_printf("\n\r   wE!\"        j17$T        7MPC        NU$E-        Ej&v-   ");
    APP_printf("\n\r   O*K^       yHH:Ovm+      UMMK        BMNTO:      H1=\"7'   ");
    APP_printf("\n\r  jO&OH;      \"OH7\"E~       U0H1        BB71'      jCf'U:   ");
    APP_printf("\n\r  vM1H1        jB-j1       wHhHh*-     /$B)B-        BkJUK    ");
    APP_printf("\n\r  ^HI'OH      j\"\"^N1       \"OHOK~       H$H\"Da      jP'N ^");
    APP_printf("\n\r   \"'  O1         \"         jVHT        T ~ \"\"         \" ");
    APP_printf("\n\r --------------------------------------------------------------");
#endif    
}




/*****************************************************************************************
函数名称:    void TERMINAML_Systems(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    显示系统信息
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void TERMINAML_Systems(void)
{
    extern  uint32  SystemCoreClock;

    APP_printf("\n\r ---------------------- 系统信息及版本表 ----------------------");
    
#if (ADC_SUPPORT == 1)
    APP_printf("\n\r    ADC Battery: %d",       ADC_GetBatteryADC());
    APP_printf("\n\r    ADC MT_TM: %d",         ADC_GetTM_ADC());
    APP_printf("\n\r    ADC MT_PAPER_END: %d",  ADC_GetPaperADC());
#endif

#if (SPI_SUPPORT == 1)
    APP_printf("\n\r    GuiChipID: 0x%X",       GuiChipID);
#endif    

#if (FLASH_SUPPORT == 1)
    APP_printf("\n\r    Machine Code: %d",      Get_MachineCODE());
#endif

    APP_printf("\n\r    SystemCoreClock: %d",               SystemCoreClock);
    APP_printf("\n\r    APP_sizeof(BSP_DBG_CMD): %d" ,      APP_sizeof(BSP_DBG_CMD));
    APP_printf("\n\r    APP_sizeof(BSP_ComnandInfo): %d" ,  APP_sizeof(BSP_ComnandInfo));
    APP_printf("\n\r    Run on the STM32F070");
    APP_printf("\n\r    System Compiled: %s %s",  __DATE__, __TIME__);
    APP_printf("\n\r --------------------------------------------------------------");
}




/*****************************************************************************************
函数名称:    void TERMINAML_Initialize(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    超级终端显示初始化
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void TERMINAML_Initialize(void)
{        
    APP_memset(TERMINAML_KB_BUF, '\0', APP_sizeof(TERMINAML_KB_BUF));
    TERMINAML_KB_DATA_NUMBER = 0;                                            // 键盘里数据个数

    APP_memset(TERMINAML_KB_BAK, '\0', APP_sizeof(TERMINAML_KB_BAK));
    TERMINAML_KB_BAK_NUM = 0;
    TERMINAML_KB_BAK_Flag = 0;
}




/*****************************************************************************************
函数名称:    uint8 SYSTEM_for_command(char * str, uint8 * number)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    找出输入的命令的长度
输入参数:    uint8 * str: 串口接收的命令字符串
            uint8 * number: 字符串长度
输出参数:    字符长度
其它说明:    无
*****************************************************************************************/
uint8 SYSTEM_for_command(char * str, uint8 number)
{
    uint8  i = 0;
    
    for (i = 0; i < number; i++)
    {
        if ((str[i] == ' ') || (str[i] == '\0'))
            return i;
    }

    if (i == number)
        return i;
    
    return 0;
}




/*****************************************************************************************
函数名称:    uint8 SYSTEM_for_string(uint8 * str, uint8 * number)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    整理字符串
输入参数:    uint8 * str: 串口接收的命令字符串
            uint8 * number: 字符串长度
输出参数:    1: 错误
            0: 正确
其它说明:    把多余的空格去掉，整理成标准的命令字符串
*****************************************************************************************/
uint8 SYSTEM_for_string(uint8 * str, uint8 * number)
{
    uint8 switch_kg = 0, i, j;
    char  tempstring[100];

    APP_memset(tempstring, '\0', APP_sizeof(tempstring));

    for (i = 0, j = 0; i < *number; i++)
    {
        if ((str[i] == ' ') && (switch_kg == 0))
        {            
            tempstring[j] = str[i];
            j++;
            switch_kg = 1;

            continue;
        }

        if (str[i] == ' ')
            continue;
        
        tempstring[j] = str[i];
        j++;
        switch_kg = 0;
    }

    if (j == 0)                                                                // 空
        return 0;

    if ((j == 1) && (tempstring[0] == ' '))                                    // 只有一个空字符
        return 0;

    while (tempstring[0] == ' ')
    {
        for (i = 1; i < j; i++)
            str[i-1] = tempstring[i];

        str[i - 1] = '\0';
        j = j - 1;

        APP_strcpy(tempstring, (char *)str);
    }
        
    while (tempstring[j - 1] == ' ')
    {
        tempstring[j - 1] = '\0';
        j = j - 1;
    }
    
    APP_strcpy((char *)str, tempstring);
    *number = j;
    
    return 1;
}




/*****************************************************************************************
函数名称:    uint8 SYSTEM_read_key(uint8 * key)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    取得调试串口键入值
输入参数:    uint8  *key:  得到的键值
输出参数:    1: 有数据
            0: 无数据
其它说明:    无
*****************************************************************************************/
uint8 SYSTEM_read_key(uint8 * key)
{
    if (DEBUG_GetChar(key) == SUCCESS)
        return 1;

    return 0;                                                                // 无数据
}




/*****************************************************************************************
函数名称:    void TERMINAML_Operation(void)
版本号:        1.0.0
生成日期:    2009.09.08
作者:        影舞者
功能说明:    扫描电脑超级终端下来的命令
输入参数:    无
输出参数:    无
其它说明:    无
*****************************************************************************************/
void TERMINAML_Operation(void)
{
    uint8   i, len, key = 0;

    if (SYSTEM_read_key(&key) == 0)                        // 查询键盘缓冲区的数据
        return;

    if (key == 91)
        return;
    if (key == 65)
        return;

    if (key == 27)
    {
        if (TERMINAML_KB_BAK_Flag == 0)
        {
            // 取备份命令
            APP_strcpy(TERMINAML_KB_BUF, TERMINAML_KB_BAK);
            TERMINAML_KB_DATA_NUMBER = TERMINAML_KB_BAK_NUM;
                        
            // 显示出来
            DBG_printf("%s", TERMINAML_KB_BUF);    
            TERMINAML_KB_BAK_Flag = 1;
        }

        return;
    }
    
    if (key == 0x0d)                                        // 收到回车符，表示命令输入结束
    {
        // 对备份命令的清空
        TERMINAML_KB_BAK_Flag = 0;
        
        if (TERMINAML_KB_DATA_NUMBER == 0)                // 只收到回车符,再次显示本层菜单
        {
            APP_printf("\n\r->");
            return;
        }

        if (SYSTEM_for_string((uint8 *)TERMINAML_KB_BUF, &TERMINAML_KB_DATA_NUMBER) == 0)
        {
            DBG_printf("\n\r 错误命令格式\n\r->");
            TERMINAML_KB_DATA_NUMBER = 0;
            return;
        }

        // 备份命令
        APP_strcpy(TERMINAML_KB_BAK, TERMINAML_KB_BUF);
        TERMINAML_KB_BAK_NUM = TERMINAML_KB_DATA_NUMBER;

        if ((APP_strcmp(TERMINAML_KB_BUF,"?") == 0) || (APP_strcmp(TERMINAML_KB_BUF,"help") == 0))    // 打印出所有的命令
        {
            DBG_printf("\n\r");
            
            for (i = 0; i < BSP_CMD_NUM; i++)            // APP_sizeof(BSP_DBG_CMD) / APP_sizeof(BSP_ComnandInfo);
            {
                if (BSP_DBG_CMD[i].Info == NULL)
                    break;

                DBG_printf("%s", BSP_DBG_CMD[i].Info);
            }

            DBG_printf("\n\r->");
            TERMINAML_KB_DATA_NUMBER = 0;
        }        
        else                                            // 扫描所有的命令表
        {
            DBG_printf("\n\r");

            for (i = 0; i < BSP_CMD_NUM; i++)            // APP_sizeof(BSP_DBG_CMD) / APP_sizeof(BSP_ComnandInfo);
            {
                if (SYSTEM_for_command(TERMINAML_KB_BUF, APP_strlen(TERMINAML_KB_BUF)) != 0)
                {
                    if (SYSTEM_for_command(TERMINAML_KB_BUF, APP_strlen(TERMINAML_KB_BUF)) > APP_strlen(BSP_DBG_CMD[i].Cmd))
                        len = SYSTEM_for_command(TERMINAML_KB_BUF, APP_strlen(TERMINAML_KB_BUF));
                    else
                        len = APP_strlen(BSP_DBG_CMD[i].Cmd);
                    
                    if (APP_strncmp(BSP_DBG_CMD[i].Cmd, TERMINAML_KB_BUF, len) == 0)
                    {
                        len = SYSTEM_for_command(TERMINAML_KB_BUF, APP_strlen(TERMINAML_KB_BUF));

                        if (APP_strlen(TERMINAML_KB_BUF) > len)
                            BSP_DBG_CMD[i].Command(&TERMINAML_KB_BUF[len + 1],  APP_strlen(TERMINAML_KB_BUF) - len - 1);
                        else
                            BSP_DBG_CMD[i].Command(NULL,  0);

                        DBG_printf("\n\r->");
                        TERMINAML_KB_DATA_NUMBER = 0;

                        return;
                    }
                }
            }
            
            TERMINAML_KB_DATA_NUMBER = 0;
            DBG_printf("\n\r 错误命令\n\r->");                    
        }
    }        
    else if (key == 8)                                                        // 退格符
    {
        if (TERMINAML_KB_DATA_NUMBER != 0)
        {
            TERMINAML_KB_DATA_NUMBER--;
            TERMINAML_KB_BUF[TERMINAML_KB_DATA_NUMBER] = '\0';   
            DBG_printf("%c", key);
            DBG_printf("%c", ' ');
            DBG_printf("%c", key);
        }
    }                    
    else if ((key >= 32) && (key <= 126) && (TERMINAML_KB_DATA_NUMBER < (TERMINAML_KB_SIZE - 1)))
    {
        TERMINAML_KB_BUF[TERMINAML_KB_DATA_NUMBER] = key;
        TERMINAML_KB_DATA_NUMBER++;
        TERMINAML_KB_BUF[TERMINAML_KB_DATA_NUMBER] = '\0';
        DBG_printf("%c", key);
    }
}

#endif



