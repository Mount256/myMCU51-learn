#include "reg51.h"
unsigned char num = 0;
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg共阴接法
void init_counter();
void display();

void main()
{
	init_counter();
	while(1)
		display();
}

void init_counter()
{
	TMOD = 0x06; // 0000 0110
	TH0 = 256 - 1;
	TL0 = 256 - 1;
	ET0 = 1; // 开启定时器0的中断
	EA = 1; // 开启总中断
	TR0 = 1; // 启动定时器0
}

void display()
{
	P2 = seg[num];
	if(num == 10)
		num = 0;
}

//0表示外部中断0，1表示定时器中断0，2表示外部中断1，3表示 定时器中断1，4表示串口中断
void counter_isr() interrupt 1
{
	num++;
}