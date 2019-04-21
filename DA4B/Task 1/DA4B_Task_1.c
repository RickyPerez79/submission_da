/*
 * DA_4B_Task_1.c
 *
 * Created: 4/19/2019 11:19:47 PM
 * Author : perezr1
 */ 

/*////////////////////////Include Library /////////////////////////////////////////*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*////////////////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////Function Prototype////////////////////////////////*/
void adc_int(void);
/*///////////////////////////////////////////////////////////////////////////////*/

/*////////////////////////////////// Variables ///////////////////////////////////*/
volatile int status_control = 0; // if set to 1, the motor is turned off
volatile unsigned int speed_control; // variable used to control delay
/*///////////////////////////////////////////////////////////////////////////////*/


int main(void)
{
/*/////////////////////////////// Initializations ///////////////////////////////////////////*/
	DDRB = 0x0F; //Enable output on all of the B pins
	PORTB = 0x00; // initialize to 0v
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // set CTC mode & prescaler of 8
	ICR1 = 62258;
/*//////////////////////////////////////////////////////////////////////////////////////////*/	
	adc_int(); // call function to initialize ADC
	
	while(1){
		while((ADCSRA&(1<<ADIF))==0); // wait for conversion
		if (ADC >= 820)
		{
			 status_control = 1;
		}
		if ((ADC < 820) && (ADC >= 617)) 
		{ 
			status_control = 0; 
			speed_control = 0x1869;
		}
		if ((ADC < 617) && (ADC >= 414)) 
		{ 
			status_control = 0; 
			speed_control = 0x124F;
		}
		if ((ADC < 414) && (ADC >= 211)) 
		{ 
			status_control = 0; 
			speed_control = 0x0C34;
		}
		if ((ADC < 211) && (ADC >= 000)) 
		{ 
			status_control = 0; 
			speed_control = 0x061A;
		}
			
		OCR1A = speed_control; // set OCR1A to the determined speed
		TCNT1 = 0x00; // reset timer
		// if the status is 1, then the motor will be OFF. If the status is 0 then the motor will be on and will run a step with a delay.
		if(status_control == 0)
		{
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0x09;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0x03;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0X06;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0X0C;
			TIFR1 |= (1<<OCF1A);
		}
	}
}
/*///////////////////////////////// Function ///////////////////////////////////////////////////*/	
void adc_int(void)
{
	ADMUX = (0<<REFS1)| // Reference Selection Bits
	(1<<REFS0)| // AVcc-external cap at	AREF
	(0<<ADLAR)| // ADC Left Adjust Result
	(0<<MUX3)|
	(0<<MUX2)| // ANalogChannel	Selection Bits
	(0<<MUX1)| // ADC0 (PC0)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)| //ADC Enable
	(1<<ADSC)| // ADC Start Conversion
	(1<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)| // ADC Interrupt	Flag
	(1<<ADIE)| // ADC Interrupt	Enable
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(1<<ADPS1)|
	(1<<ADPS0);
}
/*//////////////////////////////////////////////////////////////////////////////////////////*/	

