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
		TIMER_A0_PWM_DutyCycle(0.4, 1);

		uart0_put("Reverse");
		
		TIMER_A0_PWM_DutyCycle(0.4, 4);

	}
	
	return 0;
}

void forward(void){
	TIMER_A0_PWM_DutyCycle(0.4, 1);
}

void reverse(void){
	TIMER_A0_PWM_DutyCycle(0.4, 4);
}

void motor_init(void){
	TIMER_A0_PWM_Init((20000), 0, 1);
	TIMER_A0_PWM_Init((20000), 0, 4);
}


