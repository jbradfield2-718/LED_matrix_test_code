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
int brightness=0, cycle=0; needlatch=0;


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
//===============================================================================================
// ISR
//===============================================================================================
ISR(TIMER0_COMPA_vect)
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
//setledarray(4095,2048,1000,1500,1000,750,500,250,125,100,75,50,25,12.5,10,5);
}

	

	