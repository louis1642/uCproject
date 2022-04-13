/*
 * USART.c
 *
 * Created: 27.3.2022 17.53.29
 *  Author: Luigi Catello
 */ 

#include "USART.h"

uint8_t data;

void USART_init(void) {
	// setting baud rate
	UBRR0 = UBRRVALUE;
	// enabling receiver and RxComplete interrupt
	UCSR0B |= (1 << RXEN0 | 1 << RXCIE0 | 1 << TXEN0);
	// default values for UCSR0C are already good
	// enable global interrupts
	sei();	// should be already enabled!
}

uint8_t USART_read(void) {
	// only when the program asks for the data from the terminal,
	//  the data is provided (instead of every time the terminal receives
	//  a new message)
	return data;
}

void USART_send(uint8_t ch) {
	// wait for the data register to be ready to receive new data
	while ((UCSR0A & (1 << UDRE0)) == 0);
	// write the char in the register
	UDR0 = ch;
}


// handle the interrupt
ISR(USART_RX_vect) {
	// the data sent by the terminal is stored in the variable.
	static uint16_t dataBuffer;
	uint8_t rx = UDR0;
	
	if (rx >= '0' && rx <= '9') {
		// digit
		
		// ASCII digit to number conversion can be obtained
		//  subtracting the ASCII code for '0'
		dataBuffer = 10 * dataBuffer + (rx - '0');
	} else if (rx == '\r' && dataBuffer <= 100) {
		// user pressed enter and the inputted number is less than 100%
		
		// move the data from the dataBuffer
		data = dataBuffer;
		// clean the static buffer for future use
		dataBuffer = 0;
		// send confirmation message
		USART_send('o');
		USART_send('k');
		USART_send('\r');
	} else {
		// something is off
		
		// send error message
		USART_send(' ');
		USART_send('e');
		USART_send('r');
		USART_send('r');
		USART_send('o');
		USART_send('r');
		USART_send('\r');
		// clean the buffer
		dataBuffer = 0;
	}
}