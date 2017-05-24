/*
 * usart.c
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */

#include <avr/io.h>
#include "usart.h"

void initUSART(){
	UBRR0H = (unsigned char)(MYUBRR>>8);	/* set baud */
	UBRR0L = MYUBRR;						/* set baud */
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);		/* enable receiver and transmitter */
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);		/* 8bit data format. 2bit stop */
}

void transmit8bitUSART(uint8_t data){

	while( !(UCSR0A & (1<<UDRE0)) );

	UDR0 = data;
}

//TODO bladekp: impl
void transmit16bitUSART(uint16_t data){}

//TODO bladekp: impl
void transmit32bitUSART(uint32_t data){}

uint8_t receive8bitUSART(){

	while( !(UCSR0A & (1<<RXC0)) );

	return UDR0;
}
