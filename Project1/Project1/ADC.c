/*
 * ADC.c
 *
 * Created: 27.3.2022 17.06.00
 *  Author: Luigi Catello
 */ 

#include "ADC.h"

void ADC_init(void) {
	// since we will only use ADC0 and ADC1,
	//  we will set all bits [1:0] in Digital Input Disable Register 0 to 1
	DIDR0 = 0x03;
	// minimize power consumption setting PORTC[1:0] to 1 -> 0b00000011 = 0x03
	//PORTC |= 0x03;
	// reference voltage to AVcc (REFS[1:0] = 0b01)
	ADMUX |= (1 << REFS0);
	// setting the prescaler to get an AD-clock of around 125kHz
	//  16MHz / 125kHz ~= 128
	//  ADPS[2:0] = 0b111
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// result is right-aligned by default
	// resetting power reduction ADC
	PRR &= ~(1 << PRADC);
	// ADC enable
	ADCSRA |= (1 << ADEN);
}


void ADC_read(uint8_t channelNo, uint16_t* output) {
	// reset the multiplexer
	ADMUX &= ~0x0f;
	
	// select the channel (only channels 1 and 2 are initialized)
	if (channelNo >= 2) {
		return;
	}
	ADMUX |= channelNo;
	
	// start conversion
	ADCSRA |= (1 << ADSC);
	
	// polling: wait for the conversion to end
	while (ADCSRA & (1 << ADSC));
	
	// read the result
	*output = ADC;
	
}

void ADC_tmpDisable() {
	ADCSRA &= ~(1 << ADEN);
}

void ADC_reenable() {
	ADCSRA |= (1 << ADEN);
}