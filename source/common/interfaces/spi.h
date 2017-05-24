/*
 * spi.h
 *
 *  Created on: 30.07.2016
 *      Author: bladekp
 */

#ifndef SOURCE_COMMON_INTERFACES_SPI_H_
#define SOURCE_COMMON_INTERFACES_SPI_H_

/* Inicjalizuje SPI */
void initSPI();

/* Transmituje  i odbiera dane z SPI */
uint8_t transReceive8b(uint8_t x);

#endif /* SOURCE_COMMON_INTERFACES_SPI_H_ */
