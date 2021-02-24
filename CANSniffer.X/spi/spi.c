#include "spi.h"

void spiMasterInit(void) {
    // Reset MSSP
    SSPSTAT = 0;
    SSPCON1 = 0;
    
    // Mode (0,0)    
    SSPSTATbits.CKE = 1;
    SSPCON1bits.CKP = 0;
    
    // SPI master mode @Fosc/16 = 9MHz
    SSPCON1bits.SSPM = 0b0010;
    
    // Enable MSSP
    SSPCON1bits.SSPEN = 1;
}

void spiWriteByte(uint8_t data) {
    // Clear interrupt flag
    PIR1bits.SSPIF = 0;
    
    // Flush buffer
    flush = SSPBUF;
    // Write data
    SSPBUF = data;
    
    // Wait end of transmission
    while (!PIR1bits.SSPIF);
}

void spiReadByte(uint8_t *buff) {
    // Send dummy to start clock
    SSPBUF = 0xFF;
    
    // Wait for data
    while (!SSPSTATbits.BF);
    
    // Copy data to buffer
    *buff = SSPBUF;
}

void spiWriteBuffer(uint8_t *buff, uint8_t nBytes) {
    for (uint8_t i = 0; i < nBytes; i++) {
        // Clear interrupt flag
        PIR1bits.SSPIF = 0;

        // Flush buffer
        flush = SSPBUF;
        // Write data
        SSPBUF = buff[i];

        // Wait end of transmission
        while (!PIR1bits.SSPIF);
    }
}

void spiReadBuffer(uint8_t *buff, uint8_t nBytes) {
    for (uint8_t i = 0; i < nBytes; i++) {
        // Send dummy to start clock
        SSPBUF = 0xFF;

        // Wait for data
        while (!SSPSTATbits.BF);

        // Copy data to buffer
        buff[i] = SSPBUF;
    }
}
