/*
 * DA4A.c
 *
 * Created: 4/10/2019 1:37:12 PM
 * Author : perezr1
 */ 

/******************** Define Variable/Include Libraries **********************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*****************************************************************************/

/************************* Function Prototype *********************************/
void init_adc(void);
/*****************************************************************************/

/******************************Global Variable********************************/ 
int status_motor = 0; // status of the motor each time push button is pressed
/*****************************************************************************/

int main()
{
/*************************Set Ports Up*****************************/
	DDRD = 0x40; //enable port D
	DDRC = 0x04; // set Port C as outputs
	PORTC |= (1<<2); // enable pull-up pin
/******************************************************************/



/******************************************************************/
	TCCR0A=0x83; // set fast PWM & clear OCR0A on MATCH
	TCCR0B=0x05; // 1024 prescalar
/******************************************************************/

/*************************Set up PinChange Interrupt*****************************/
	PCICR = 0x02; // 0x02 is PCIE1, that is, enable PCIE1 for PCMSK1 to work
	PCMSK1 = 0x04; // enable pin changes on PCINT9 (PC1)
/******************************************************************************/
	init_adc(); // function call for init_adc 

	sei(); // enable interrupt

	while (1)
	{
		// wait here 
	}
}
void init_adc(void) // Initiate ADC functions
{
	ADMUX = (1<<REFS0); // Reference voltage at A_ref
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // enable ADC/Start Conversion , 128 prescalar
}

// Pin Change Interrupt Service Routine 
ISR(PCINT1_vect)
{
	if(!(PINC & (1<<PINC2))) // if push button is pressed go in if statement
	{
		if(status_motor == 0) // motor will be OFF
		{
			OCR0A = 0;
			_delay_ms(1000); // delay for debouncing
		}
		if (status_motor == 1) // motor will be ON
		{
			while((ADCSRA&(1<<ADIF))==0); // wait for conversion
			// when convertion is done, it will store the value into OCR0A
			OCR0A = ADC/10; // Converts ADC/Output value to 0CR0A
			_delay_ms(1000); // delay for debouncing
		}
		status_motor ^= 1; //update status (ON = 1, OFF = 0) of the motor when push button is pressed
	}
}


