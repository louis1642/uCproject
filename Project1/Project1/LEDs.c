/*
 * LEDs.c
 *
 * Created: 29.3.2022 11.45.37
 *  Author: Luigi Catello
 */ 

#include "LEDs.h"


// initialize the LEDs pins as digital output
void LEDs_init(void) {
	// configure the pins as digital outputs
	DDRD |= LED_ALL;
}


// turn on the LED
void LEDs_turnOn(uint8_t led) {
	PORTD |= led;
}


// turn off the LED
void LEDs_turnOff(uint8_t led) {
	PORTD &= ~led;
}
