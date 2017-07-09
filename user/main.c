

#include "app_types.h"
#include "app_cmd.h"
#include "app_debug.h"
#include "app_adc.h"
#include "app_led.h"
#include "app_kbd.h"
#include "app_spi.h"
#include "app_wdt.h"
#include "app_pwm.h"
#include "app_uart.h"
#include "app_usart.h"
#include "app_power.h"

#include "config.h"
#include "updata.h"

#include "main.h"




/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
extern  uint32  SystemCoreClock;

extern  uint16  bmpPrintInterTime;
extern  uint16  BATTRY_LOW_PowerOFF_Count;

extern  uint8   sys_battery_Pre;
extern  uint8   sys_battery_voltage;

extern  uint8   KBD_LongPress_POWER_Count;
extern  uint8   PrinterERROR;
extern  uint8   BattLowPowerERROR;
extern  uint8   MOTOR_Inc_FLAG;
extern  uint8   MOTOR_Warm_FLAG;
extern  uint8   MOTOR_Warm_BEGIN;

extern  uint16  UART1_ActiveCOUNT;
extern  uint16  UART2_ActiveCOUNT;
extern  uint16  KBD_PrinterTestCount;

extern  uint8   UARTPro_PID;
extern  uint8   UARTPro_CMD;
extern  uint8   UARTPro_Num;
extern  uint8   UARTPro_CaseMode;
extern  uint16  UARTPro_CountALL;

extern  uint16  uartPrinter_count;

extern  void    SystemCoreClockUpdate (void);


#if 1


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
uint8   SysTick_COUNT     = 0;
uint8   SysTick_JumpFlag  = 0;
uint8   SysTick_1HZ_COUNT = 0;
uint8   SysTick_5HZ_COUNT = 0;

uint8   ADC_RunFlag       = FALSE;
uint8   SYSTEM_RunFlag    = FALSE;
uint8   SYSTEM_RunDelayCount = 0;

uint32  SysTimeTick = 0;

uint8   BlueLinkOK = false;

uint8   STB_TempLogicHL = 0;
uint8   STB_TempCountH  = 0;
uint8   STB_TempCountL  = 0;
uint8   STB_PrintfCount = 0;

uint16  MotorVHCount  = 0;
uint16  paperEndCount = 0;
uint16  battLowCount  = 0;

uint8   MotorSTB_TimeValue = MOTOR_WARM_TICK;
uint8   MotorIncTick_COUNT  = 0;
uint8   MotorWarmTick_COUNT = 0;

uint8   OpenBEEP_Flag   = FALSE;
uint8   OpenBEEP_Status = 0;
uint16  OpenBEEP_COUNT  = 0;
uint16  OpenBEEP_TIMEER = 0;

uint16  OpenRunDelay_COUNT = 0;

uint16  SecondTimer_COUNT = 0;

uint16  STB_TempH = STB_MaxTempH;                // ��������
uint16  STB_TempL = STB_MaxTempL;                // ����������

uint16  ADC_60C_Value = ADC_TM_60C;              // 60�ȱ�׼ֵ  3000�ı�


extern  uint8  getFlowInfo_Index(uint8 cmd, uint8 comType);
extern  void   Pin_Status(void);


// �Ŵ�10����ʱ��
void BEEP_Player(uint8 second)
{
    if (OpenBEEP_Flag == TRUE)
        return;

    OpenBEEP_TIMEER = (second * (TICKRATE_HZ / 10));
    OpenBEEP_Flag   = TRUE;
}


#define PRINT_PREHEAT                   1                       // ��ӡͷ60��Ԥ�ȼ���

uint8  SystickHalfCount = 0;
uint8  SystickCount = 0;
uint8  printPreHeatFlag = FALSE;


__align(4)   uint8   HZPrintBuff[HZPrintSIZE];                // 48 * 48 = 2304


/********************************************************************************
�������ƣ�Delay()
��    �ܣ���ʱ����
��    ������
�� �� ֵ����
*********************************************************************************/
void Delay(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
		nCount--;
  }
}




/********************************************************************************
�������ƣ�Delay_Us()
��    �ܣ������ʱ΢�뼶����
��    ������
�� �� ֵ����
*********************************************************************************/
void Delay_Us(uint32_t nCount)
{
  /* 10uS�ӳ�=>10.8uS,100uS�ӳ�=>104uS*/
  while (nCount != 0)
  {
	   nCount--;  
	   Delay(150);
  }
}




/********************************************************************************
�������ƣ�Delay_Ms()
��    �ܣ������ʱ���뼶����
��    ������
�� �� ֵ����
*********************************************************************************/
void Delay_Ms(uint32_t nCount)
{
  /* 10uS�ӳ�=>10.8uS,100uS�ӳ�=>104uS*/
  while (nCount != 0)
  {
	nCount--;  
	Delay(15000);
  }
}




