/*
 * File:        LED.c
 * Purpose:     Provide LED routines for serial IO
 *
 * Notes:		
 *
 */

#include "msp.h"
#include "uart.h"  // you need to create this file with the function prototypes
#include "Common.h"  // from Lab1 code

//LED1 (RED)
void LED1_Init(void)
{
	// configure PortPin for LED1 as port I/O 
	P1 -> SEL0 &= ~BIT0;
	P1 -> SEL1 &= ~BIT0;

	// make built-in LED1 LED high drive strength
	P1 -> DS |= BIT0;

	// make built-in LED1 out	 
	P1 -> DIR |= BIT0;

	// turn off LED
	P1 -> OUT &= ~BIT0;
	
}

void LED1_On(void)
{
	P1 -> OUT |= BIT0;
}

void LED1_Off(void)
{
	P1 -> OUT &= ~BIT0;
}

BOOLEAN LED1_State(){
	return (P1 -> OUT & BIT0);
}
//LED2 (RGB)
void LED2_Init(void)
{
	// configure PortPin for LED2 as port I/O 
	P2 -> SEL0 &= ~BIT0;
	P2 -> SEL1 &= ~BIT0;
	
	P2 -> SEL0 &= ~BIT1;
	P2 -> SEL1 &= ~BIT1;
	
	P2 -> SEL0 &= ~BIT2;
	P2 -> SEL1 &= ~BIT2;

	// make built-in LED2 LEDs high drive strength
	P2 -> DS |= BIT0;
	P2 -> DS |= BIT1;
	P2 -> DS |= BIT2;

	// make built-in LED2 out	 
	P2 -> DIR |= BIT0;
	P2 -> DIR |= BIT1;
	P2 -> DIR |= BIT2;

	// turn off LED
	P2 -> OUT &= ~BIT0;
	P2 -> OUT &= ~BIT1;
	P2 -> OUT &= ~BIT2;
 
}

void LED2_Off(void){
		//LED RED OFF
		P2 -> OUT &= ~BIT0;
		//LED BLUE OFF
		P2 -> OUT &= ~BIT1;
		//LED GREEN OFF
		P2 -> OUT &= ~BIT2;
}

void LED2_On(int col){
	
	// col = 0 -> LED Off
	if (col == 0){
		//LED RED OFF
		P2 -> OUT &= ~BIT0;
		//LED BLUE OFF
		P2 -> OUT &= ~BIT1;
		//LED GREEN OFF
		P2 -> OUT &= ~BIT2;
	}
	
	// col = 1 -> LED Red
	else if (col == 1){
		//LED OFF
		LED2_Off();
		//LED RED ON
		P2 -> OUT |= BIT0;
	}
	
	// col = 2 -> LED Blue
	else if (col == 2){
		//LED OFF
		LED2_Off();
		//LED BLUE ON
		P2 -> OUT |= BIT2;
	}
	
	// col = 3 -> LED Green
	else if (col == 3){
		//LED OFF
		LED2_Off();
		//LED GREEN ON
		P2 -> OUT |= BIT1;
	}
	
}

BOOLEAN LED2_State(){
	return FALSE;
}
	