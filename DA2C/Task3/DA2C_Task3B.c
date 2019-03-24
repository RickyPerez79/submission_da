/*
 * DA2C_Task3B.c
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
	DDRB = 36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	PORTB |= (1<<2); // turns off pd2
	DDRC &= (0<<2); // sets it to read
	PORTC |= (0<<2); // has portC clear
	OCR0A = 255;// overflow
	TCCR0A = 2;// CTC mode
	TCCR0B = 5; // 1024
	TIMSK0 = (1<<OCIE0A);
	sei();
	while (1)
	{
		// while true
	}
}
ISR (TIMER0_COMPA_vect)
{
	TCNT0 = 0; // timer is set to zero
	int counter = 0; // resets counter
	if(!(PINC&(1<<PINC2))) // will detect if the push button was pushed
	{
		while(counter < 77) // 19530/255 = 77
		{
			while ((TIFR0 & (1<<OCF0A)) == 0)
			{
				PORTB &= ~(1<<2); // will turn the LED on
			}
			TCNT0 =0; // resets timer
			TIFR0 |= (1<<OCF0A);//resets
			counter++; // counter += 1
		}
		counter = 0; // resets counter
	}
	else
	{
		PORTB |= (1<<2); // will keep the LED off
	}
	
}
