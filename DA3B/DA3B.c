/*
 * DA3B.c
 *
 * Created: 3/29/2019 12:04:14 AM
 * Author : perezr1
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart_init();
void usart_send(unsigned char ch);

// TCNT1 = 65535 - ( ((16Mz/1024) * 1sec) - 1 ) = 49911 

int main(void)
{
    usart_init();
	
	/** Setup and enable ADC **/

	ADMUX = (0<<REFS1)|
			(1<<REFS0)| //AVcc - external cap at AREF
			(0<<ADLAR)| //ADC Left Adjust Result
			(1<<MUX2)| //Analog Channel Selection Bits
			(0<<MUX1)| //ADC5(PC5, PIN28)
			(1<<MUX0);
			
	ADCSRA =(1<<ADEN)|  //ADC Enable
		 	(0<<ADSC)|  //ADC Start Conversion
			(1<<ADATE)| //ADC Auto Trigger Enable
			(0<<ADIF)| //ADC Interrupt Flag
			(0<<ADIE)| //ADC Interrupt Enable
			(1<<ADPS2)| //ADC Prescaler Select Bits
			(0<<ADPS1)| 
			(1<<ADPS0);
	TCCR1B = 5;	//setting the prescaler	to 1024
	TIMSK1 = (1<<TOIE1);	//enable interrupt flag
	TCNT1 = 49911;	//set TCNT1	
	sei();//enable	interrupt
	while(1)
	{
		//main	loop
	}
}

ISR(TIMER1_OVF_vect)
{
		ADCSRA|=(1<<ADSC); //start conversion
		while((ADCSRA&(1<<ADIF)) ==0); //wait for conversion to finish
		
		ADCSRA |= (1<<ADIF);
		
		int a = ADCL;
		a = a | (ADCH<<8);
		a = (a/1024.0) * 5000/10;
		usart_send((a/100)+'0');
		a = a % 100;
		usart_send((a/10) + '0');
		a = a % 10;
		usart_send((a)+'0');
		usart_send('\r');

		TCNT1 = 49911; // resets timer
}

usart_init(void)
{
	UCSR0B = (1<<TXEN0); // Enable	TX
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = F_CPU/16/BAUD_RATE - 1;
}

void usart_send(unsigned char ch)
{
	while(!(UCSR0A & (1<<UDRE0)));  //wait until UDR0 is empty
	UDR0 = ch;						//transmit ch
}

void usart_print(char * str)
{
	int i = 0;
	while(str[i] != 0)
		usart_send(str[i]);		
}


