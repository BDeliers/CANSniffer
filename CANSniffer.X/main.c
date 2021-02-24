#include "main.h"

void main(void) {
    //Primary clock source selected.
    OSCCON = 0;

    // Wait for PLL to be locked
    {
        unsigned int pll_startup_counter = 600;
        while(pll_startup_counter--);
    }

    // Reset pins
    initPins();

    // Assign input pins
    DIGITAL_BAT_TRIS = 1;

    MCP2551_INT_TRIS = 1;
    MCP2551_RXINT0_TRIS = 1;
    MCP2551_RXINT1_TRIS = 1;

    SPI_MISO_TRIS = 1;

    // Raise nSS
    SPI_SS_LAT = 1;

    // Blink LED
    for (uint8_t i = 0; i < 5; i++) {
        DIGITAL_LED_LAT = 1;
        __delay_ms(200);
        DIGITAL_LED_LAT = 0;
        __delay_ms(200);
    }

    // Initialize interrupts
    initInterrupt();

    // Initialize USB framework
    USBDeviceInit();
    // Attch device to computer
    USBDeviceAttach();

    while(1) {
        // USB routine
        USBDeviceTasks();

        if (USBUSARTIsTxTrfReady()) {
            // Get data from computer
            numBytesRead = getsUSBUSART(usbReadBuffer, sizeof(usbReadBuffer));

            // If car is connected and we didn't initialized the MCP2515 CAN controller
            if ((DIGITAL_BAT_PORT == 1) && !mcpInitialized) {
                // Initialize MCP2515 CAN controller. Device will enter in configuration mode
                MCP2515Reset();

                // Set baudrate to 500kBps for Peugeot CAN bus
                MCP2515WriteSingle(MCP_CNF1, 0x00);
                MCP2515WriteSingle(MCP_CNF2, 0x90);
                MCP2515WriteSingle(MCP_CNF3, 0x82);

                // Set RX buffer 0 to receive all messages (RXM = 0b11) and RXB0 rollover enabled (BUKT = 0b1)
                MCP2515WriteSingle(MCP_RXB0CTRL, 0b01100100);
                // Use nRX0BF and nRX1BF as interrupt pins
                MCP2515WriteSingle(MCP_BFPCTRL, 0b00001111);

                // Enable RXB interrupts
                MCP2515BitModify(MCP_CANINTE, 0b00000011, 0b00000011);

                // Set as Listen-Only mode
                MCP2515BitModify(MCP_CANCTRL, 0b11100000, MODE_LISTENONLY);

                // Print device status to serial
                MCP2515Read(MCP_CANSTAT, canBuff, 1);
                putUSBUSART(canBuff, 1);

                // Raise flag
                mcpInitialized = true;
            }

            // If CAN is ready
            else if (mcpInitialized) {
                // If receive buffer 0 is full
                //if (MCP2515ReadStatus() & 0b00000001) {
                if (!MCP2551_RXINT0_PORT) {
                    // Read data from buffer
                    MCP2515Read(MCP_RXB0SIDH, &canBuff[1], 13);
                    // Clear interrupt
                    MCP2515BitModify(MCP_CANINTF, 0b00000001, 0b00000000);

                    // Store data in the structure
                    /*canData.stdId = canBuff[0] << 3;
                    canData.stdId |= (canBuff[1] & 0b11100000) >> 5;

                    canData.stdRemoteTxReq = canBuff[1] & 0b00010000;
                    canData.extended = canBuff[1] & 0b00001000;

                    canData.extId = (canBuff[1] & 0b00000011) << 16;
                    canData.extId |= canBuff[2] << 8;
                    canData.extId |= canBuff[3];

                    canData.extRemoteTxReq = canBuff[4] & 0b010000000;

                    canData.dataLen = canBuff[4] & 0b00001111;

                    for (uint8_t i = 0; i < canData.dataLen; i++) {
                        canData.data[i] = canBuff[i+5];
                    }*/

                    // Dump data (+ formatting) to serial
                    canBuff[0] = '\n';
                    canBuff[15] = '\r';
                    putUSBUSART(canBuff, 16);
                }
            }
        }

        // CDC tasks
        APP_DeviceCDCTasks();
    }

    return;
}

// High priority interrupt routine
void __interrupt(high_priority) highPriorityISR(void) {
    return;
}

// Low priority interrupt routine
void __interrupt(low_priority) lowPriorityISR(void) {
    return;
}
