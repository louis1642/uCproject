/*
 * PowerSaving.h
 *
 * Created: 6.4.2022 18.09.29
 *  Author: Luigi Catello
 */ 


#ifndef POWERSAVING_H_
#define POWERSAVING_H_

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "LEDs.h"

extern void Task_WriteLEDs();	// this function is defined in Tasks.h
extern void ADC_tmpDisable();	// defined in ADC.h
extern void ADC_reenable();		// defined in ADC.h

void PowerSaving_init();
void PowerSaving_sleep();


#endif /* POWERSAVING_H_ */