/*******************************************************************************
* ��������: void SysTick_Handler(void)
* ��������: �δ�ʱ���ص�
* �������: void
* ���ز���: ��
********************************************************************************/
void SysTick_Handler(void)
{
    uint8   TimeValue;
    uint16  ADCValue = 0;

    ADCValue = ADCValue;
    TimeValue = TimeValue;


    //============================================================
    //============================================================

    // �뱶�ٶ�, 0.05ms
    SystickHalfCount++;
    if (SystickHalfCount <= (TICK_FREQ_MUL / 2))
    {
        SystickHalfCount = 0;

        //============================================================
        //============================================================


        //============================================================
        //============================================================

        //============================================================
        //============================================================

        #if 0
            // ���ݵ�ѹ�仯ѡ���������ʱ��
            if (sys_battery_Pre <= 20)                  // ����20%���� 
            {
                STB_TempH = STB_MaxTempH;               // ��������
                STB_TempL = STB_MaxTempL;               // ����������
            }
            else if (sys_battery_Pre <= 40)             // ����40%���� 
            {
                STB_TempH = STB_MaxTempH;               // ��������
                STB_TempL = STB_MaxTempL;               // ����������
            }
            else if (sys_battery_Pre <= 60)             // ����60%���� 
            {
                STB_TempH = STB_MaxTempH;               // ��������
                STB_TempL = STB_MaxTempL;               // ����������
            }
            else if (sys_battery_Pre <= 80)             // ����80%���� 
            {
                STB_TempH = STB_MaxTempH;               // ��������
                STB_TempL = STB_MaxTempL;               // ����������
            }
            else
            {
                STB_TempH = STB_MaxTempH;               // ��������
                STB_TempL = STB_MaxTempL;               // ����������
            }
        #endif
    }

    //============================================================
    //============================================================

    // ˫���ٶ�
    SystickCount++;
    if (SystickCount <= TICK_FREQ_MUL)
        return;
    SystickCount = 0;

    //============================================================
    //============================================================

    // 2000HZ ����
#if (ADC_SUPPORT == 1)
    ADC_FlushScanf();
#endif

    //============================================================
    //============================================================


    // ��ֹδ����ʱ����
    if (SYSTEM_RunFlag == FALSE)
        return;

    // ϵͳʱ��Ƭ
    SysTimeTick++;

    // ������ʱ
    OpenRunDelay_COUNT++;

#if (KEY_SUPPORT == 1) 
    if (KBD_LongPress_POWER_Count >= POWER_OffTime)              // 3 ��ػ�
        return;
#endif

#if (POWER_SUPPORT == 1)
    // VH����ʱ�����
    if (POWER_StatusIO(PM_MOTOR) == 1)
        MotorVHCount++;
#endif

#if (KEY_SUPPORT == 1)
    // ���Դ�ӡҳ�������
    KBD_PrinterTestCount++;
#endif

    //============================================================
    //============================================================

    // 10HZ ��Ƶ����
    SysTick_COUNT++;
    if (SysTick_COUNT >= (TICKRATE_HZ / 10))
    {
        SysTick_COUNT = 0;
        SysTick_JumpFlag = TRUE;
    }

    // 4HZ ������
    SecondTimer_COUNT++;
    if (SecondTimer_COUNT >= (TICKRATE_HZ / 4))
    {
        SecondTimer_COUNT = 0;

        #if (LED_SUPPORT == 1)
        LED_FlushScanf();
        #endif
    }

    //============================================================
    //============================================================

    // ����̻����Ķ�ʱ
#if (UPDATA_SUPPORT == 1)
    RequestFrameTIMER();
#endif
}




void x_printf(char *fmt,...)
{
#if (DEBUG_SUPPORT == 1)
    va_list  ap;
    char  i, len, str[100];

    va_start(ap, fmt);
    vsprintf(str, fmt, ap);
    len = APP_strlen(str);
    for (i = 0; i < len; i++)
        DEBUG_PutChar(str[i]);
    va_end(ap);
#endif
}




/*******************************************************************************
* ��������: Systick_Init();
* ��������: �δ�ʱ����ʼ��
* �������: void
* ���ز���: ��
********************************************************************************/
void Systick_Init(void)
{    
    SysTick_Config(SystemCoreClock / (TICKRATE_HZ * TICK_FREQ_MUL));
}



extern void usb_start(void);
/********************************************************************************
��������: main()
��    ��: ���������
��    ��: ��
�� �� ֵ: ��	  
*********************************************************************************/
int main(void)
{
    uint32  i = 0, *bootVectorTable;  
    uint8   vaule = 0;

    i = i;
    vaule = vaule;

#if 1
    /*!< At this stage the microcontroller clock setting is already configured,  
       this is done through SystemInit() function which is called from startup 
       file (startup_stm32f0xx.s) before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to 
       system_stm32f0xx.c file 
    */   
  
    /* Relocate by software the vector table to the internal SRAM at 0x20000000 ***/    
  
    /* Copy the vector table from the Flash (mapped at the base of the application 
     load address 0x08003000) to the base address of the SRAM at 0x20000000. */  
    bootVectorTable = (uint32_t*)0x20000000;
    for(i = 0; i < 48; i++)
    {
        bootVectorTable[i] = *(__IO uint32_t*)(APPLICATION_ADDRESS + (i<<2));  
    }
  
    /* Enable the SYSCFG peripheral clock*/  
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);    //��Ҫ�޸ĳ�����  
    /* Remap SRAM at 0x00000000 */  
    SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);  
