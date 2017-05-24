/*
 * LTC.c
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */


#include <avr/io.h>
#include <util/delay.h>
#include "../../common/utils/utils.h"
#include "../../common/utils/crc.h"
#include "LTC.h"
#include "../../common/interfaces/spi.h"
#include "../../terminal/screen.h"

void sendBytes(uint8_t bytes[], uint8_t length){
	uint8_t crc = pec8_calc(length, &bytes[0]);

	for (uint8_t i=0; i<length; i++){
		transReceive8b(bytes[i]);

		/*consoleLogUint8(bytes[i]);
		consoleLogChar(SPACE);
		consoleLogUint8(crc);
		consoleLogLine();*/
	}
	transReceive8b(crc);
}

uint8_t receiveByte(){
	return transReceive8b(0x00);
}

void initLTCs(){
	DEVICES[0].address = 0x00;
	for (uint8_t i = 0; i<12; i++){
		DEVICES[0].voltages[i] = 0x00;
	}
	PORTB = SET_BIT(PORTB, 2, 0);
	sendBytes((uint8_t []){WRCFG}, 1);
	sendBytes((uint8_t []){0b10001111, 0b00000000, 0b00000000, 0b11111100, 0b00000000, 0b11111111}, 6);
	PORTB = SET_BIT(PORTB, 2, 1);
}

void readConfiguration(){
	PORTB = SET_BIT(PORTB, 2, 0);
	//sendBytes((uint8_t []){0x80}, 1);
	sendBytes((uint8_t []){RDCFG}, 1);

	for (uint8_t i=0; i<7; i++){
		consoleLogLine();
		consoleLogUint8(receiveByte());
	}
	PORTB = SET_BIT(PORTB, 2, 1);
}

void startConversions(){
	sendBytes((uint8_t []){STCVAD}, 1);
	uint8_t b;
	while ((b = receiveByte()) == 0){}
}

void readVoltages(LTC6803 devices[]){
	PORTB = SET_BIT(PORTB, 2, 0);
	startConversions();
	PORTB = SET_BIT(PORTB, 2, 1);
	_delay_ms(T_CYCLE_12CELL_MES_VOL);
	PORTB = SET_BIT(PORTB, 2, 0);
	sendBytes((uint8_t []){RDCV}, 1);
	for (uint8_t i=0; i<12; i=i+2){
		uint8_t b1 = receiveByte();
		uint8_t b2 = receiveByte();
		uint8_t b3 = receiveByte();
		devices[0].voltages[i] = ((b2 & 0x0F) << 8) + b1;
		devices[0].voltages[i+1] = ((b2 & 0xF0) >> 4) + (b3 << 4);
	}
	uint8_t crc = receiveByte(); //TODO: sprawdzić CRC po transmisji, narazie jebać
	PORTB = SET_BIT(PORTB, 2, 1);
}

void powerOffLTCs(){

}

void powerOnLTCs(){

}

void sleepModeLTCs(){

}
