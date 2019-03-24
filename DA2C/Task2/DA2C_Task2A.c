/*
 * DA2C_Task2A.c
 *
 * Created: 3/20/2019 9:06:40 PM
 * Author : perezr1
 */ 

#define F_CPU 16000000UL  // sets frequency to 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
// // TCNT0 = (((16MHz/1024)*1.25) -1 ) = 19530
int main(void)
{
	DDRB =36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	TCCR0B = 5; // 1024
	TIMSK0 = (1<< TOIE0);
	sei();
	while (1)
	{
	// while true
	}
}

ISR (TIMER0_OVF_vect)
{
	TCNT0 = 0; // sets clock
	int count =  0; // keeps count of overflow
	// when 60% DC is on
	while(count!=27) // 6796/255 = 27
	{
		while ( TCNT0 != 255)
		{
			
			// delay
		}
		TCNT0 =0; // reset timer
		count++; // count += 1
	}
	
	PORTB ^= (1<<2); // toggle portb
	count = 0; // resets count
	TCNT0 = 0; // resets clock
	// when 40% DC is off
	while(count!=18) // 4530/255 = 18
	{
		while (TCNT0 != 255)
		{
			// delay
		}
		TCNT0 =0; // resets timer
		count++; // count += 1
	}
}

