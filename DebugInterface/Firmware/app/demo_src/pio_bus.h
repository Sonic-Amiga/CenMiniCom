void PIOBus_Reset(unsigned char state);
void PIOBus_Init(void);
void PIOBus_Write(unsigned char addr, unsigned char data);
unsigned char PIOBus_Read(unsigned char addr);
void PIOBus_LED(unsigned char status);
