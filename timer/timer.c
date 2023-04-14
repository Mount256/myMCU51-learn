#include "reg51.h"

unsigned char count = 0, num = 0;
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg共阴接法
void init_timer();
void display();

void main()
{
	init_timer();
	while(1)
		display();
}

void init_timer()
{
	TMOD = 0x01; // 0000 0001
	TH0 = (65536 - 50000) / 256; // 50ms = 50000us  256 = 2^8 相当于 初值>>8
	TL0 = (65536 - 50000) % 256;
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
void timer_isr() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	count++;	
	if(count == 20) // 50ms*20=1000ms=1s，1s时num加1，数码管的数字跳动
	{
		count = 0; 
		num++;
	}
}
