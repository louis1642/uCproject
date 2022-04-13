/*
 * PWM.h
 *
 * Created: 28.3.2022 17.18.40
 *  Author: Luigi Catello
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

#define PRESCALER 1				// timer prescaler
#define STROBE_FREQ 250000		// this is the frequency of the wave we are going to generate
#define STARTING_DUTY_CYCLE 1	// duty cycle of the wave
#define FRREQ 16000000			// CPU frequency

static uint8_t PWM_state;

void PWM_init(void);
void PWM_setDutyCycle(uint8_t percent);
void PWM_start(void);
void PWM_stop(void);



#endif /* PWM_H_ */