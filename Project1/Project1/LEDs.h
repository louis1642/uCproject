/*
 * LEDs.h
 *
 * Created: 29.3.2022 11.38.11
 *  Author: Luigi Catello
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>

#define LED_GREEN	(1 << PORTD4)
#define LED_RED		(1 << PORTD3)
#define LED_BLUE	(1 << PORTD5)
#define LED_ALL		(LED_GREEN | LED_RED | LED_BLUE)

void LEDs_init(void);
void LEDs_turnOn(uint8_t led);
void LEDs_turnOff(uint8_t led);


#endif /* LEDS_H_ */