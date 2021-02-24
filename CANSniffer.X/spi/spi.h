/*
    PIC18F2550 SPI Driver
    BDeliers
    15/02/2021 
*/

#ifndef SPI_H
#define	SPI_H

// Standard includes
#include <xc.h>

// Variables includes
#include "../config.h"

uint8_t flush;

// Initializes SPI as master, Fosc/16 = 3MHz, mode (0,0)
void spiMasterInit(void);

void spiWriteByte(uint8_t data);

void spiReadByte(uint8_t *buff);

void spiWriteBuffer(uint8_t* buff, uint8_t nBytes);

void spiReadBuffer(uint8_t* buff, uint8_t nBytes);

#endif	/* SPI_H */
