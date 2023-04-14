#include "reg51.h"

unsigned char count = 0, num = 0;
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg�����ӷ�
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
	TH0 = (65536 - 50000) / 256; // 50ms = 50000us  256 = 2^8 �൱�� ��ֵ>>8
	TL0 = (65536 - 50000) % 256;
	ET0 = 1; // ������ʱ��0���ж�
	EA = 1; // �������ж�
	TR0 = 1; // ������ʱ��0
}

void display()
{
	P2 = seg[num];
	if(num == 10)
		num = 0;
}

//0��ʾ�ⲿ�ж�0��1��ʾ��ʱ���ж�0��2��ʾ�ⲿ�ж�1��3��ʾ ��ʱ���ж�1��4��ʾ�����ж�
void timer_isr() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	count++;	
	if(count == 20) // 50ms*20=1000ms=1s��1sʱnum��1������ܵ���������
	{
		count = 0; 
		num++;
	}
}
