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

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"

#include <string.h>

#include "system.h"
#include "pio_bus.h"
#include "usb_protocol.h"

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[CMD_PACKET_LENGTH];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[CMD_PACKET_LENGTH];
        #pragma udata

    #elif defined(__XC8)
        unsigned char ReceivedDataBuffer[CMD_PACKET_LENGTH] HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[CMD_PACKET_LENGTH] HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[CMD_PACKET_LENGTH];
    unsigned char ToSendDataBuffer[CMD_PACKET_LENGTH];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

/** DEFINITIONS ****************************************************/


/** FUNCTIONS ******************************************************/

static void startRead(void)
{
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP, ReceivedDataBuffer, sizeof(ReceivedDataBuffer));
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    startRead();
}

static void set_reply(unsigned char *reply, unsigned char cmd0, unsigned char cmd1)
{
    reply[CMD0_OFFSET] = cmd0;
    reply[CMD1_OFFSET] = cmd1;
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks()
{
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
    
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false)
    {
        uint8_t response[CMD_PACKET_LENGTH] = {0};
        unsigned char cmd0 = ReceivedDataBuffer[CMD0_OFFSET];
        unsigned char cmd1 = ReceivedDataBuffer[CMD1_OFFSET];
        
        // Any unknown command will respond with '??'
        response[CMD0_OFFSET] = '?';
        response[CMD1_OFFSET] = '?';
        
        switch(cmd0)
        {
            case COMMAND_RESET:
                // 'S' - control bus reset
                // data (1 byte) - logical line state (1 = asserted)
                PIOBus_Reset(ReceivedDataBuffer[DATA_OFFSET]);
                set_reply(response, cmd0, 0);
                response[DATA_OFFSET] = ReceivedDataBuffer[DATA_OFFSET];
                break;

            case COMMAND_WRITE:
                // 'W' - Write value to the specified address
                // cmd1 - length of data to write.
                // addr - address to write to
                // data (`cmd1` bytes) - data to write
                switch (cmd1) {
                    case 1:
                        PIOBus_Write(ReceivedDataBuffer[ADDR_OFFSET], ReceivedDataBuffer[DATA_OFFSET]);
                        memcpy(response, ReceivedDataBuffer, sizeof(response));
                        break;
                }
                break;

            case COMMAND_READ:
                // 'R' - Read value from the specified address
                // cmd1 - length of data to read
                // addr - address to read from
                switch (cmd1) {
                    case 1:                        
                        response[DATA_OFFSET] = PIOBus_Read(ReceivedDataBuffer[ADDR_OFFSET]);
                        set_reply(response, cmd0, cmd1);
                        response[ADDR_OFFSET] = ReceivedDataBuffer[ADDR_OFFSET];
                        break;
                }
                break;
        }

        // Send the reply
        // Check to make sure the endpoint/buffer is free before we modify the contents
        if(!HIDTxHandleBusy(USBInHandle))
        {
            memcpy(ToSendDataBuffer, response, sizeof(response));
            //Prepare the USB module to send the data packet to the host
            USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, ToSendDataBuffer, sizeof(ToSendDataBuffer));
        }
        
        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        startRead();
    }
}