#ifndef APP_DEVICE_CDC_H
#define APP_DEVICE_CDC_H

// Standard includes
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

// USB framework
#include "usb.h"
#include "usb_device_cdc.h"
#include "usb_config.h"

// Custom config
#include "../config.h"

/*   Methods   */
// Initialize baudrate
void APP_DeviceCDCInitialize();

// Recurrent tasts
void APP_DeviceCDCTasks();

#endif //APP_DEVICE_CDC_H


