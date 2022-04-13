/*
 * PWM.c
 *
 * Created: 28.3.2022 17.27.01
 *  Author: Luigi Catello
 */ 

#include "PWM.h"


// initialize the PWM on PB1
void PWM_init(void) {
	//OC1A - PB1 output
	DDRB |= 0x2;
	
	//Set Compare Output Mode for channel 1
	TCCR1A |= (1 << COM1A1);
	
	//Table 15-5 of the datasheet
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	// Set PWM frequency/top value
	ICR1 = (FRREQ / (PRESCALER * STROBE_FREQ)) - 1;
	OCR1A = ICR1 * STARTING_DUTY_CYCLE / 100;
	
	PWM_state = 1;
}


// set a new duty cycle for the PWM:
// percent must be in the interval [0;100]
void PWM_setDutyCycle(uint8_t percent) {
	if (percent == 0) {
		PWM_stop();
		return;
	}
	if (percent > 100) {
		percent = 100;
	}
	if (PWM_state == 0)	{
		PWM_start();
	}

	ICR1 = (FRREQ / (PRESCALER * STROBE_FREQ)) - 1;
	OCR1A = ICR1 * percent / 100;

}


// start the counter for the PWM
void PWM_start(void) {
	// PB1 as output
	DDRB |= 0x2;
	//Set Compare Output Mode for channel 1
	TCCR1A |= (1 << COM1A1);
	// timer on
	TCCR1B |= (1 << CS10);
	
	PWM_state = 1;
}


// stop the counter for the PWM
void PWM_stop(void) {
	// unset compare output mode (CH1)
	TCCR1A &= ~(1 << COM1A1);
	// stop counter
	TCCR1B &= ~(1 << CS10);
	// write digital 0 on PB1
	PORTB &= ~0x2;
	
	PWM_state = 0;
}