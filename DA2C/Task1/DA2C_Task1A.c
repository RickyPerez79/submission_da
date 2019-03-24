/*
 * DA2C_Task1A.c
 *
 * Created: 3/20/2019 6:10:30 PM
 * Author : perezr1
 */ 
#include <avr/io.h>
// TCNT_ON = (((16MHz/1024)*0.435) -1 ) = 6796
// TCNT_OFF = (((16MHz/1024)*0.29) -1 ) = 4530
int main(void)
{
	DDRB =36;  // sets to pd2 and pd5
	PORTB |= (1<<5); // turns off pd5
	TCCR0B = 5; // 1024
	while (1)
	{
		TCNT0 = 0; // sets clock
		int count =  0;
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
}
