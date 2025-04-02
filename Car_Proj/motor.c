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

//2.5 and 2.7 in car tester
void forward(void){

		TIMER_A0_PWM_DutyCycle(0.25, 2); //2.5 left motor
		TIMER_A0_PWM_DutyCycle(0.25, 4); //2.7 right motor

}

void reverse(void){
	TIMER_A0_PWM_DutyCycle(0.4, 1);
	TIMER_A0_PWM_DutyCycle(0.4, 3);
}

void motor_init(void){
	P3 -> SEL0 &= ~BIT6;
	P3 -> SEL1 &= ~BIT6;
	P3 -> SEL0 &= ~BIT7;
	P3 -> SEL1 &= ~BIT7;


	// make built-in motor out	 
	P3 -> DIR |= BIT6;
	P3 -> DIR |= BIT7;

	// turn on LED
	P3 -> OUT |= BIT6;
	P3 -> OUT |= BIT7;

	TIMER_A0_PWM_Init((20000), 0, 1);
	TIMER_A0_PWM_Init((20000), 0, 4);
	TIMER_A0_PWM_Init((20000), 0, 2);
	TIMER_A0_PWM_Init((20000), 0, 3);
}
