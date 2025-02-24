/*
 * File:        Switches.c
 * Purpose:     Provide routines for switch configuration and use
 *
 * Notes:		
 *
 */

#include "msp.h" 
#include "Switches.h"
#include "Common.h"

void Switch1_Init(void)
{
	// configure PortPin for Switch 1 as port I/O 
	P1 -> SEL0 &= ~BIT1;
	P1 -> SEL1 &= ~BIT1;
	
	// configure as input
	P1 -> DIR &= ~BIT1;
	
	P1 -> REN |= BIT1;
	
	P1 -> OUT |= BIT1;
              
	// configure for interrupt
	// interrupt on falling edge
	P1 -> IES |= BIT1;
	
	// interrupt enable
	P1 -> IE |= BIT1;
	
	// interrupt flag (clear)
	P1 -> IFG &= ~BIT1;
	
	//NOTE: the three above lines are also used in Lab5-Timer, Switch1_Interrupt_Init()
	
}

void Switch2_Init(void)
{
	// configure PortPin for Switch 2 as port I/O 
	P1 -> SEL0 &= ~BIT4;
	P1 -> SEL1 &= ~BIT4;
	
	// configure as input
	P1 -> DIR &= ~BIT4;
	
	P1 -> REN |= BIT4;
	
	P1 -> OUT |= BIT4;
              
	// configure for interrupt
	// interrupt on falling edge
	P1 -> IES |= BIT4;
	
	// interrupt enable
	P1 -> IE |= BIT4;	
	
	// interrupt flag (clear)
	P1 -> IFG &= ~BIT4;	
	
	//NOTE: the three above lines are also used in Lab5-Timer, Switch2_Interrupt_Init()
	
}

//------------Switch_Input------------
// Read and return the status of Switch1
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch1_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	if(!(P1IN & BIT1)){
		retVal = TRUE;
	}
	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}

//------------Switch_Input------------
// Read and return the status of Switch2
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch2_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	if(!(P1IN & BIT4)){
		retVal = TRUE;
	}	
	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}