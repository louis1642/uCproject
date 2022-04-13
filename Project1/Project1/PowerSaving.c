/*
 * PowerSaving.c
 *
 * Created: 6.4.2022 18.09.54
 *  Author: Luigi Catello
 */ 

#include "PowerSaving.h"

void PowerSaving_init() {
	// Setup interrupts
	// Enable Pin Change Interrupt 18
	PCICR |= (1 << PCIE2);
	// Mask PCINT18
	PCMSK2 |= (1 << PCINT18);
	// enable global interrupt
	sei();
}


void PowerSaving_sleep() {
	// turn off LEDs
	LEDs_turnOff(LED_ALL);

	// disable ADC
	ADC_tmpDisable();
	
	// select Power Down sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// disable interrupt
	cli();
	// set SE bit
	sleep_enable();
	// enable interrupts
	sei();
	// sleep instruction
	sleep_cpu();
	//
	// --> entry point after interrupt
	// reset SE bit
	sleep_disable();
	
	// turn on LEDs like before
	Task_WriteLEDs();
	
	// enable ADC again
	ADC_reenable();
}

ISR(PCINT2_vect){
	// interrupt used to wake up the microcontroller
}