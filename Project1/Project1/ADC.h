/*
 * ADC.h
 *
 * Created: 27.3.2022 16.54.15
 *  Author: Luigi Catello
 *
 * Initialize ADC and read voltage
 *
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_init(void);
void ADC_read(uint8_t channelNo, uint16_t* output);
void ADC_tmpDisable();
void ADC_reenable();

#endif /* ADC_H_ */