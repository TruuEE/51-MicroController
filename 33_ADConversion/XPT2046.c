#include <REGX52.H>
#include "Delay.h"

sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue = 0;
	
	XPT2046_DCLK = 0; // Initialization 
	XPT2046_CS = 0;
	
	// Send Command
	for (i = 0; i < 8; i ++)
	{
		XPT2046_DIN = Command & (0x80 >> i);
		XPT2046_DCLK = 1;
		// Delay(1);
		XPT2046_DCLK = 0;
	}
	
	// Read Data
	for (i = 0; i < 16; i ++)
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
			// Coming, get 1s
		
		if(XPT2046_DOUT) ADValue |= (0x8000 >> i); //. 16 bits
	}
	
	// End this
	XPT2046_CS = 1;
	
	if(Command & 0x08) // 8 bits
	{
		return ADValue >> 8; // 8 bit mode only uses forst 8bits in 16 bits
	}
	else
	{
		return ADValue >> 4; 
	}

}