#include "reg51.h"
unsigned char num = 0;
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg�����ӷ�
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
void counter_isr() interrupt 1
{
	num++;
}