/*
 * spi.c
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */
#include <avr/io.h>


void initSPI(){
	// set MOSI, SCK, SS as outputs
	DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2);

	// set MISO as input
	DDRB &= ~(1<<PB4);

    //  Enable SPI, Set as Master, Prescaler: Fosc/128 = 125kHz -> SPR1 = 1 i SPR0 = 1; Fosc/16 = 1MHz -> SPR1 = 0 i SPR0 = 1; //LTC6803 max = 1MHz
    SPCR |= (1<<SPE) | (1<<MSTR) | (1 << CPHA) | (1<<CPOL) | (1<<SPR1) | (1<<SPR0);

    // high on SS
    PORTB |= (1<<PB2);
}

uint8_t transReceive8b(uint8_t data){
	SPDR = data;
	while(!((SPSR)&(1<<SPIF)));
	data = (SPDR);
	return data;
}
