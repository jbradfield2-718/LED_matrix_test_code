/*
 * GccApplication1.c
 *	This program was created as a mockup prior to building a 12 x 24 LED Matrix.  The program is meant to work out
 *	bugs/understanding of the use of the TI TLC5940 16 channel PWM control LED Driver IC.
 *
 * Created: 11/17/2012 5:27:40 PM
 *  Author: Justin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define PULSE(ADDRESS,BIT)	do{ \
								SETBIT(ADDRESS,BIT); \
								CLEARBIT(ADDRESS,BIT); \
								} while(0);
#define serin	5
#define sclk	1
#define xlat	2
#define blank	3


void init();
void latch();
void setledarray(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
void setledlevel(int);
void arraypulse();
int brightness=0, cycle=0; needlatch=0, last, swivel=0, count=0;
int a=50, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0, j=0, k=0, l=0, m=0, n=0, o=0, p=0;


int main(void)
{
	init();
	for (;;)		// Awaiting interrupts...
	{
		
	}
	   
		
    
	return 0;
}
/*---------------------------------------------------------------------------------------------------------------------------------
	Init:  Initialization code for the AVR ATMEGA328P
-----------------------------------------------------------------------------------------------------------------------------------*/
void init()
{
	DDRB = 0xff;		//Sets all pins to outputs
	// Setup timer0 in CTC mode to count to 4096 for the grayscale cycle of the TI IC.
	SETBIT(TCCR0A,1);	// Sets WGM01 for CTC mode
	TCCR0B = ((1 << CS02) | (1 << CS00));	// Sets bits 0, 3 to one.  This configures Timer 0 prescaler = 1024
	OCR0A = 4;
	SETBIT(TIMSK0,OCIE0A);					// Sets bit 1 in timersk0 for match interrupt.
	sei();
	return;
}
//--------------------------------------------------------------
/*	Latches the data stream into the TLC 5940 */
//--------------------------------------------------------------
void latch()
{
	SETBIT(PORTB,blank);
	SETBIT(PORTB,xlat);
	CLEARBIT(PORTB,xlat);
	CLEARBIT(PORTB,blank);
	
}
//--------------------------------------------------------------
/*	Sets the LED array brightness with calls to setledlevel */
//--------------------------------------------------------------
void setledarray(int led0, int led1, int led2, int led3, int led4, int led5, int led6, int led7, \
				int led8, int led9, int led10, int led11, int led12, int led13, int led14, int led15)
{
	setledlevel(led0);
	setledlevel(led1);
	setledlevel(led2);
	setledlevel(led3);
	setledlevel(led4);
	setledlevel(led5);
	setledlevel(led6);
	setledlevel(led7);
	setledlevel(led8);
	setledlevel(led9);
	setledlevel(led10);
	setledlevel(led11);
	setledlevel(led12);
	setledlevel(led13);
	setledlevel(led14);
	setledlevel(led15);
	latch();
}
void setledlevel(int led)
{
	int brtval = 2048;	//	This variable holds the MSB of brightness
	int i;
	do 
	{
		i = (led & brtval);	// logical and to determine if MSB in LED0 is a 1 or 0
		if (i>0)
		{
			SETBIT(PORTB,serin);
		}
		else
			CLEARBIT(PORTB,serin);
		brtval = brtval/2;
		PULSE(PORTB,sclk);
	} while (brtval >= 1);
	
}
/*===============================================================================================
	Arraypulse--pulses the entire ledarray bright-->dim
================================================================================================*/
void arraypulse()
{
	int i, led0, led1, led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12, led13, led14, led15;


switch(cycle)
{
	case(0):
	{
		led0 = brightness;
		led1 = brightness;
		led2 = brightness;
		led3 = brightness;
		led4 = brightness;
		led5 = brightness;
		led6 = brightness;
		led7 = brightness;
		led8 = brightness;
		led9 = brightness;
		led10 = brightness;
		led11 = brightness;
		led12 = brightness;
		led13 = brightness;
		led14 = brightness;
		led15 = brightness;
		setledarray(led0,led1,led2,led3,led4,led5,led6,led7,led8,led9,led10,led11,led12,led13,led14,led15);
		latch();
		if(brightness>=2000)
		{
			cycle=1;
		}
		brightness=brightness+1;
		break;
	}		
	case(1):
	{	
			led0 = brightness;
			led1 = brightness;
			led2 = brightness;
			led3 = brightness;
			led4 = brightness;
			led5 = brightness;
			led6 = brightness;
			led7 = brightness;
			led8 = brightness;
			led9 = brightness;
			led10 = brightness;
			led11 = brightness;
			led12 = brightness;
			led13 = brightness;
			led14 = brightness;
			led15 = brightness;
			setledarray(led0,led1,led2,led3,led4,led5,led6,led7,led8,led9,led10,led11,led12,led13,led14,led15);
			//setledarray(4095,2048,1000,1500,1000,750,500,250,125,100,75,50,25,12.5,10,5);
			latch();
			if(brightness<=0)
			{
				cycle=0;
			}
			brightness=brightness-1;
			break;
		}			
		} 
}
//===============================================================================================
// ISR
//===============================================================================================
ISR(TIMER0_COMPA_vect)
{
//arraypulse();	
//setledarray(4095,2048,1000,1500,1000,750,500,250,125,100,75,50,25,12.5,10,5);
switch(swivel)
{
	case(0):
	a=150; b=50; c=0; d=0; e=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	last=0;
	if (count=10)
	{
		swivel=1;
		count=0;
	}
	count+=1;
	break;

	case(1):
	a=50; b=150; c=50; d=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==0 && count==100)
	{
		swivel+=1;
		count=0;
		last=1;
	}
	else if(count==100)
	{
		swivel-=1;
		count=0;
		last=1;
	}
	count+=1;
	break;

	case(2):
	a=0; b=50; c=150; d=50; e=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==1 && count==100)
	{
		swivel+=1;
		count=0;
		last=2;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=2;
	}
	count+=1;
	break;
	
	case(3):
	b=0; c=50; d=150; e=50; f=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==2 && count==100)
	{
		swivel+=1;
		count=0;
		last=3;
	}
	else if(count==100)
	{
		swivel-=1;
		count=0;
		last=3;
	}
	count+=1;
	break;
	
	case(4):
	c=0; d=50; e=150; f=50; g=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==3 && count==100)
	{
		swivel+=1;
		count=0;
		last=4;
	}
	else if(count==100)
	{
		swivel-=1;
		count=0;
		last=4;
	}
	count+=1;
	break;
	
	case(5):
	d=0; e=50; f=150; g=50; h=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==4 && count==100)
	{
		swivel+=1;
		count=0;
		last=5;
	}
	else if(count==100)
	{
		swivel-=1;
		count=0;
		last=5;
	}
	count+=1;
	break;
	
	case(6):
	e=0; f=50; g=150; h=50; i=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==5 && count==100)
	{
		swivel+=1;
		count=0;
		last=6;
	}
	else if(count==100)
	{
		swivel-=1;
		count=0;
		last=6;
	}
	count+=1;
	break;
	
	case(7):
	f=0; g=50; h=150; i=50; j=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==6 && count==100)
	{
		swivel+=1;
		count=0;
		last=7;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=7;
	}
	count+=1;
	break;
	
	case(8):
	g=0; h=50; i=150; j=50; k=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==7 && count==100)
	{
		swivel+=1;
		count=0;
		last=8;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=8;
	}
	count+=1;
	break;
	
	case(9):
	h=0; i=50; j=150; k=50; l=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==8 && count==100)
	{
		swivel+=1;
		count=0;
		last=9;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=9;
	}
	count+=1;
	break;
	
	case(10):
	i=0; j=50; k=150; l=50; m=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==9 && count==100)
	{
		swivel+=1;
		count=0;
		last=10;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=10;
	}
	count+=1;
	break;
	
	case(11):
	j=0; k=50; l=150; m=50; n=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==10 && count==100)
	{
		swivel+=1;
		count=0;
		last=11;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=11;
	}
	count+=1;
	break;
	
	case(12):
	k=0; l=50; m=150; n=50; o=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==11 && count==100)
	{
		swivel+=1;
		count=0;
		last=12;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=12;
	}
	count+=1;
	break;
	
	case(13):
	l=0; m=50; n=150; o=50; p=0;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==12 && count==100)
	{
		swivel+=1;
		count=0;
		last=13;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=13;
	}
	count+=1;
	break;
	
	case(14):
	m=0; n=50; o=150; p=50;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (last==13 && count==100)
	{
		swivel+=1;
		count=0;
		last=14;
	}
	else if (count==100)
	{
		swivel-=1;
		count=0;
		last=14;
	}
	count+=1;
	break;
	
	case(15):
	n=0; o=50; p=150;
	setledarray(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	if (count==100)
	{
		swivel-=1;
		count=0;
	}
	count+=1;
	last=15;
	break;

}
}

	

	