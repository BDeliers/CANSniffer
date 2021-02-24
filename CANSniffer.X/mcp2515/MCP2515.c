#include "MCP2515.h"

void MCP2515Reset(void) {
    // Initialize SPI
    spiMasterInit();
    
    SPI_SS_LAT = 0;
    spiWriteByte(MCP_RESET);
    SPI_SS_LAT = 1;
}

void MCP2515Read(uint8_t address, uint8_t *buff, uint8_t nBytes) {
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_READ);
    spiWriteByte(address);
    
    spiReadBuffer(buff, nBytes);
    
    SPI_SS_LAT = 1;
}

void MCP2515ReadRxBuffer(uint8_t bufferId, uint8_t *buff, uint8_t nBytes) {
    SPI_SS_LAT = 0;
    
    if (bufferId == 0) {
        spiWriteByte(MCP_READ_RX0);
    }
    else {
        spiWriteByte(MCP_READ_RX1);
    }
    
    spiReadBuffer(buff, nBytes);
    
    SPI_SS_LAT = 1;
}

void MCP2515WriteSingle(uint8_t address, uint8_t value) {
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_WRITE);
    spiWriteByte(address);
    spiWriteByte(value);
    
    SPI_SS_LAT = 1;
}

void MCP2515Write(uint8_t address, uint8_t *buff, uint8_t nBytes) {
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_WRITE);
    spiWriteByte(address);
    
    spiWriteBuffer(buff, nBytes);
    
    SPI_SS_LAT = 1;
}

void MCP2515LoadTxBuffer(uint8_t bufferId, uint8_t *buff, uint8_t nBytes) {
    SPI_SS_LAT = 0;
    
    if (bufferId == 0) {
        spiWriteByte(MCP_LOAD_TX0);
    }
    else if (bufferId == 1) {
        spiWriteByte(MCP_LOAD_TX1);
    }
    else {
        spiWriteByte(MCP_LOAD_TX2);
    }
    
    spiWriteBuffer(buff, nBytes);
    
    SPI_SS_LAT = 1;
}

void MCP2515RequestToSend(uint8_t bufferId) {
    SPI_SS_LAT = 0;
    
    if (bufferId == 0) {
        spiWriteByte(MCP_RTS_TX0);
    }
    else if (bufferId == 1) {
        spiWriteByte(MCP_RTS_TX1);
    }
    else if (bufferId == 2) {
        spiWriteByte(MCP_RTS_TX2);
    }
    else {
        spiWriteByte(MCP_RTS_ALL);
    }
    
    SPI_SS_LAT = 1;
}

uint8_t MCP2515ReadStatus(void) {
    uint8_t buff;
    
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_READ_STATUS);
    spiReadByte(&buff);
    
    SPI_SS_LAT = 1;
    
    return buff;
}

uint8_t MCP2515RxStatus(void) {
    uint8_t buff;
    
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_RX_STATUS);
    spiReadByte(&buff);
    
    SPI_SS_LAT = 1;
    
    return buff;
}

void MCP2515BitModify(uint8_t address, uint8_t mask, uint8_t data) {
    SPI_SS_LAT = 0;
    
    spiWriteByte(MCP_BITMOD);
    
    spiWriteByte(address);
    spiWriteByte(mask);
    spiWriteByte(data);
    
    SPI_SS_LAT = 1;
}