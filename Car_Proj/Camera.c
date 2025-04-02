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

extern BOOLEAN g_sendData;

static char str[100];

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
  int max = 0;
	int min = input[0];
	length -= 4;
	for (int i = 4; i <= length - window; i++) {
        double sum = 0.0;
        for (int j = 0; j < window; j++) {
            sum += input[i + j];
        }
				if (input[i] > max){
					max = input[i];
				}
				if (input[i] < min){
					min = input[i];
				}
        output[i] = sum / window;
    }
	return ((max + min) / 2);
}

/////////////////////////////////////////////////////
//
// main function
//
//
/////////////////////////////////////////////////////
int main(void)
{	
	int i = 0;
	int high_thresh = 15000;
	//initializations
	DisableInterrupts();
	uart0_init();
	uart0_put("\r\nLab5 CAMERA demo\r\n");

	
	uart0_put("\r\nINIT LEDs\r\n");
	LED1_Init();
	LED2_Init();
	servo_init();
	motor_init();
//	OLED_Init();
//	OLED_display_on();
//	OLED_display_clear();
//	OLED_display_on();

	// remember that we double the desired frequency because we need to account for aliasing

	uart0_put("\r\nINIT Camera CLK and SI\r\n");
	uart0_put("\r\nINIT ADC\r\n");	
	INIT_Camera();
	
	uart0_put("\r\nINIT Switch 2\r\n");


	uart0_put("\r\nEnable Interrupts\r\n");
	EnableInterrupts();
	uart0_put("\r\nInterrupts successfully enabled\r\n");
	
	//high_thresh = runningAverage(line, data, sizeof(line), 5);

	while(1)
	{
		int low_max, low_delta = 0;
		int high_max, high_delta = 0;
		runningAverage(line, data, sizeof(line), 5);
		for (int i = 0; i < 64; i++){ //64 marks the next half
			if (data[i] >= high_thresh){
				low_delta++;
			}
			if(data[i + 64] >= high_thresh){
				high_delta++;
			}
		}
		//OLED_DisplayCameraData(data);

		sprintf(str,"%i %i %i\n\r", low_delta, high_delta, high_thresh);
		uart0_put(str);
		forward();		
		
		if (abs(low_delta - high_delta) <= 2){
			servo_2center();
			uart0_put("Center\r\n");
		}
		else if(low_delta > high_delta){
			servo_2left();
			uart0_put("Left\r\n");
		}
		else{
			servo_2right();
			uart0_put("Right\r\n");
		}
		// do a small delay
		myDelay();
	}
	
}
