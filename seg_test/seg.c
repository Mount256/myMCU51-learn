// 数码管动态扫描  Proteus电路仿真模拟
#include "reg51.h"
#define uint8 unsigned int
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg共阴接法
unsigned char xbit[]={0x00, 0x01, 0x02 ,0x03, 0x04, 0x05, 0x06, 0x07};

void delay(uint8);

void main()
{
	uint8 i = 0;
	while(1)
	{
		for(i = 0; i < 8; ++i)
		{
			P2 = seg[i]; // 共阴
			P3 = xbit[i];
			delay(5);

			P2 = 0x00; // 消除重影
			delay(5);
		}
	}
}

void delay(uint8 n)
{
	uint8 i = 0, j = 0;
	for(i = 0; i < n; ++i)
		for(j = 0; j < 70; ++j);
}