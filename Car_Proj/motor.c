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

void forward(void){
	TIMER_A0_PWM_DutyCycle(0.4, 1);
	TIMER_A0_PWM_DutyCycle(0.4, 3);

}

void reverse(void){
	TIMER_A0_PWM_DutyCycle(0.4, 4);
	TIMER_A0_PWM_DutyCycle(0.4, 2);
}

void motor_init(void){
	TIMER_A0_PWM_Init((20000), 0, 1);
	TIMER_A0_PWM_Init((20000), 0, 4);
		TIMER_A0_PWM_Init((20000), 0, 2);
	TIMER_A0_PWM_Init((20000), 0, 3);
}


