/*****************************************************************************************
��Ȩ����:        ---------------
�汾��:          1.0.0
��������:        2010.05.11
�ļ���:          app_compile.h
����:            Ӱ����
����˵��:        �������������ļ�
����˵��:        Evaluation Board
�����ļ���ϵ:    ���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#ifndef APP_COMPILE_PRESENT
#define APP_COMPILE_PRESENT




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.08
����˵��:   ���ÿ���
����˵��:   ��
*****************************************************************************************/
#define WDT_DELAY                       (200)                       // WDT ʱ����

#define HD_VERSION                      (100)                       // Ӳ���汾 220 == H2.20
#define SF_VERSION                      (9774)                      // ����汾 SVNxxxx
#define DT_DEVLOPER                     "2017-02-21"                // "DOTT: 2014 -11 -12"




/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define TICK_FREQ_MUL                   (20)                        // Ԥ���ȱ�Ƶ
#define TICKRATE_HZ                     (2000)                      /* 2000 ticks per second */
#define ADCRATE_HZ                      (1000000)                   /* 1000000 HZ */




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.08
����˵��:   �ͺ�ȷ��
����˵��:   ��
*****************************************************************************************/
#ifdef  IFLASH_STM32F0_P1
    #include "app_p1.h"
    #define PRODUCT_NAME                  "MPT-II"
    #define APP_NAME                      "iflash_STM32F0_P1.bin"

    #define BLUE_SPP_NAME                 "MPT-II(SPP)"
    #define BLUE_BLE_NAME                 "MPT-II(BLE)"
#endif




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:        1.0.0
��������:    2009.09.08
����˵��:   ���ÿ���
����˵��:   ��
*****************************************************************************************/
#define LED_SUPPORT                         1                           // �Ƿ����LEDָʾ��
#define KEY_SUPPORT                         1                           // �Ƿ����KEY֧��
#define WDT_SUPPORT                         1                           // �Ƿ����WDT֧��
#define ADC_SUPPORT                         1                           // �Ƿ����ADC֧��
#define IAP_SUPPORT                         1                           // �Ƿ����IAP֧��
#define SPI_SUPPORT                         1                           // �Ƿ����SPI֧��
#define MX25L1602_SUPORT                    0                           // �Ƿ����MX25L1602֧��
#define PWM_SUPPORT                         0                           // �Ƿ����PWM֧��
#define FLASH_SUPPORT                       1                           // �Ƿ����FLASH����
#define POWER_SUPPORT                       1                           // �Ƿ����POWER����
#define MOTOR_SUPPORT                       1                           // �Ƿ����MOTOR����




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2010.05.11
����˵��:   ��������������
����˵��:   ��
*****************************************************************************************/
#define    uint8        unsigned   char                                 // �޷��� 8λ���ͱ���
#define    int8         signed     char                                 // �з��� 8λ���ͱ���
#define    uint16       unsigned   short                                // �޷���16λ���ͱ���
#define    int16        signed     short                                // �з���16λ���ͱ��� 
#define    uint32       unsigned   int                                  // �޷���32λ���ͱ���
#define    int32        signed     int                                  // �з���32λ���ͱ���
#define    uint64       unsigned   long long                            // �޷���64λ���ͱ���
#define    int64        signed     long long                            // �з���64λ���ͱ���
#define    float32      float                                           // �����ȸ�����(32λ����)
#define    float64      double                                          // ˫���ȸ�����(64λ����)

#define    FALSE        0
#define    TRUE         1

#define    false        0
#define    true         1

#define    DEF_OFF      0
#define    DEF_ON       1




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.09.08
����˵��:   ���ÿ���
����˵��:   ��
*****************************************************************************************/
#define LOCAL_CODE                     (2014019999)                     // 4λ�� + 2λ�� + 4λ���
#define LOCAL_PASSWORD                 (2014019999)                     // Ĭ����������к�һ��

#define PRINTER_XByte                   48                              // X���ֽ���
#define PRINTER_XBit                    384                             // X�������

#define UART1_BPS                       115200                          // �û��ٶ� 
#define UART2_BPS                       115200                          // �����ٶ�  




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:        1.0.0
��������:    2009.09.08
����˵��:   ���ÿ���
����˵��:   ��
*****************************************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"

#include "includes.h"




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.10.13
����˵��:   �ṹ����
����˵��:   ��
*****************************************************************************************/
#define __APP_PACKED(n)        __attribute__ ((packed, aligned(n)))            // �ṹ���� 

extern  void  TICK_DisableIRQ(void);
extern  void  TICK_EnableIRQ(void);




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2009.10.04
����˵��:   ϵͳ����
����˵��:   ��
*****************************************************************************************/
#if (DEBUG_SUPPORT == 1)
    #define dprintf(fmt, args...)       printf(fmt, ##args)                // ��Ϣ��ӡ
#endif
#if (DEBUG_SUPPORT == 0)
    #define dprintf(fmt, args...)
#endif

#define ENTER_CRITICAL()               // TICK_DisableIRQ()                  // �����ж�
#define EXIT_CRITICAL()                // TICK_EnableIRQ()                   // �˳��ж�

#define qprintf(fmt, args...)           dprintf(fmt, ##args)               // ��ӡ
#define mprintf(fmt, args...)           dprintf(fmt, ##args)               // ��ӡ
#define pprintf(fmt, args...)           dprintf(fmt, ##args)               // ��ӡ
#define bprintf(fmt, args...)           dprintf(fmt, ##args)               // ��ӡ
#define DBG_printf(fmt, args...)        dprintf(fmt, ##args)               // ��ӡ
#define APP_printf(fmt, args...)        dprintf(fmt, ##args)               // ��ӡ

#define APP_sprintf                     sprintf                            // ��ӡ
#define APP_malloc(a)                   malloc(a)                          // �����ڴ�
#define APP_free(a)                     free(a)                            // �ͷ��ڴ�
#define APP_strlen(a)                   strlen(a)                          // ����
#define APP_sizeof(a)                   sizeof(a)                          // ��С
#define APP_strcat(a, b)                strcat(a, b)                       // ����
#define APP_strstr(a, b)                strstr(a, b)                       // ��������
#define APP_strchr(a, b)                strchr(a, b)                       // ��������
#define APP_strcmp(a, b)                strcmp(a, b)                       // �Ƚ�
#define APP_strncmp(a, b, n)            strncmp(a, b, n)                   // �Ƚ�
#define APP_strcpy(a, b)                strcpy(a, b)                       // ����
#define APP_strncpy(a, b, n)            strncpy(a, b, n)                   // ����
#define APP_abs(a)                      abs(a)                             // ����ֵ
#define APP_fabs(a)                     fabs(a)                            // ����ֵ
#define APP_atoi(a)                     atoi(a)                            // �ַ���ת����
#define APP_atol(a)                     atol(a)                            // �ַ���ת����
#define APP_atof(a)                     atof(a)                            // �ַ���ת����
#define APP_memset(a, b, n)             memset(a, b, n)                    // �ڴ�����
#define APP_memcpy(a, b, n)             memcpy(a, b, n)                    // �ڴ濽��
#define APP_memcmp(a, b, n)             memcmp(a, b, n)                    // �ڴ�Ƚ�
#define APP_memmove(a, b, n)            memmove(a, b, n)                   // �ڴ��ƶ�




#endif


