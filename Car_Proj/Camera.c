/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "leds.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
#include "ControlPins.h"
#include "ServoMotor.h"
#include "TimerA.h"
#include "motor.h"
#include "oled.h"
#include "switches.h"



///////////////////////////////////////////////////////
//
// NOTE: For the camera, you may want to change the default
//       clock to 48MHz
//
// To do that: Edit system_msp432p401r.c
//             Change:   #define  __SYSTEM_CLOCK    3000000
//             To:       #define  __SYSTEM_CLOCK    48000000 
// ADC will be P4.7 A6
//
// SI Pin will be P5.5 A0
//
// CLK Pin will be P5.4 A1//
//

// line stores the current array of camera data
extern uint16_t line[128];
uint16_t data[128];
float straightSpeed = 0.5;
float fastWheel = 0.5;
float slowWheel = 0.25;
		
extern BOOLEAN g_sendData;

//static char str[100];

BOOLEAN SW1 = FALSE;
BOOLEAN SW2 = FALSE;
// ADC_In() gets the latest value from the ADC
// ADC will be P4.7 A6

// SI Pin will be P5.5 A0

// CLK Pin will be P5.4 A1

// main


/////////////////////////////////////////////////////
//
// simple delay function
//
//
/////////////////////////////////////////////////////
void myDelay(void)
{
	volatile int j = 0;
	for (j = 0; j < 80000; j++)
	{
		;
	}
}
/////////////////////////////////////////////////////
//
// INIT_Camera function
//
//
/////////////////////////////////////////////////////
void INIT_Camera(void)
{
	g_sendData = FALSE;
	ControlPin_SI_Init();
	ControlPin_CLK_Init();
	ADC0_InitSWTriggerCh6();
}

int runningAverage(const uint16_t *input, uint16_t *output, int length, int window) {
  uint16_t max = 0;
	for (int i = 0; i < length; i++) {
//        double sum = 0.0;
//        for (int j = 0; j < window; j++) {
//            sum += input[i + j];
//        }
				if (input[i] > max){
					max = input[i];
				}
//        output[i] = sum / window;
    }
//		sprintf(str, "max: %i min: %i\n\r", max, min);
//		uart2_put(str);
	return (max * 0.7);
}

//

//  I/O interrupt pin setup
//
// DIR     SEL0/SEL1    IE    IES     Port Mode
//  0          00        0     0       Input, rising edge trigger
//  0          00        0     1       Input, falling edge trigger, interrupt
//  0          00        1     0       Input, rising edge trigger, interrupt
//  0          00        1     1       Input, falling edge trigger, interrupt
//

void Switch1_Interrupt_Init(void)
{
	// disable interrupts
	DisableInterrupts();
	// initialize the Switch as per previous lab
	Switch1_Init();
	
 
	
	//7-0 PxIFG RW 0h Port X interrupt flag
	//0b = No interrupt is pending.
	//1b = Interrupt is pending.
	// clear flag1 (reduce possibility of extra interrupt)	
  P1 -> IFG &= ~BIT1; 

	//7-0 PxIE RW 0h Port X interrupt enable
	//0b = Corresponding port interrupt disabled
	//1b = Corresponding port interrupt enabled	
	// arm interrupt on  P1.1	
  P1 -> IE |= BIT1;  

	//7-0 PxIES RW Undefined Port X interrupt edge select
  //0b = PxIFG flag is set with a low-to-high transition.
  //1b = PxIFG flag is set with a high-to-low transition
	// now set the pin to cause falling edge interrupt event
	// P1.1 is falling edge event
  P1 -> IES |= BIT1; 
	
	// now set the pin to cause falling edge interrupt event
  NVIC_IPR8 = (NVIC_IPR8 & 0x00FFFFFF)|0x40000000; // priority 2
	
	// enable Port 1 - interrupt 35 in NVIC	
  NVIC_ISER1 = 0x00000008;  
	
	// enable interrupts  (// clear the I bit	)
  EnableInterrupts();              
	
}
void Switch2_Interrupt_Init(void)
{
	// disable interrupts
	DisableInterrupts();
	
	// initialize the Switch as per previous lab
	Switch2_Init();
	
	// now set the pin to cause falling edge interrupt event
	// P1.4 is falling edge event
  P1 -> IES |= BIT4;
  
	// clear flag4 (reduce possibility of extra interrupt)
  P1 -> IFG &= ~BIT4; 
  
	// arm interrupt on P1.4 
  P1 -> IE |= BIT4;     
	
	// now set the pin to cause falling edge interrupt event
  NVIC_IPR8 = (NVIC_IPR8&0x00FFFFFF)|0x40000000; // priority 2
	
	// enable Port 1 - interrupt 35 in NVIC
  NVIC_ISER1 = 0x00000008;         
	
	// enable interrupts  (// clear the I bit	)
  EnableInterrupts();              
	
}
// PORT 1 IRQ Handler
// LJBeato
// Will be triggered if any pin on the port causes interrupt
//
// Derived From: Jonathan Valvano


