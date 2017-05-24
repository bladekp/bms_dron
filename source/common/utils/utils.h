#ifndef UTILS_H
#define UTILS_H
#include <avr/io.h>

/* Makra do operacji bitowych */
#define GET_BIT(variable, position) ((variable >> position) & 1)
#define SET_BIT(variable, position, value) (variable ^ ((-value ^ variable) & (1 << position)))

/* Dla celów zmiennych typu logicznego */
#define FALSE 	0
#define TRUE	1

/* Zwraca wybrany bajt liczby 32bitowej.
 * Bajty liczone od najmłodszego.
 * @param val liczba do podzielenia
 * @param k = 0,1,2,3 numer bajtu liczby val
 */
uint8_t nibble32bit(uint32_t val, uint8_t k);

/* Zwraca wybrany bajt liczby 32bitowej.
 * Bajty liczone od najmłodszego.
 * @param val liczba do podzielenia
 * @param k = 0,1 numer bajtu liczby val
 */
uint8_t nibble16bit(uint16_t val, uint8_t k);

#endif
