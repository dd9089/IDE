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

int main(void) {
	// Initialize UART and PWM
	uart0_init();
	
	// Print welcome over serial
	uart0_put("Running... \n\r");
	// Configure the GPIO Pins for Output
	P4 -> SEL0 &= ~(BIT4 | BIT3 | BIT2 | BIT1);
	P4 -> SEL1 &= ~(BIT4 | BIT3 | BIT2 | BIT1);
  P4 -> DIR |= (BIT4 | BIT3 | BIT2 | BIT1);
	
	int forward = 1;
	int phase = 0;
	while ( 1 ){
		// Turn off all coils , Set GPIO pins to 0
		P4->OUT &= ~(BIT1 | BIT2 | BIT3 | BIT4);
		// Set one pin high at a time
		if ( forward ) {
		if ( phase == 0) { P4->OUT |= BIT1; phase ++;} // A ,1 a
		else if ( phase == 1) { P4->OUT |= BIT2; phase ++;} // B ,2 a
		else if ( phase == 2) { P4->OUT |= BIT3; phase ++;} // C ,1 b
		else { P4->OUT |= BIT4; phase =0;} // D ,2 b
		}
		else { // reverse
		if ( phase == 0) { P4->OUT |= BIT4 ; phase ++;} // D ,2 b
		else if ( phase == 1) { P4->OUT |= BIT3; phase ++;} // C ,1 b
		else if ( phase == 2) { P4->OUT |= BIT2; phase ++;} // B ,2 a
		else { P4->OUT |= BIT1; phase =0;} // A ,1 a
		}
		delay (5); // smaller values = faster speed
	}
	
	return 0;
}



