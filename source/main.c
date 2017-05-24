/*
 * main.c
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */

#include <avr/io.h>
#include <util/delay.h>
#include "board.h"
#include "common/interfaces/spi.h"
#include "common/interfaces/i2c.h"
#include "common/interfaces/usart.h"
#include "bms/measurement/LTC.h"
#include "bms/measurement/current.h"
#include "bms/measurement/temperature.h"
#include "controller/controller.h"
#include "charger/charger.h"
#include "common/utils/utils.h"
#include "terminal/screen.h"
#include "common/utils/utils.h"

//uint16_t odswiezaniePrzyciskuSleepMode;

int main(void){
	/* inicjalizacja przerwań */
 	//initInterrupts();

 	/* inicjalizacja interfejsów */
 	initSPI();
 	initUSART();
 	//initI2C();

 	/* inicjalizacja urządzeń */
 	initLTCs();
 	//initADConverter();
 	//initTemperatureMaesurement();
 	//initControllerComunication();
 	//initChargerComunication();

 	/* Po podaniu zasilania i inicjalizacji peryferiów, wchodzimy w stan uśpienia */
 	//enablePoweredOffMode();

 	while(1){
 		//readConfiguration();
 		readVoltages(DEVICES);
 		refreshScreen(DEVICES, LTC6803_DEVICES_COUNT);
 		_delay_ms(2000);
 		//if (DEVICE_STATUS == POWERED_OFF){

 		//} else if (DEVICE_STATUS == SLEEP_MODE){
 			/*if(odswiezaniePrzyciskuSleepMode == 0xFFFF){
 				odswiezaniePrzyciskuSleepMode = 0;
 				PORTC = SET_BIT(PORTC, ATMEGA_ON_LED, ~GET_BIT(PORTC, ATMEGA_ON_LED));
 			}
 			odswiezaniePrzyciskuSleepMode = odswiezaniePrzyciskuSleepMode +1;*/
 		//} else if (DEVICE_STATUS == RUNNING){
 			/* Odświeżam ekran konsoli debugera */
 			 			 		//refreshScreen(DEVICES, LTC6803_DEVICES_COUNT);

 			 			 		/* Czytamy voltaż */

 			 			 		/* Czytamy temperatury */

 			 			 		/* Czytamy prąd */

 			 			 		/* Czy parametry są w normie (UNDERVOLTAGE, OVERVOLTAGE ...) */
 			 			 			/* Jeżeli nie, powiadom kontroler */
 			 			 			/* Jeżeli tak, włącz wszystkie napędy */

 			 			 		/* Czy jesteśmy w trybie ładowania, voltaż jest powyżej 4V i różnica potencjałów ogniw przekracza BALANCE_THRESHOLD */
 			 			 			/* Jeżeli tak, włącz balansowanie */



 			 			 		/* Obliczenie parametrów statystycznych akumulatora (SOC, SOH ...) */

 			 			 		/* Komunikacja z kontrolerem (to w wektorze przerwania z USART) */

 			 			 		/* Obsługa ładowarki (w wektorze przerwania USART) */

 			 			 		//readConfiguration();
 		//}
 	}

 	return 0;
 }
