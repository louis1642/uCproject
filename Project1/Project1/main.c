/*
 * Project1.c
 *
 * Created: 27.3.2022 12.43.18
 *  Author: Luigi Catello
 *
 * Clock: 16MHz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TaskMgr.h"
#include "Tasks.h"


// GLOBAL VARIABLES
uint16_t targetTemperature;
uint8_t state_heating;	// ok: 0; warming up: 1; cooling down: 2



void LocalRemoteSwitch_init();


int main(void) {
	// initialize components
	TM_init();
	PWM_init();
	USART_init();
	ADC_init();
	PowerSaving_init();
	LEDs_init();
	LocalRemoteSwitch_init();
	
	// send hello message
	USART_send('S');
	USART_send('e');
	USART_send('t');
	USART_send('u');
	USART_send('p');
	USART_send(' ');
	USART_send('c');
	USART_send('o');
	USART_send('m');
	USART_send('p');
	USART_send('l');
	USART_send('e');
	USART_send('t');
	USART_send('e');
	USART_send('d');
	USART_send('\r');
	
	// add tasks to the TaskMgr
	TM_add_task(Task_ReadOnOffSw, 0, 200);
	TM_add_task(Task_ReadTargetTemp, 10, 50);
	TM_add_task(Task_Heat, 20, 15);
	TM_add_task(Task_WriteLEDs, 100, 200);
	
	// main loop: execute the tasks when they are ready
	while (1) {
		TM_dispatcher();
	}
}


void LocalRemoteSwitch_init() {
	// set PC2 to pull-up mode
	PORTC |= (1 << PORTC2);
}