#endif

    //ϵͳʱ�����ú�����ͨ����ͬ��ʱ�Ӷ��壬��ѡ��ͬ����Ƶ 
    SystemInit();                
    Systick_Init();

#if (DEBUG_SUPPORT == 1)
    ConfigureDEBUG(115200);
#endif

#if (DEBUG_SUPPORT == 1)
    TERMINAML_Initialize();
    TERMINAML_Interface();
    TERMINAML_Systems();

    SystemCoreClockUpdate();
#endif

#if (POWER_SUPPORT == 1)
    ConfigurePOWER();
#endif

#if (LED_SUPPORT == 1)
    ConfigureLED();
#endif

#if (KEY_SUPPORT == 1)
    ConfigureKBD();
#endif

#if (USART_USE_BUSY == 1)
    ConfigureUSART_BUSY();
#endif

#if (USART1_SUPPORT == 1)
    ConfigureUSART1(UART1_BPS);
#endif

#if (USART2_SUPPORT == 1)
    ConfigureUSART2(UART2_BPS);
#endif

#if (ADC_SUPPORT == 1)
    ConfigureADC();
#endif

#if (SPI_SUPPORT == 1)
    ConfigureSPI();
    uint8_t input[64] = {0};
    uint8_t output[64] = {0};
    for (i=0; i<64; i++)
    	input[i] = i;
    spi_flash_test(0,input,64,output);
    APP_printf("output is :\r\n");
    for (i=0; i<64; i++)
	{
		APP_printf("%03d ",output[i]);
		if ((i+1)%16 == 0)
			APP_printf("\r\n");
	}
#endif

#if (FLASH_SUPPORT == 1)
    InitConfig();
#endif

#if (UPDATA_SUPPORT == 1)
    ConfigureUPDATA();
#endif

#if (PWM_SUPPORT == 1)
    ConfigurePWM();
#endif

#if (WDT_SUPPORT == 1)
    ConfigureWDTC();
#endif

    // �� ϵͳ ��Դ
    POWER_Manager(PM_POWER,  DEF_ON); 

    // ��ʼ����
    SYSTEM_RunFlag = TRUE;
    ADC_RunFlag    = TRUE;

#if 1
    // ������һ��            
    #if (PWM_SUPPORT == 1)
        PWMC_LevelCTRL(1);
    #endif
    #if (PWM_SUPPORT == 0)
        POWER_Manager(PM_BEEP,   DEF_ON);          // �� ���� ��Դ
    #endif

    BEEP_Player(5);
#endif

#if (DEBUG_SUPPORT == 1)
    APP_printf("\n\r\n\r app_run...... \n\r");
#endif
	  usb_start();
    while(1)
    {
        #if 1
        if (0)  break;
        #endif
        #if (DEBUG_SUPPORT == 1)
            TERMINAML_Operation();
        #endif

        // 10HZ ����
        if (SysTick_JumpFlag == TRUE)
        {
            SysTick_JumpFlag = FALSE;

            // 5HZ ����
            SysTick_5HZ_COUNT++;
            if (SysTick_5HZ_COUNT >= 2)
            {
                SysTick_5HZ_COUNT = 0;

                #if (KEY_SUPPORT == 1)
                    KBD_GetPinValue();
                #endif

                #if 0
                    USART_SendChar(USART2, 91);
                   // APP_printf("\n\r ADC: %d, %d, %d", ADC_GetBatteryADC(), ADC_GetPaperADC(), ADC_GetTM_ADC());
                #endif
                
                // ����ʹ��====
                // Pin_Status();
                // ADCStart(ADC_TM);
            }

            // 1HZ ����
            SysTick_1HZ_COUNT++;
            if (SysTick_1HZ_COUNT >= 10)
            {
                SysTick_1HZ_COUNT = 0;

                // ������ʱ
                if (SYSTEM_RunDelayCount < 5)
                    SYSTEM_RunDelayCount++;

                #if (WDT_SUPPORT == 1) 
                    WDTC_Clear();
                #endif

                #if (MOTOR_PM_PROTECT == 1)
                    // ��ʱ�رմ�ӡ����Դ
                    if (MotorVHCount >= (TICKRATE_HZ * 2))
                    if (POWER_StatusIO(PM_MOTOR) == 1)
                    {
                        APP_printf("\n\r VH Close \n\r");
        
                        POWER_Manager(PM_MOTOR,  DEF_OFF);  
                        MotorVHCount = 0;
                    }
                #endif
            }
        }
    }

    return 0;	    	
}

#endif


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
        ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {
        APP_printf("&");
    }
}
#endif




