/*
 * File:        LED.h
 * Purpose:     Provide LED routines for serial IO
 *
 * Notes:		
 *
 */
#include "Common.h"  // from Lab1 code

#define RED     (BYTE)(0x1) //0001
#define GREEN   (BYTE)(0x2) //0010
#define BLUE    (BYTE)(0x4) //0100
#define CYAN    (BYTE)(0x6) //0000
#define MAGENTA (BYTE)(0x5) //0101
#define YELLOW  (BYTE)(0x3) //0011
#define WHITE   (BYTE)(0x7) //0111

void LED1_Init(void);
	
void LED1_On(void);

void LED1_Off(void);

BOOLEAN LED1_State(void);


void LED2_Init(void);

void LED2_On(int);
	
void LED2_Off(void);

//BOOLEAN LED2_State(void);