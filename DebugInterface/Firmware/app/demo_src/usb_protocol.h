#ifndef USB_PROTOCOL_H
#define USB_PROTOCOL_H

typedef enum
{
    COMMAND_RESET = 'S',
    COMMAND_READ  = 'R',
    COMMAND_WRITE = 'W'
} PIO_BUS_COMMANDS;

#define CMD_PACKET_LENGTH 64
#define CMD0_OFFSET 0
#define CMD1_OFFSET 1
#define ADDR_OFFSET 2
#define DATA_OFFSET 10

#endif
