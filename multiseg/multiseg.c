#include "reg51.h"
#define uint32 unsigned int
#define uint8 unsigned char
uint8 seg[]={0x3F, 0x06, 0x5B, 
			 0x4F, 0x66, 0x6D, 
			 0x7D, 0x07, 0x7F, 0x6F};  // seg�����ӷ�
uint8 order[]={0x0E, 0x0D, 0x0B, 0x07};
uint32 num = 0;
uint8 count = 0;

sbit dula = P2^6; // ��ѡ��
sbit wela = P2^7; // λѡ��

void init_seg();
void delay(uint32);
void init_timer();
void display(uint8, uint8);

void main()
{
	uint8 i = 0;
	init_seg();
	init_timer();
	while(1)
	{
		display(num/1000, 0);	   //ǧλ
		display(num/100%10, 1);		//��λ
		display(num/10%10, 2);	   //ʮλ
		display(num%10, 3);	   //��λ
		if(num == 10000)
			num = 0;  
	}	
}

void init_seg()
{
	dula = 1;
	P0 = 0x3F;
	dula = 0;

	wela = 1;
	P0 = 0x0F;
	wela = 0;
}


void init_timer()
{
	EA = 1; // �������ж�
	ET0 = 1; // ������ʱ��0�ж�
	TMOD = 0x01; // ���ö�ʱ��0
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	TR0 = 1; // ������ʱ��0
}


void delay(uint32 n)
{
	uint32 i = 0, j = 0;
	for(i = 0; i < n; ++i)
		for(j = 0; j < 70; ++j);
}


void display(uint8 n, uint8 i)
{
	//if(n != 0)
	{
		wela = 1;
		P0 = order[i];
		wela = 0;
		dula = 1;
		P0 = seg[n];
		dula = 0;	
	}
	delay(10);
}


void timer_isr() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	count++;
	if(count == 20)
	{
		num++;
		count = 0;
	}
}
