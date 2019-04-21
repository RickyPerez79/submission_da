/*
 * DA_4B_Task_2.c
 *
 * Created: 4/19/2019 11:21:06 PM
 * Author : perezr1
 */ 

/*///////////////////////////// Include Library /////////////////////////////////////*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*//////////////////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////Function Prototype////////////////////////////////*/
void adc_int(void);
/*///////////////////////////////////////////////////////////////////////////////*/

/*////////////////////////////// Variable /////////////////////////////////////////*/
int check_value = 0;
/*//////////////////////////////////////////////////////////////////////////////////*/

int main(void)
{
/*/////////////////////////////// Initializations /////////////////////////////////////////////////////////////////////////////*/
	DDRB = 0xFF; //DDRB as an output
	DDRD = 0xFF;
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); // Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM (inverting mode)
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); // set to Fast PWM mode & 64 prescaler
	ICR1=4999;
	adc_int(); // call function to initialize ADC
/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	while (1)
	{
		ADCSRA |= (1 << ADSC); // start conversion
		while((ADCSRA & (1 << ADIF))== 0);
		check_value = ADCH; // temp value
		
		if(check_value == 0) // the minimum value
		{
			OCR1A = 0; //turn 0 degrees
			_delay_ms(1000);
		}
		if(check_value == 255) // the max value of the potentiometer
		{
			OCR1A = 535;  //servo motor will turn 180 degrees
			_delay_ms(1000);
		}
	}
}

/*///////////////////////////////// Function ///////////////////////////////////////////////////*/	
void adc_int(void)
{
	ADMUX = (0<<REFS1)| // Reference Selection Bits
	(1<<REFS0)| // AVcc-external cap at	AREF
	(1<<ADLAR)| // ADC Left Adjust Result
	(0<<MUX3)|
	(0<<MUX2)| // ANalogChannel	Selection Bits
	(0<<MUX1)| // ADC0 (PC0)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)| //ADC Enable
	(0<<ADSC)|
	(1<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)| 
	(0<<ADIE)|
	(1<<ADPS2)| // ADC Prescaler Select Bits (64)
	(1<<ADPS1)|
	(0<<ADPS0);
}
/*//////////////////////////////////////////////////////////////////////////////////////////*/	