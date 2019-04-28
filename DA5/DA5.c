#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
unsigned int ADC_TEMP;
// Set up UART for printf();
#ifndef BAUD
#define BAUD 9600
#endif
#include "STDIO_UART.h"
// Include nRF24L01+ library
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include "spi.h"
void print_config(void);
void ADC_INIT(void);
void READ_ADC(void);
// Used in IRQ ISR
volatile bool message_received = false;
volatile bool status = false;
int main(void){
	// Set cliche message to send (message cannot exceed 32 characters)
	char tx_message[32]; // Define string array
	char *tx_ptr = tx_message;
	strcpy(tx_message,"Hi :) !"); // Copy string into array
	// Initialize UART
	uart_init();
	// Initialize nRF24L01+ and print configuration info
	nrf24_init();
	print_config();
	ADC_INIT();
	// Start listening to incoming messages
	printf("start listening\n");
	nrf24_start_listening();
	printf("Done listening\n");
	ADC_TEMP = 0;
	while (1){
		//printf("outside if\n");
		READ_ADC();
		tx_ptr = tx_message;
		//sprintf(tx_ptr, "%d", ADC_TEMP);
		nrf24_send_message(tx_ptr);
		delay_ms(100);
		//continue;
		//;
		if (message_received){
			printf("inside if condition\n");
			// Message received, print it
			message_received = false;
			printf("Received message: %s\n",nrf24_read_message());
			// Send message as response
			_delay_ms(500);
			status = nrf24_send_message(tx_message);
			if (status == true) printf("Message sent successfully\n");
		}
	}
}
// Interrupt on IRQ pin
ISR(INT0_vect) {
	message_received = true;
}
void ADC_INIT(void){
	ADMUX = (0<<REFS1)| // Reference Selection Bits
	(1<<REFS0)| // AVcc - external cap at AREF
	(0<<ADLAR)| // ADC Left Adjust Result
	(1<<MUX2)| // ANalog Channel Selection Bits
	(0<<MUX1)| //
	(0<<MUX0);
	ADCSRA = (1<<ADEN)| // ADC ENable
	(0<<ADSC)| // ADC Start Conversion
	(0<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)| // ADC Interrupt Flag
	(0<<ADIE)| // ADC Interrupt Enable
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
	// Timer/Counter1 Interrupt Mask Register
	TIMSK1 |= (1<<TOIE1); // enable overflow interrupt
	TCCR1B |= (1<<CS12)|(1<<CS10); // clock
	TCNT1 = 49911; //((16MHz/1024)*1)-1 = 15624
}
void READ_ADC(void) {
	unsigned char i =4;
	ADC_TEMP = 0; //initialize
	while (i--) {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		ADC_TEMP+= ADC;
		_delay_ms(50);
	}
	ADC_TEMP = ADC_TEMP/8 ; // Average
}
void print_config(void){
	uint8_t data;
	printf("Startup successful\n\n nRF24L01+ configured as:\n");
	printf("-------------------------------------------\n");
	nrf24_read(CONFIG,&data,1);
	printf("CONFIG 0x%02X\n",data);
	nrf24_read(EN_AA,&data,1);
	printf("EN_AA 0x%02X\n",data);
	nrf24_read(EN_RXADDR,&data,1);
	printf("EN_RXADDR 0x%02X\n",data);
	nrf24_read(SETUP_RETR,&data,1);
	printf("SETUP_RETR 0x%02X\n",data);
	nrf24_read(RF_CH,&data,1);
	printf("RF_CH 0x%02X\n",data);
	nrf24_read(RF_SETUP,&data,1);
	printf("RF_SETUP 0x%02X\n",data);
	nrf24_read(STATUS,&data,1);
	printf("STATUS 0x%02X\n",data);
	nrf24_read(FEATURE,&data,1);
	printf("FEATURE 0x%02X\n",data);
	printf("-------------------------------------------\n\n");
}
