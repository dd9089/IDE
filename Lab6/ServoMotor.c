// ServoMotor.c

/*  Noah Bhuiya
    Diego Diaz
    2025
    Servo Motor functionality??
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
	// INSERT CODE HERE
	uart0_init();
	
	// Print welcome over serial
	uart0_put("Running... \n\r");
	
	//Part 1 - UNCOMMENT THIS
	// Generate 20% duty cycle at 10kHz
	TIMER_A2_PWM_Init((800), 0.075, 1);
	
	
	for(;;)  //loop forever
	{		
		uart0_put("Turning Clockwise\n\r");
		TIMER_A2_PWM_DutyCycle(0.05, 1);
		delay(100);
		TIMER_A2_PWM_DutyCycle(0.075, 1);
		delay(300);
		uart0_put("Turning Counter Clockwise\n\r");
		TIMER_A2_PWM_DutyCycle(0.1, 1);
		delay(100);
		TIMER_A2_PWM_DutyCycle(0.075, 1);
		delay(300);
	}
	
	return 0;
}
