/*
 * Main module for testing the PWM Code for the K64F
 * 
 * Author:  
 * Created:  
 * Modified: Carson Clarke-Magrab <ctc7359@rit.edu> 
 * LJBeato
 * 2021
 */

#include "msp.h"
#include "uart.h"
#include "TimerA.h"


/**
 * Waits for a delay (in milliseconds)
 * 
 * del - The delay in milliseconds
 */
void delay(int del){
	volatile int i;
	for (i=0; i<del*50000; i++){
		;// Do nothing
	}
}

///////////////////////////////////////////////////////
//
// Helper function
//
///////////////////////////////////////////////////////
unsigned long  CalcPeriodFromFrequency (double Hz)
{
	double period = 0.0;
	period = (double)SystemCoreClock/Hz;
	period = period;   // we divide by 2 because we want an interrupt for both the rising edge and the falling edge
	return (unsigned long) period;
}

int main(void) {
	// Initialize UART and PWM
	// INSERT CODE HERE
	uart0_init();
	
	// Print welcome over serial
	uart0_put("Running... \n\r");
	
	//Part 1 - UNCOMMENT THIS
	// Generate 20% duty cycle at 10kHz
	TIMER_A0_PWM_Init((20000), 0.2, 1);
	TIMER_A0_PWM_Init((20000), 0, 4);


	//for(;;) ;  //then loop forever
	
	
	 //Part 2 - UNCOMMENT THIS
	for(;;)  //loop forever
	{
		uint16_t dc = 0;
		uint16_t freq = 20000; // Frequency = 10 kHz 
		uint16_t dir = 0;
		char c = 48;
		int i=0;
		
		uart0_put("Forward");

		// 0 to 100% duty cycle in forward direction
		for (i=0; i<100; i++) {
		    // INSERT CODE HERE
			TIMER_A0_PWM_DutyCycle((double)i/100.0, 1);
			delay(10);
		}
		
		// 100% down to 0% duty cycle in the forward direction
		for (i=100; i>=0; i--) {
		    // INSERT CODE HERE
				TIMER_A0_PWM_DutyCycle((double)i/100.0, 1);
			delay(10);
		}
		uart0_put("Reverse");
		// 0 to 100% duty cycle in reverse direction
		for (i=0; i<100; i++) {
			TIMER_A0_PWM_DutyCycle((double)i/100.0, 4);
			
			delay(10);
		}
		
		// 100% down to 0% duty cycle in the reverse direction
		for (i=100; i>=0; i--) {
			TIMER_A0_PWM_DutyCycle((double)i/100.0, 4);
			
			delay(10);
		}

	}
	
	return 0;
}



