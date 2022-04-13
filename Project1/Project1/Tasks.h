/*
 * Tasks.h
 *
 * Created: 27.3.2022 12.43.18
 *  Author: Luigi Catello
 *
 * Tasks to execute
 *
 */

#ifndef TASKS_H_
#define TASKS_H_

#include <avr/io.h>
#include "ADC.h"
#include "USART.h"
#include "PWM.h"
#include "LEDs.h"
#include "PowerSaving.h"

// functions prototypes
void Task_ReadOnOffSw(void);	// read on/off switch
void Task_ReadTargetTemp(void); // read local vs ext, read pot/term
void Task_Heat(void);			// read current temp, compare with target, turn on/off PWM, write state (for LEDs)
void Task_WriteLEDs(void);		// write heater state on the LEDs


// variables
extern uint16_t targetTemperature;
extern uint8_t state_heating;


#endif /* TASKS_H_ */