void PORT1_IRQHandler(void)
{
	// First we check if it came from Switch1 ?
  if(P1->IFG & BIT1)
	{
		// Switch 1 Pressed
		
		// acknowledge P1.1 is pressed, by setting BIT1 to zero - remember P1.1 is switch 1
		// clear flag, acknowledge
		//uart0_put("\r\nIRQ Handler SW 1\r\n");
		
    P1 -> IFG &= ~BIT1;
		straightSpeed = 0.5;
		fastWheel = 0.4;
		slowWheel = 0.4;
	}
	// Now check to see if it came from Switch2 ?
  if(P1->IFG & BIT4)
	{ 
		P1 -> IFG &= ~BIT4;     // clear flag4, acknowledge
		straightSpeed = 0.5;
		fastWheel = 0.5;
		slowWheel = 0.2;
		
  }
	
}

/////////////////////////////////////////////////////
//
// main function
//
//
/////////////////////////////////////////////////////
int main(void)
{	
	uint16_t high_thresh = 0;
	//initializations
	DisableInterrupts();
	uart0_init();
  uart2_init();
	uart0_put("\r\nLab5 CAMERA demo\r\n");
  uart2_put("BLuetooth test");
	
	uart0_put("\r\nINIT LEDs\r\n");
	LED1_Init();
	LED2_Init();
	servo_init();
	motor_init();
	Switch1_Init();
	Switch2_Init();
	Switch1_Interrupt_Init();
	Switch2_Interrupt_Init();
//	OLED_Init();
//	OLED_display_on();
//	OLED_display_clear();
//	OLED_display_on();

	uart0_put("\r\nINIT Camera CLK and SI\r\n");
	uart0_put("\r\nINIT ADC\r\n");	
	INIT_Camera();
	
	uart0_put("\r\nINIT Switch 2\r\n");


	uart0_put("\r\nEnable Interrupts\r\n");
	EnableInterrupts();
	uart0_put("\r\nInterrupts successfully enabled\r\n");
	
	high_thresh = runningAverage(line, data, 128, 5);
	
	while(1)
	{
		int error = 0, num_white = 0, middle = 0;
		uint16_t pos[128];

		for (int i=0; i < 128; i++){
			if (line[i] >= high_thresh){
				pos[num_white] = i;
				num_white += 1;
			}
		}
		if (num_white == 0){
			SW1 = FALSE;
			Toggle_Motor(TRUE);
		} else SW1 = TRUE;
		middle = num_white / 2;
		error = 64 - pos[middle];
		
		static float Kp = 0.00046; //, Ki = 0.0000, Kd = 0.000;
	//	static float errInt = 0, errOld = 0;
//		float dt = 0.007; // approx loop time

		if (SW1) {
				float err = (float)error;
				//errInt += err * dt;

				//float derr = (err - errOld) / dt;
				float control = Kp * err;// + Kd * derr; //+ Ki * errInt

				float pwm = 0.075f + control*1.1;  // 0.075 is center

				servo_turn(pwm);  // update PWM output
//				errOld = err;

				if (pwm > 0.09 ){ //left
					TIMER_A0_PWM_DutyCycle(fastWheel, 2);
					TIMER_A0_PWM_DutyCycle(slowWheel, 4);
				}
				else if (pwm < 0.06){
					TIMER_A0_PWM_DutyCycle(slowWheel, 2);
					TIMER_A0_PWM_DutyCycle(fastWheel, 4);
				}
				else{
					// drive motors straight
					TIMER_A0_PWM_DutyCycle(straightSpeed, 2);
					TIMER_A0_PWM_DutyCycle(straightSpeed, 4);
				}

			}
//				OLED_DisplayCameraData(line);

				// do a small delay
				//myDelay(); //change implemention to make servo respond faster
			}
		}
