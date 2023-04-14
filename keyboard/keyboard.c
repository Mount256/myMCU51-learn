#include "reg51.h"
#define uint8 unsigned char
#define uint32 unsigned int

/*  原理解释	H:行	L:列

	初始状态：
	H3 H2 H1 H0 L3 L2 L1 L0
	1  1  1  1  0  0  0  0	-->0xF0
	0  0  0  0  1  1  1  1	-->0x0F

	当第一行第一列被按下时：
	H3 H2 H1 H0 L3 L2 L1 L0
	1  1  1  0  0  0  0  0	-->0xE0
	0  0  0  0  1  1  1  0	-->0x0E
	按位或后：
	1  1  1  0  1  1  1  0	-->0xEE

	当第一行第二列被按下时：
	H3 H2 H1 H0 L3 L2 L1 L0
	1  1  1  0  0  0  0  0	-->0xE0
	0  0  0  0  1  1  0  1	-->0x0D
	按位或后：
	1  1  1  0  1  1  0  1	-->0xED

*/

uint8 seg[]={0x3F,0x06,0x5B,
			 0x4F,0x66,0x6D,
			 0x7D,0x07,0x7F,0x6F};
void delay(uint32);
void display(uint8);
void key_scan();

int main()
{
	P2 = 0x00;
	while(1)
	{
		key_scan();
	}
}

void delay(uint32 n)
{
	uint32 i = 0, j = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < 120; j++);
}

void display(uint8 temp)
{
	switch(temp)
	{
		case 0xEE: P2 = seg[0]; break;
		case 0xED: P2 = seg[1]; break;
		default: break;
	}
}

void key_scan()
{
	uint8 temp0 = 0, temp1 = 0, temp = 0;
	P1 = 0xF0;
	if(P1 != 0xF0)
	{
		delay(20);
		temp0 = P1;
		P1 = 0x0F;
		if(P1 != 0x0F)
			temp1 = P1;
	}
	temp = temp0 + temp1;
	display(temp);
}