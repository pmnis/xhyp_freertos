/*
    FreeRTOS V7.0.2 - Copyright (C) 2011 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "timers.h"
#include "StackMacros.h"

#include "xhyp.h"
#include "shared_page.h"
#include <stdio.h>

/*-----------------------------------------------------------*/

struct shared_page * volatile xhyp_sp = (struct shared_page *) 0x02000000;
#define portINITIAL_SPSR	0x10
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE * pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
{
	struct context *ctx;

	*pxTopOfStack = 0;	/* Clear location	*/
	pxTopOfStack--;		/* Reserve room		*/
	ctx = (struct context *) pxTopOfStack;
	ctx--;

	/* Clear context	*/
	memset(ctx, 0, sizeof(*ctx));

	ctx->regs.regs[0] = (unsigned long )pvParameters;
	ctx->sregs.sp = (unsigned long )ctx;
	ctx->sregs.pc = (unsigned long )pxCode;
	ctx->sregs.spsr = portINITIAL_SPSR;

	return (unsigned long *) ctx;

}
/*-----------------------------------------------------------*/
extern volatile void * volatile pxCurrentTCB;

void prvStartTask( void )
{
	unsigned long *p = (unsigned long *)pxCurrentTCB;
	struct context *ctx;

	debugp("pxCurrentTCB: %08lx\n", pxCurrentTCB);
	ctx = (struct context *) *p;

	*p += sizeof(*ctx);	/* reset TopOfStack	*/
	ctx->sregs.sp = *p;	/* reset stack 		*/

	debugp("pc %08lx lr %08lx\n", ctx->sregs.pc, ctx->sregs.lr);
	xhyp_task_switch(ctx);

	/* Should never been reached	*/
	debugp("Arrrrgggghhhh\n");
	while(1);
}

/*-----------------------------------------------------------*/
unsigned long irq_stack[1024];
#define XHYP_IRQ_TIMER	0x10
void show_ctx(struct context *ctx)
{
	unsigned long *p = (unsigned long *)ctx;
	int i;

	for (i = 0; i < 16; i++)
		debugp("reg[%02d] : %08lx\n", i, *p++);
}

struct context	saved_ctx[3];
struct context *current = &saved_ctx[1];
struct context *saved   = &saved_ctx[2];

void prvIrqTimer(void)
{
	volatile unsigned volatile long *p = (volatile unsigned long * volatile)pxCurrentTCB;
	struct context * volatile ctx = (struct context *) *p;
	//struct context *ctx = (struct context *) *((unsigned long *)pxCurrentTCB);

	ctx--;		/* Decrement stack	*/
	ctx--;		/* Decrement stack	*/


	*ctx = xhyp_sp->context_irq;	/* and save context	*/
	*p = (unsigned long) ctx;	/* adjust stack	*/
	debugp("ctx at %p\n", ctx);

	vTaskIncrementTick();	/* increment ticks	*/
	vTaskSwitchContext();	/* get next task	*/

	p = (unsigned long *)pxCurrentTCB;	/* Point to stack */
	ctx = (struct context *) *p;		/* point to context */
	debugp("ctx at %p\n", ctx);
	xhyp_sp->context_irq = *ctx;	/* set context in shared page	*/
				/* for irq_return		*/
	ctx++;		/*Increment stack	*/
	ctx++;		/*Increment stack	*/
	*p = (unsigned long) ctx;
}

void prvIrqHandler(unsigned long mask)
{
	debugp("mask %08lx\n", mask);
	if (mask & XHYP_IRQ_TIMER)
		prvIrqTimer();
	xhyp_irq_return(0);
}

static void prvSetupTimerInterrupt( void )
{
	xhyp_irq_request(prvIrqHandler, irq_stack + 1024);
	xhyp_irq_enable(XHYP_IRQ_TIMER);
	xhyp_irq_enable(0);
	xhyp_sp->v_irq_enabled = XHYP_IRQ_TIMER;
}

portBASE_TYPE xPortStartScheduler( void )
{
	prvSetupTimerInterrupt();
	prvStartTask();

	return pdFALSE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	debugp("\n");
	while(1);
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
	debugp("\n");
	while(1);
}

/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
	debugp("\n");
	while(1);
}

/*-----------------------------------------------------------*/

void vPortYieldHandler( void )
{
	debugp("\n");
	while(1);
}


extern void _xhyp_intr_enable(int);
extern void _xhyp_intr_disable(int);
extern void _xhyp_task_switch(struct context *);

void xhyp_irq_enable(unsigned long mask)
{
	debugp("mask %08lx\n", mask);
	_xhyp_intr_enable(mask);
}
void xhyp_irq_disable(unsigned long mask)
{
	debugp("mask %08lx\n", mask);
	_xhyp_intr_disable(mask);
}

void xhyp_critical_enter(void)
{
	xhyp_irq_disable(0);
}
void xhyp_critical_exit(void)
{
	xhyp_irq_enable(0);
}
void xhyp_task_switch(struct context *ctx)
{
	debugp("pc at %08lx\n", ctx->sregs.pc);
	_xhyp_task_switch(ctx);
}
