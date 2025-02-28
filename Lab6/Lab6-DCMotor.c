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

int main(void) {
	// Initialize UART and PWM
	// INSERT CODE HERE

	// Print welcome over serial
	put("Running... \n\r");
	
	/* Part 1 - UNCOMMENT THIS
	// Generate 20% duty cycle at 10kHz
	// INSERT CODE HERE
	
	for(;;) ;  //then loop forever
	*/
	
	/* Part 2 - UNCOMMENT THIS
	for(;;)  //loop forever
	{
		uint16_t dc = 0;
		uint16_t freq = 10000; // Frequency = 10 kHz 
		uint16_t dir = 0;
		char c = 48;
		int i=0;
		
		// 0 to 100% duty cycle in forward direction
		for (i=0; i<100; i++) {
		    // INSERT CODE HERE
			
			delay(10);
		}
		
		// 100% down to 0% duty cycle in the forward direction
		for (i=100; i>=0; i--) {
		    // INSERT CODE HERE
			
			delay(10);
		}
		
		// 0 to 100% duty cycle in reverse direction
		for (i=0; i<100; i++) {
		    // INSERT CODE HERE
			
			delay(10);
		}
		
		// 100% down to 0% duty cycle in the reverse direction
		for (i=100; i>=0; i--) {
		    // INSERT CODE HERE
			
			delay(10);
		}

	}
	*/
	return 0;
}



