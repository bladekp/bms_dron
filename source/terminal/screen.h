/*
 * screen.h
 *
 *  Created on: 04.08.2016
 *      Author: bladekp
 */

#ifndef SOURCE_TERMINAL_SCREEN_H_
#define SOURCE_TERMINAL_SCREEN_H_

#include "../bms/measurement/LTC.h"

/* Parametry ekranu */
#define ROWS			25
#define COLUMNS			80


/* Użyteczne kody ASCII */
#define BACKSPACE		0x08
#define HORIZONTAL_TAB	0x09
#define VERTICAL_TAB    0x0B
#define CARRIAGE_RETURN 0x0D
#define SPACE			0x20
#define ZERO_ASCII		0x30

void refreshScreen(LTC6803 *devices, uint8_t devices_count);

void consoleLogUint8(uint8_t data);

void consoleLogUint16(uint16_t data);

void consoleLogChar(char data);

void consoleLogLine();

#endif /* SOURCE_TERMINAL_SCREEN_H_ */
