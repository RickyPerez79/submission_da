/*
 * DA2A_1_C_code.c
 *
 * Created: 3/4/2019 7:50:37 PM
 * Author : perezr1
 */ 

#include <avr/io.h>

int main(void)
{
	DDRB =36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	TCCR1B = 5; // 1024

	while (1)
	{
		TCNT1 = 0; // sets clock
		
		while( TCNT1 != 6796) // when 60% DC is on 
		{
			//Delay
		}
		PORTB ^= (1<<2); // toggle portb
		TCNT1 = 0; // resets clock
		while( TCNT1 != 4530) // when 40% DC is off
		{
			// Delay
		}
	}
}
