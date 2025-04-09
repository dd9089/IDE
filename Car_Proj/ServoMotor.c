// ServoMotor.c

/*  Noah Bhuiya
    Diego Diaz
    2025
    Servo Motor functionality for steering
 */
#include "msp.h"
#include "uart.h"
#include "TimerA.h"


void servo_init(void){
		// Print welcome over serial
	uart0_put("Running... \n\r");
	
	//Part 1 - UNCOMMENT THIS
	// Generate 20% duty cycle at 10kHz
	TIMER_A2_PWM_Init((800), 0.075, 1); //maybe change this to make servo respond faster?
}

void servo_2right(void){
	TIMER_A2_PWM_DutyCycle(0.05, 1);
}

void servo_2left(void){
	TIMER_A2_PWM_DutyCycle(0.1, 1);
}

void servo_2center(void){
	TIMER_A2_PWM_DutyCycle(0.075, 1);
}
