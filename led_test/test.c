#include "reg51.h"

void delay(unsigned int);

void main()
{
	while(1)
	{
		unsigned int i = 0;
		for(i = 0; i < 8; i++)
		{
			P2 = ~(0x01<<i);
			delay(50);
		}
	}
}

void delay(unsigned int n)
{
	unsigned int i = 0, j = 0;
	for(i = 0 ; i <= n; ++i)
		for(j = 0; j <= 120; ++j); 
}