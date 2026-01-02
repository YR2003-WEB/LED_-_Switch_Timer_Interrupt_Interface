#include<lpc21xx.h>
#define led0 1<<17
#define led1 1<<16
#define sw 14

int flag=0;

void Timer0_isr(void) __irq
{
	T0IR=0x01;
	if(flag==0)
	{
		IOSET1=led1;
		flag=1;
	}
	else
	{
		IOCLR1=led1;
		flag=0;
	}
	VICVectAddr=0;
}

int main()
{
	IODIR0=led0;
	IODIR1=led1;
	T0MCR=0X03;
	T0MR0=15000000-1;
	VICIntSelect=0;
	VICVectCntl0=(0x20)|4;
	VICVectAddr0=(int)Timer0_isr;
	VICIntEnable=1<<4;
	T0TCR=0x01;
	while(1)
	{
		if(((IOPIN0>>sw)&1)==0)
			IOCLR0=led0;
		else
			IOSET0=led0;
	}
}
