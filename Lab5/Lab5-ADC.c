/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "leds.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
// The sprintf function seemed to cause a hange in the interrupt service routine.
// I think if we increase the HEAP size, it will work
// change to Heap_Size       EQU     0x00000200 in startup_msp432p401r_uvision.s


BOOLEAN Timer1RunningFlag = FALSE;
BOOLEAN Timer2RunningFlag = FALSE;

unsigned long MillisecondCounter = 0;

unsigned int analogIn = 0;



// Interrupt Service Routine for Timer32-1
void Timer32_1_ISR(void)
{
		TIMER32_1->INTCLR = 1;
		Timer1RunningFlag = TRUE;
		analogIn = ADC_In();
	
}
// Interrupt Service Routine
void Timer32_2_ISR(void)
{

}



// main
int main(void)
{
	char temp[64];
	double cel = 0;
	double far = 0; 
	double v = 0;
	//initializations
	uart0_init();
	uart0_put("\r\nLab5 ADC demo\r\n");

	

	LED1_Init();
	LED2_Init();
	Switch2_Init();
	ADC0_InitSWTriggerCh6();
	Timer32_1_Init(&Timer32_1_ISR, 1500000, T32DIV1);
	EnableInterrupts();
  while(1)
	{
		if (Timer1RunningFlag == TRUE){
			v = (2.5/ 16383.0) * analogIn;
			cel = (v - 0.55) * 100;
			far = (cel * 1.8 + 32);
			sprintf(temp, "Celcius: %f Farenheight: %f \r\n", cel, far);
			//sprintf(temp, "ADC Value: %u (0x%X)\r\n", analogIn, analogIn);
			uart0_put(temp);
			Timer1RunningFlag = FALSE;
		}
		
  }
}

