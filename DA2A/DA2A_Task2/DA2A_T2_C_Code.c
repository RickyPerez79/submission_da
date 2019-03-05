/*
 * DA2A_2_Ccode.c
 *
 * Created: 3/4/2019 5:54:55 PM
 * Author : perezr1
 */ 

 #define F_CPU 16000000UL  // sets frequency to 16MHz
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	PORTB |= (1<<2); // turns off pd2
	DDRC &= (0<<2); // sets it to read
	PORTC |= (0<<2); // has portC clear

    while (1) // while true
    {
if(!(PINC&(1<<PINC2))) // will detect if the push button was pushed 
	{
	PORTB &= ~(1<<2); // will turn the LED on
   _delay_ms(1250); // delay of 1250ms == 1.25 seconds
    }
	else
	{
	PORTB |= (1<<2); // will keep the LED off
	}
	}
return 0;
}
