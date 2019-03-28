/*
 * DA3A_Task1.c
 *
 * Created: 3/27/2019 1:46:32 PM
 * Author : perezr1
 */ 

#define BAUD 9600
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//////////////////////////// Declare functions////////////////
void USART_send(char data);
void USART_putstring(char* StringPtr);
void USART_init(void);
///////////////////////////////////////////////////////////////

char String[] = "Ricky Perez DA3A!!"; //String[] is the variable to output into terminal
char outs[20]; // contains up to 19 characters in the array.
volatile float adc_temp = 79.95; // my birthday MonDay.Year

int main(void)
{
	TCCR1B = 5; // 1024 prescaler 
	TIMSK1 = (1<<TOIE1); //  enable Overflow Interrupt in the Interrupt Mask Register
	TCNT1 = 49911; // 65535-15624
	USART_init();// calls function
	sei();// enable interrupt 
	
	while(1)
	{
			// main loop
	}
}

ISR (TIMER1_OVF_vect)
{
		USART_putstring(String); // prints string
		USART_putstring("\n"); // create a new line.
		USART_send('7'); // In decimal its 55. also my birth month :D
		USART_putstring("\n"); // create a new line.
		snprintf(outs, sizeof(outs), "%f\r\n", adc_temp); // the floating point characters are stored in outs
		USART_putstring(outs); // transmits outs to UART
		TCNT1 = 49911; // reset 

}

void USART_init( void ) 
{
	UBRR0H = 0; //USART Baud Rate Register high
	UBRR0L = F_CPU/16/BAUD - 1;// USART Baud Rate Register low: BAUD prescaler
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void USART_send(char data) // sends data/ integer
{
	while (!(UCSR0A & (1 << UDRE0)));//USART Control and Status Register & ?USART Data Register Empty
		UDR0 = data;
}

void USART_putstring(char *StringPtr) // prints strings in terminal
{
	while ((*StringPtr != '\0')){
		while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = *StringPtr;
				StringPtr++;
	}
}
