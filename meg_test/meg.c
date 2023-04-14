#include "reg51.h"
#define uint8 unsigned int
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg共阴接法

void delay(uint8);

void main()
{
	uint8 i = 0;
	while(1)
	{
		for(i = 0; i < 10; ++i)
		{
			P2 = seg[i]; // 共阴
			P0 = ~seg[i]; // 共阳
			delay(1000);
		}
	}
}

void delay(uint8 n)
{
	uint8 i = 0, j = 0;
	for(i = 0; i < n; ++i)
		for(j = 0; j < 120; ++j);
}