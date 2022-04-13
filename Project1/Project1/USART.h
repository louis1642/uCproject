/*
 * USART.h
 *
 * Created: 27.3.2022 17.49.17
 *  Author: Luigi Catello
 */ 


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUDRATE 9600ul
#define CLKF 16000000ul
#define UBRRVALUE (CLKF/(16ul*BAUDRATE)-1)

void USART_init(void);
uint8_t USART_read(void);
void USART_send(uint8_t ch);


#endif /* USART_H_ */