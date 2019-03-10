#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int main ()
{
	DDRB |= (1<<2)|(1<<5);//PB5 as an output
	PORTB |= (1<<2)|(1<<5);


	PORTD = (1<<2);//pull-up activated
	EICRA = 0x2;//make INT0 falling edge triggered
	EIMSK = (1<<INT0);//enable external interrupt 0
	sei ();//enable interrupts
	while (1);//wait here
}
ISR (INT0_vect)//ISR for external interrupt 0
{
	PORTB ^= (1<<2);//toggle PORTB.2
	_delay_ms(1250);
	PORTB ^= (1<<2);//toggle PORTB.2
}