/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license),
please contact mla_licensing@microchip.com
*******************************************************************************/

#include "app_device_cdc.h"

void APP_DeviceCDCInitialize() {
    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 115200;

    DIGITAL_LED_LAT = 1;
}

void APP_DeviceCDCTasks() {
    // If device is not configured
    if(USBGetDeviceState() < CONFIGURED_STATE) {
        // Try it attach it back
        USBDeviceAttach();
        return;
    }

    if(USBIsDeviceSuspended()) {
        return;
    }

    CDCTxService();
}
