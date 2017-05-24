/*
 * board.h
 *
 *  Created on: 31.07.2016
 *      Author: bladekp
 */

#ifndef SOURCE_BOARD_H_
#define SOURCE_BOARD_H_

#include <avr/io.h>

/* Interfejsy płyty */
#define ATMEGA_PWR_DOWN_BUTTON	PD2
#define ATMEGA_ON_LED			PC2

/* Czas jaki należy przytrzymać przycisk ATMEGA_PWR_DOWN_BUTTON aby włączyć/wyłączyć BMS <1000:4194> [ms]*/
#define BMS_STARTUP_TIME		2000 //ms

/* Czas jaki należy przytrzymać przycisk ATMEGA_PWR_DOWN_BUTTON aby wyjść ze stanu uśpienia BMS <0:999> [ms]*/
#define BMS_WAKEUP_TIME			200 //ms

/* Czas zwłoki przycisku, tyle trzeba czekać po zwolnieniu przycisku żeby zaczął on reagować ponownie <0:65535> [ms] */
#define CZAS_ZWLOKI_PRZYCISKU	500 //ms

/* Możliwe statusy urządzenia */
#define POWERED_OFF				0
#define SLEEP_MODE				1
#define RUNNING					2

/* Status początkowy urządzenia */
uint8_t DEVICE_STATUS;

/* Inicjalizuje przerwania (timera, oraz przycisku) */
void initInterrupts();

/* Przechodzi w stan wyłączenia (atmega w uśpieniu) */
void enablePoweredOffMode();

/* Przechodzi do stanu uśpienia */
void enableSleepMode();

/* Wychodzi ze stanu uśpienia/wyłączenia i przechodzi do normalnej pracy */
void enbleRunningMode();

#endif /* SOURCE_BOARD_H_ */
