#include <xc.h>
#include "pio_bus.h"

#define _XTAL_FREQ 20000000UL

#define ADDR_PORT PORTA
#define DATA_PORT PORTB
#define CTRL_PORT PORTC

#define ADDR_DIR  TRISA
#define DATA_DIR  TRISB
#define CTRL_DIR  TRISC

#define CTL_RST (1 << 0)
#define CTL_nWR (1 << 1)
#define CTL_nRD (1 << 2)

#define CTL_IDLE  (CTL_nWR | CTL_nRD)
#define CTL_WR    (CTL_nRD)
#define CTL_RD    (CTL_nWR)

#define TRIS_OUT 0x00
#define TRIS_IN  0xFF

static int reset;

void PIOBus_Init(void)
{
    ADCON1 = 0x0F;
    
    ADDR_PORT = 0;
    DATA_PORT = 0;

    PIOBus_Reset(1);

	ADDR_DIR = TRIS_OUT;
	DATA_DIR = TRIS_IN;
	CTRL_DIR = TRIS_OUT;
}

void PIOBus_Reset(unsigned char state)
{
    unsigned char ctl = CTL_IDLE;

    if (state)
        ctl |= CTL_RST;

    reset = state;
    CTRL_PORT = ctl;
}

static void release(void)
{
    if (reset) {
        PIOBus_Reset(0);
    }
}

void PIOBus_Write(unsigned char addr, unsigned char data)
{
    release();
    DATA_DIR = TRIS_OUT;
    ADDR_PORT = addr;
    DATA_PORT = data;
    CTRL_PORT = CTL_WR;
    _delay(2);  // 400 ns
    CTRL_PORT = CTL_IDLE;
}

unsigned char PIOBus_Read(unsigned char addr)
{
    unsigned char ret;

    release();
    DATA_DIR = TRIS_IN;  
    ADDR_PORT = addr;
    CTRL_PORT = CTL_RD;
    _delay(2);
    ret = DATA_PORT;
    CTRL_PORT = CTL_IDLE;

    return ret;
}
