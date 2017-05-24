/*
 * LTC.h
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */

#ifndef BMS_MEASUREMENT_LTC_H_
#define BMS_MEASUREMENT_LTC_H_

#include <avr/io.h>

/* Rozkazy */
#define WRCFG 	0x01
#define RDCFG	0x02
#define RDCV	0x04
#define STCVAD	0x10

/* Czasy opóźnień */
#define T_CYCLE_12CELL_MES_VOL	15 	//ms
#define T_CYCLE_10CELL_MES_VOL	13 	//ms
#define T_CYCLE_3TEMP_MES		5  	//ms
#define T_CYCLE_1CELL_OR_1TEMP	2	//ms

#define LTC6803_DEVICES_COUNT 1 		/* Ilość urządzeń */

/* Struktura (i definicja typu) przedstawiająca stan jednego urządzenia LTC6803 */
typedef struct{
	uint8_t address;
	uint16_t voltages[12];
} LTC6803;

LTC6803 DEVICES[LTC6803_DEVICES_COUNT];	/* Tablica wszystkich urządzeń */

/* Metoda inicializuje rejestry urządzeń */
void initLTCs();

void readVoltages(LTC6803 devices[]);

void readConfiguration();

void powerOffLTCs();

void powerOnLTCs();

void sleepModeLTCs();

#endif /* BMS_MEASUREMENT_LTC_H_ */
