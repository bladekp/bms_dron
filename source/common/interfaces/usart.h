/*
 * usart.h
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */

#ifndef COMMON_INTERFACES_USART_H_
#define COMMON_INTERFACES_USART_H_

#define BAUD 57600						/* baud */
#define MYUBRR F_CPU/16/BAUD-1			/* baud for UBRR */

/* Inicjalizuje interfejs USART */
void initUSART();

/* Transmituje dane do urządzenia USART */
void transmit8bitUSART(uint8_t data);
void transmit16bitUSART(uint16_t data);
void transmit32bitUSART(uint32_t data);

/*Pobiera dane z USART */
uint8_t receive8bitUSART();

#endif /* COMMON_INTERFACES_USART_H_ */
