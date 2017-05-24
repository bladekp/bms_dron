/*
 * bms.c
 *
 *  Created on: 31.07.2016
 *      Author: bladekp
 */

#include "board.h"
#include "charger/charger.h"
#include "controller/controller.h"
#include "bms/measurement/current.h"
#include "bms/measurement/temperature.h"
#include "bms/measurement/LTC.h"
#include "common/utils/utils.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

#include "common/utils/utils.h"
#include "terminal/screen.h"

/* ----------------- ZMIENNE GLOBALNE ---------------------------*/

/* Flaga aktywności przycisku */
uint8_t BUTTON_DISABLED = FALSE;

/* ----------------- FUNKCJE PRYWATNE ---------------------------*/

void initTimer(void){
	TIMSK1 |=(1<<TOIE1); //włączenie timera 1
}

/*zamienia czas na ms - uwaga, nie jest dokładne, dodatkowo przydałaby się zależność od FOSC */
uint16_t convertTimeForTimer(uint16_t czas){
	return 0xFFFF - (czas*16);
}

void startTimer(uint16_t czas){
	TCCR1B |=(1<<CS12)|(1<<CS10); // preskaler na 1024
	TCNT1 = convertTimeForTimer(czas);
}

void stopTimer(){
	TCCR1B = SET_BIT(TCCR1B, CS12, 0); // czyścimy preskaler (wyłączamy timer)
	TCCR1B = SET_BIT(TCCR1B, CS10, 0);

	BUTTON_DISABLED = FALSE;
}

void powerOnBoard(){
	PORTC = SET_BIT(PORTC, ATMEGA_ON_LED, 1);
}

void powerOffBoard(){
	PORTC = SET_BIT(PORTC, ATMEGA_ON_LED, 0);
}

void sleepModeBoard(){
}

void enablePoweredOffMode(){
	DEVICE_STATUS = POWERED_OFF;

	powerOffCharger();
	powerOffTemperatureMeasurement();
	powerOffADConverter();
	powerOffLTCs();
	powerOffController();
}

void enableSleepMode(){
	DEVICE_STATUS = SLEEP_MODE;

	sleepModeCharger();
	sleepModeTemperatureMeasurement();
	sleepModeADConverter();
	sleepModeLTCs();
	sleepModeController();

	/* Przejdź w stan uśpienia, wyłącz LTC,
	 			 * odłącz przekaźnik kontrolera i napędów
	 			 * przetwornik AD na płycie mocy do tryby STANDBY*/
}

void enableRunningMode(){
	DEVICE_STATUS = RUNNING;

	powerOnBoard();
	powerOnController();
	powerOnLTCs();
	powerOnADConverter();
	powerOnTemperatureMeasurement();
	powerOnCharger();

	/*inicjalizacja i2c oraz AD do pomiaru prądu */
	/* po włączeniu przycisku */

			//0. Init ltc, komunikacja, sprawdzenie ...

			//1.WŁĄCZ DIODĘ ATMEGA_ON_LED

			//2.ZASILENIE UKŁADU LTC (OTWARCIE TRANZYSTORA Q_LTC

			//3.ZAMKNIĘCIE PRZEKAŹNIKA PŁYTY MOCY I ZASILENIE KONTROLERA (PD7 - Coil On/Off)(PD6 - STM On/Off)

	 	/* Inicjalizacja urządzeń  i interfejsów */
}

void zmienStan(uint32_t time){

	/* 							MACIERZ PRZEJŚĆ 							*/
	/*
	 * 							                   STAN POPRZEDNI
	 * 		_______________________	POWERED_OFF_____SLEEP_MODE_____RUNNING____
	 * 		|					|				 |				|
	 * 		|BMS_WAKEUP_TIME	|		-		 |	  RUNNING	|  SLEEP_MODE
	 * CZAS	|___________________|________________|______________|_____________
	 * 		|					| 				 |				|
	 * 		|BMS_STARTUP_TIME	|	RUNNING		 |	POWERED_OFF	|  POWERED_OFF
	 *		|					| 				 |				|
	 */

	/* BMS_STARTUP_TIME */
	if (time == 0){
		if (DEVICE_STATUS == POWERED_OFF){
				enableRunningMode();
		} else if (DEVICE_STATUS == SLEEP_MODE){
				enablePoweredOffMode();
		} else if (DEVICE_STATUS == RUNNING){
				enablePoweredOffMode();
		} else {
				//TODO bladekp: stan niedozwolony, trzeba obsłużyć.
		}
	} else if (time < BMS_STARTUP_TIME - BMS_WAKEUP_TIME){ /* BMS_WAKEUP_TIME */
		if (DEVICE_STATUS == POWERED_OFF){
				//TODO bladekp: prawdopodobnie jest to stan niedozwolony, trzeba obsłużyć.
		} else if (DEVICE_STATUS == SLEEP_MODE){
				enableRunningMode();
		} else if (DEVICE_STATUS == RUNNING){
				enableSleepMode();
		} else {
				//TODO bladekp: stan niedozwolony, trzeba obsłużyć.
		}
	}

	/* Żaden z przypadków nie satysfakcjonuje macierzy przejść, nie zmieniamy nic */
}

/* Obsługa przerwania przycisku ATMEGA_PWR_DOWN_BUTTON */
ISR(INT0_vect){
	/* Jeżeli przycisk nie jest aktywny nie reaguj */
	if (BUTTON_DISABLED) return;
	BUTTON_DISABLED = TRUE;
	EIFR = SET_BIT(EIFR, 1, 1);
	uint32_t bootstrap_time = BMS_STARTUP_TIME;

	while(bootstrap_time > 0){
		if (GET_BIT(EIFR, 0) == 1) break;
		_delay_us(1000);
		bootstrap_time--;
	}

	/* ustawiamy zwłokę przycisku */
	startTimer(CZAS_ZWLOKI_PRZYCISKU);

	zmienStan(bootstrap_time);

	return;
}

/*Zegar, nie pozwala zbyt często wciskać przycisku */
ISR(TIMER1_OVF_vect){
	stopTimer();
}

void initInterrupts(){
	/* ATmega LED pin as output */
	DDRC |= (1<<ATMEGA_ON_LED);

	/* ATmega button pin as input */
	DDRD &= ~(1<<ATMEGA_PWR_DOWN_BUTTON);
	// turn On the Pull-up
	//PORTD |= (1 << ATMEGA_PWR_DOWN_BUTTON);

	// The falling edge of INT0 generates an interrupt request.
	EICRA |= (1 << ISC00);

	EIMSK |= (1 << INT0);     // Turns on INT0

	/* enable global interrupts */
	sei();

	initTimer();
}
