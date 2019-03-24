/*
 * DA2C_Task3A.c
 *
 * Created: 3/20/2019 10:30:14 PM
 * Author : perezr1
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
// TCNT_ON = (((16MHz/1024)*0.435) -1 ) = 6796
// TCNT_OFF = (((16MHz/1024)*0.29) -1 ) = 4530
int main(void)
{
	DDRB =36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	OCR0A = 255;// max
	TCCR0A = 2; // CTC
	TCCR0B = 5; // 1024
	TIMSK0 = (1<<OCIE0A);
	sei();	
	
	while (1)
	{
	}
}

ISR (TIMER0_COMPA_vect)
{
	TCNT0 = 0; // sets clock
	int count =  0;// sets counter
	// when 60% DC is on
	while(count != 27) // 6796/255 = 27
	{
		while ((TIFR0 & (1<<OCF0A)) == 0)
		{	
			// delay
		}
		TCNT0 = 0; // reset timer
		TIFR0 |= (1<<OCF0A);
		count++; // count += 1
	}
	
	PORTB ^= (1<<2); // toggle portb
	count = 0; // resets count
	TCNT0 = 0; // resets clock
	//TIFR0 |= (1<<OCF0A);
	// when 40% DC is off
	while(count != 18) // 4530/255 = 18
	{
		while ((TIFR0 & (1<<OCF0A)) == 0)
		{
			// delay
		}
		TCNT0 = 0; // resets timer
		TIFR0 |= (1<<OCF0A); // reset
		count++; // count += 1
	}
}


