#include <xhyp.h>


#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

/*-----------------------------------------------------------*/

/*
 * Checks that all the demo application tasks are still executing without error
 * - as described at the top of the file.
 */
//static long prvCheckOtherTasksAreStillRunning( void );

/*
 * The task that executes at the highest priority and calls
 * prvCheckOtherTasksAreStillRunning().  See the description at the top
 * of the file.
 */
static void xTask1( void *pvParameters );
static void xTask2( void *pvParameters );

/*
 * Configure the processor for use with the Atmel demo board.  This is very
 * minimal as most of the setup is performed in the startup code.
 */
static void prvSetupHardware( void );

/*
 * The idle hook is just used to stream data to the USB port.
 */
void vApplicationIdleHook( void );
/*-----------------------------------------------------------*/

/*
 * Setup hardware then start all the demo application tasks.
 */
int main( void )
{
	/* Setup the ports. */
	//xhyp_console("hello\n", 6);
	debugp("Starting FreeRTOS............\n");
	//xhyp_console("hello\n", 6);
	prvSetupHardware();

	debugp("Create Task2................\n");
	xTaskCreate( xTask2, ( signed char * )"Task2", 0x100, NULL, ( tskIDLE_PRIORITY + 4 ), NULL );
	debugp("Create Task1................\n");
	xTaskCreate( xTask1, ( signed char * )"Task1", 0x100, NULL, ( tskIDLE_PRIORITY + 4 ), NULL );

	debugp("Start Scheduler.............\n");
	vTaskStartScheduler();

	debugp("Stopping FreeRTOS\n");
	xhyp_idle();
while(1) debugp(".........END.........\n");;

	return 0;
}


/*-----------------------------------------------------------*/

/*
 * Checks that all the demo application tasks are still executing without error
 * - as described at the top of the file.
 */
/*
static long prvCheckOtherTasksAreStillRunning( void )
{
	return 0;
}
*/

/*
 * The task that executes at the highest priority and calls
 * prvCheckOtherTasksAreStillRunning().  See the description at the top
 * of the file.
 */
#define MAXI	3000
void delay(int n)
{
	int i;
	int j;
	int k = n;

	while(k--) {
		i = MAXI;
		while(i--) {
			j = MAXI;
			while(j--);
		}
	}
	
}

int Total = 0;

static void xTask2( void *pvParameters )
{
	int xCount2 = 100;

	debugp("\n");
	while(1) {
		xCount2++;
		Total++;
		//portDISABLE_INTERRUPTS();
		debugp("Count2: %d Total %d\n", xCount2, Total);
		//portENABLE_INTERRUPTS();
		delay(10);
	}
}

static void xTask1( void *pvParameters )
{
	int xCount1 = 0;
	debugp("\n");
	while(1) {
		xCount1++;
		//portDISABLE_INTERRUPTS();
		debugp("Count1: %d Total %d\n", xCount1, Total);
		//portENABLE_INTERRUPTS();
		delay(10);
	}
}


/*
 * Configure the processor for use with the Atmel demo board.  This is very
 * minimal as most of the setup is performed in the startup code.
 */
static void prvSetupHardware( void )
{
	debugp("\n");
}

/*
 * The idle hook is just used to stream data to the USB port.
 */
void vApplicationIdleHook( void )
{
	debugp("\n");
}
