/*
 * crc.h
 *
 *  Created on: 04.08.2016
 *      Author: bladekp
 */

#ifndef SOURCE_COMMON_UTILS_CRC_H_
#define SOURCE_COMMON_UTILS_CRC_H_

/* Wielomian do CRC */
#define PEC_POLY 	7

/* liczy kod CRC do zastosowań transmisji SPI z LTC */
uint8_t pec8_calc(uint8_t len, uint8_t *data);

#endif /* SOURCE_COMMON_UTILS_CRC_H_ */
