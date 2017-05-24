/*
 * screen.c
 *
 *  Created on: 04.08.2016
 *      Author: bladekp
 */

#include "../terminal/screen.h"
#include "../bms/measurement/LTC.h"
#include "../common/utils/utils.h"
#include "../common/interfaces/usart.h"

/* Łańcuchy znakowe */
const char STRING_ADDRESS[8] = "ADDRESS0";
const char STRING_CELL[5] = "CELL0";

void printChar(char c){
	transmit8bitUSART(c);
}

void cleanScreen(){
	for(uint16_t i = 0; i<ROWS*COLUMNS; i++) printChar(BACKSPACE);
}

void printLine(){
	printChar(CARRIAGE_RETURN);
	printChar(VERTICAL_TAB);
}

void printString(const char string[]){
	char c;
	uint8_t i = 0;
	while ((c = string[i]) != '0'){
		printChar(c);
		i++;
	}
}

void printDigit(uint8_t d){
	printChar(d + ZERO_ASCII);
}

void printUint16(uint16_t l){
	uint16_t dzielnik = 10000;
	uint8_t przegiecie = FALSE;
	for(uint8_t i = 0; i<5; i++){
		uint8_t x = l/dzielnik;
		l -= x*dzielnik;
		dzielnik /= 10;
		if (x != 0)	przegiecie = TRUE;
		if (przegiecie || i == 4) printDigit(x);
	}
}

void printVoltage(uint16_t vol){
	float miliVolts = (vol - 512) * 1.5;
	printUint16((uint16_t) miliVolts); //TODO bladekp: możemy stracić 0,5 mV, trzeba poprawić
}

void refreshScreen(LTC6803 *devices, uint8_t devices_count){

	/* Czyszczenie ekranu terminala */
	cleanScreen();

 	for(uint8_t i = 0; i<devices_count; i++){ //dla każdego LTC w łańcuchu
 		printString(STRING_ADDRESS);
 		printChar(':');
 		printChar(SPACE);
 		printUint16(devices->address);
 		printLine();
 		for(uint8_t j = 0; j<12; j++){	//dla każdego ogniwa
 			printString(STRING_CELL);
 			printChar(SPACE);
 			printUint16(j+1);
 			printChar(':');
 			printChar(SPACE);
 			printVoltage(devices->voltages[j]);
 			printChar(SPACE);
 			printChar('m');
 			printChar('V');
 			printChar(SPACE);
 			if (j == 3 || j == 7){	// po 4 ogniwa w każdej linii
 				printLine();
 			}
 		}
 	}
}

void consoleLogUint8(uint8_t data){
	printUint16(data);
}

void consoleLogUint16(uint16_t data){
	printUint16(data);
}

void consoleLogChar(char data){
	printChar(data);
}

void consoleLogLine(){
	printLine();
}
