#ifndef MAIN_H
#define	MAIN_H

// PIC includes
#include <xc.h>
#include <stdbool.h>

// Configuration
#include "config.h"

// USB app
#include "usb.h"
#include "app_device_cdc.h"

// MCP2515 Driver
#include "mcp2515/MCP2515.h"

/*   GLOBAL VARIABLES   */
bool mcpInitialized = false;
uint8_t canBuff[16];
canPayload canData;

/*   USB buffers   */
uint8_t usbReadBuffer[CDC_DATA_OUT_EP_SIZE];
uint8_t usbWriteBuffer[CDC_DATA_IN_EP_SIZE];
uint8_t numBytesRead = 0;

#endif	/* MAIN_H */

