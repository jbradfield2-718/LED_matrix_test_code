/*
 * GccApplication1.c
 *	This program was created as a mockup prior to building a 12 x 24 LED Matrix.  The program is meant to work out
 *	bugs/understanding of the use of the TI TLC5940 16 channel PWM control LED Driver IC.
 *
 * Created: 11/17/2012 5:27:40 PM
 *  Author: Justin
 */ 

#include <avr/io.h>
#include<util/delay.h>
#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define serin	5
#define sclk	1
#define xlat	2
#define blank	3
#define gsclk	4

void latch();
void setledarray(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
void setledlevel(int);



int main(void)
{
	DDRB = 0xff;		//Sets all pins to outputs
	int i, led0, led1, led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12, led13, led14, led15;
    while(1)
    {	
		

		for(i=0; i<20; i++)
		{
		led0 = i*i;
		led1 = i*i;
		led2 = i*i;
		led3 = i*i;
		led4 = i*i;
		led5 = i*i;
		led6 = i*i;
		led7 = i*i;
		led8 = i*i;
		led9 = i*i;
		led10 = i*i;
		led11 = i*i;
		led12 = i*i;
		led13 = i*i;
		led14 = i*i;
		led15 = i*i;
		setledarray(led0,led1,led2,led3,led4,led5,led6,led7,led8,led9,led10,led11,led12,led13,led14,led15);
		latch();
		_delay_ms(100);
		
		
		}
		
		for(i=20; i > -1; i--)
		{
			led0 = i*i;
			led1 = i*i;
			led2 = i*i;
			led3 = i*i;
			led4 = i*i;
			led5 = i*i;
			led6 = i*i;
			led7 = i*i;
			led8 = i*i;
			led9 = i*i;
			led10 = i*i;
			led11 = i*i;
			led12 = i*i;
			led13 = i*i;
			led14 = i*i;
			led15 = i*i;
			setledarray(led0,led1,led2,led3,led4,led5,led6,led7,led8,led9,led10,led11,led12,led13,led14,led15);
			latch();
			_delay_ms(100);			
		}    
		/*setledarray(250,225,200,175,150,125,100,75,50,25,0,0,0,0,0,0);
		latch();*/
    }
	return 0;
}
/*	Latches the data stream into the TLC 5940 */
//--------------------------------------------------------------
void latch()
{
	SETBIT(PORTB,blank);
	SETBIT(PORTB,xlat);
	CLEARBIT(PORTB,xlat);
	CLEARBIT(PORTB,blank);
	for (int i=0; i<4096; i++)
	{
		SETBIT(PORTB,gsclk);
		CLEARBIT(PORTB,gsclk);
	}
}
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
	int brtval = 2048;	//	This variable holds the max brightness value
	int i;
	
	
	
	do 
	{
		CLEARBIT(PORTB,sclk);	//serial low to begin clock data in
		i = (led & brtval);	// logical and to determine if MSB in LED0 is a 1 or 0
		if (i>0)
		{
			SETBIT(PORTB,serin);
		}
		else
			CLEARBIT(PORTB,serin);
		brtval = brtval/2;
		SETBIT(PORTB,sclk);
	} while (brtval >= 1);
	
}
//===============================================================================================
// grayscale cycle.  Ensures the data is properly clocked into TLC 5940
//===============================================================================================


	