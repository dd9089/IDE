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
	
	// Generate 20% duty cycle at 10kHz
	//2 DC motors (Driving)
	TIMER_A0_PWM_Init((20000), 0.2, 1);
	TIMER_A0_PWM_Init((20000), 0, 4);
	TIMER_A0_PWM_Init((20000), 0.2, 2);
	TIMER_A0_PWM_Init((20000), 0, 3);
	
	//Servo motor (stering)
	TIMER_A2_PWM_Init((800), 0.075, 1);

	
	for(;;)  //loop forever
	{
		uint16_t dir = 0;
		char c = 48;
		
		if (dir == 0){
			uart0_put("Forward");
			
			TIMER_A0_PWM_DutyCycle(0.3, 1);
			TIMER_A0_PWM_DutyCycle(0.3, 2);
			delay(100);
			//turn clockwise
			TIMER_A2_PWM_DutyCycle(0.05, 1);
			delay(50);
			TIMER_A2_PWM_DutyCycle(0.075, 1);
		}
		
		if (dir == 1){
			uart0_put("Reverse");
			TIMER_A0_PWM_DutyCycle(0.3, 4);
			TIMER_A0_PWM_DutyCycle(0.3, 3);
			delay(10);
		}

	}
	
	return 0;
}



