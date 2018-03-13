//*****************************************************************************
//
// startup_gcc.c - Startup code for use with GNU tools.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include "system_stm32f0xx.h"

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the interrupt handler used by the application.
//
//*****************************************************************************
extern void NMI_Handler(void);
extern void HardFault_Handler();
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void USB_IRQHandler(void);
//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
static uint32_t pui32Stack[128];
#define BootRAM ((void *)(0xF108F85F))
//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	(void (*)(void))((uint32_t)pui32Stack + sizeof(pui32Stack)),
	// The initial stack pointer
	ResetISR, 			//Reset_Handler
	NMI_Handler, 		//	NMI_Handler
	HardFault_Handler, 	//	HardFault_Handler
	0                              ,//Reserved
	0                              ,//Reserved
	0                              ,//Reserved
	0                              ,//Reserved
	0                              ,//Reserved
	0                              ,//Reserved
	0                              ,//Reserved
	SVC_Handler                    ,//SVCall Handler
	0                              ,//Reserved
	0                              ,//Reserved
	PendSV_Handler                 ,//PendSV Handler
	IntDefaultHandler                ,//SysTick Handler

	//External Interrupts
	IntDefaultHandler                ,//Window Watchdog
	0                              ,//Reserved
	IntDefaultHandler                 ,//RTC through EXTI Line
	IntDefaultHandler               ,//FLASH
	IntDefaultHandler                 ,//RCC
	IntDefaultHandler             ,//EXTI Line 0 and 1
	IntDefaultHandler             ,//EXTI Line 2 and 3
	IntDefaultHandler            ,//EXTI Line 4 to 15
	0                              ,//Reserved
	IntDefaultHandler       ,//DMA1 Channel 1
	IntDefaultHandler     ,//DMA1 Channel 2 and Channel 3
	IntDefaultHandler     ,//DMA1 Channel 4 and Channel 5
	IntDefaultHandler                ,//ADC1 
	IntDefaultHandler ,//TIM1 Break, Update, Trigger and Commutation
	IntDefaultHandler             ,//TIM1 Capture Compare
	0                              ,//Reserved
	IntDefaultHandler                ,//TIM3
	0                              ,//Reserved
	0                              ,//Reserved
	IntDefaultHandler               ,//TIM14
	0                              ,//Reserved
	IntDefaultHandler               ,//TIM16
	IntDefaultHandler               ,//TIM17
	IntDefaultHandler                ,//I2C1
	0                              ,//Reserved
	IntDefaultHandler                ,//SPI1
	0                              ,//Reserved
	IntDefaultHandler              ,//USART1
	IntDefaultHandler              ,//USART2
	0                              ,//Reserved
	0                              ,//Reserved
	USB_IRQHandler                 ,//USB
	BootRAM
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
//extern uint32_t _etext;
//extern uint32_t _data;
//extern uint32_t _edata;
//extern uint32_t _bss;
//extern uint32_t _ebss;

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;




//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
	void
ResetISR(void)
{
	uint32_t *pui32Src, *pui32Dest;

	//
	// Copy the data segment initializers from flash to SRAM.
	//
	pui32Src = &_sidata;
	for(pui32Dest = &_sdata; pui32Dest < &_edata; )
	{
		*pui32Dest++ = *pui32Src++;
	}

	//
	// Zero fill the bss segment.
	//
	for(pui32Dest = &_sbss; pui32Dest < &_ebss; )
	{
		*pui32Dest++ = 0;
	}

	//
	// Call the application's entry point.
	//
	SystemInit();
	//__libc_init_array();
	main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
	static void
IntDefaultHandler(void)
{
	//
	// Go into an infinite loop.
	//
	while(1)
	{
	}
}
