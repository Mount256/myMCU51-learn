#include "reg51.h"
unsigned char num = 0;
unsigned char seg[]={0x3F, 0x06, 0x5B, 
					 0x4F, 0x66, 0x6D, 
					 0x7D, 0x07, 0x7F, 0x6F};  // seg�����ӷ� 0-9

void init_ex()
{
	IT0 = 1; // �ⲿ�ж�0������ʽ����Ϊ���ش���
	EX0 = 1; // �ⲿ�ж�ITNT0����Ϊʹ���жϣ��������жϣ�
	EA = 1;	// ���������ж�����
}

void main()
{
	init_ex();
	while(1)
		P2 = seg[num];
}

void ex_isr() interrupt 0
{
	num++;
	if(num == 10)
		num = 0;
}