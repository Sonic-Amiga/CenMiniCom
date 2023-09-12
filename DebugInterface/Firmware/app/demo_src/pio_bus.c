#include <xc.h>
#include "pio_bus.h"

#define _XTAL_FREQ 20000000UL

#define ADDR_PORT PORTA
#define DATA_PORT PORTB
#define CTRL_PORT PORTC

#define CTL_RST (1 << 0)
#define CTL_nWR (1 << 1)
#define CTL_nRD (1 << 2)

#define CTL_IDLE  (CTL_nWR | CTL_nRD)
#define CTL_RESET (CTL_RST | CTL_IDLE)
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

    PIOBus_Reset();
    
	TRISA = TRIS_OUT;
	TRISB = TRIS_IN;
	TRISC = TRIS_OUT;
}

void PIOBus_Reset(void)
{
    reset = 1;
    CTRL_PORT = CTL_RESET;
}

static void release(void)
{
    if (!reset)
        return;
    
    PORTC = CTL_IDLE;
    reset = 0;
    __delay_us(1);
}

void PIOBus_Write(unsigned char addr, unsigned char data)
{
    release();
    TRISB = TRIS_OUT;
            
    ADDR_PORT = addr;
    DATA_PORT = data;
    CTRL_PORT = CTL_WR;
    __delay_us(1);
    CTRL_PORT = CTL_IDLE;
    __delay_us(1);
}

unsigned char PIOBus_Read(unsigned char addr)
{
    unsigned char ret;

    release();
    TRISB = TRIS_IN;
            
    ADDR_PORT = addr;
    CTRL_PORT = CTL_WR;
    __delay_us(1);
    ret = DATA_PORT;
    CTRL_PORT = CTL_IDLE;
    __delay_us(1);

    return ret;
}
