/*
 * Tasks.c
 *
 * Created: 27.3.2022 12.43.18
 *  Author: Luigi Catello
 *
 */

#include "Tasks.h"
uint16_t currentTemperature;

uint16_t abs(int16_t x);

// read On/Off from PD2
void Task_ReadOnOffSw(void) {
	if ((PIND & (1 << PIND2)) == 0) {
		// ON
	} else {
		// OFF
		PowerSaving_sleep();
	}
}


// read Local/External from PC2 (pull-up)
// acquire target temperature from either the potentiometer or the terminal
void Task_ReadTargetTemp(void) {
	if ((PINC & (1 << PINC2)) == 0) {
		// closed switch -> local
		// read target temperature from potentiometer (ADC1)
		ADC_read(1, &targetTemperature);
	} else {
		// open switch -> external
		// read target temperature from terminal
		targetTemperature = (uint16_t) (USART_read() * 10.23);
	}
}


// read current temperature from ADC0, compare with target temperature,
// then turn on/off PWM to warm up/cool down, and update the status (for the LEDs)
void Task_Heat(void) {
	ADC_read(0, &currentTemperature);
	if (abs(targetTemperature - currentTemperature) < 512) {
		if (abs(targetTemperature - currentTemperature) < 128) {
			// OK
			state_heating = 0;
		} else if(currentTemperature > targetTemperature) {
			// COOL DOWN
			state_heating = 2;
		} else {
			// WARM UP
			state_heating = 1;
		}
		PWM_setDutyCycle(targetTemperature);
		
	} else if(currentTemperature > targetTemperature) {
		// COOL DOWN
		PWM_stop();
		state_heating = 2;
		
	} else {
		// WARM UP
		PWM_setDutyCycle(100);
		//PWM_start();
		state_heating = 1;
	}
}


// write the state (heating up / cooling down / temperature ok) on the LEDs
void Task_WriteLEDs(void) {
	switch (state_heating) {
		case 0:
			// temperature ok - green led
			LEDs_turnOff(LED_ALL & ~LED_GREEN);
			LEDs_turnOn(LED_GREEN);
			break;
		case 1:
			// heating up - red led
			LEDs_turnOff(LED_ALL & ~LED_RED);
			LEDs_turnOn(LED_RED);
			break;
		case 2:
			// cooling down - blue led
			LEDs_turnOff(LED_ALL & ~LED_BLUE);
			LEDs_turnOn(LED_BLUE);
			break;
		default:
			// should never happen
			return;
	}
}


uint16_t abs(int16_t x) {
	if (x >= 0) {
		return (uint16_t) x;
	} else {
		return (uint16_t) (-1 * x);
	}
}