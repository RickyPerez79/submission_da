/************* Include Library/Header Files ************************************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c_master.h"
#include "uart.h"
#include "apds.h"
/*******************************************************************************/
FILE str_uart = FDEV_SETUP_STREAM(uart_putchar, NULL , _FDEV_SETUP_WRITE);
char results[256];

int main(void)
{
	uint16_t red = 0, green = 0, blue = 0;
	
	i2c_init();                             // initialize i2c
	init_UART();							// initialize uart
	stdout = &str_uart;
	apds_init(); 							// initialize apds-9960
	
 	_delay_ms(2000);
 /**************************** Begining AT commands ********************************************/
	printf("AT\r\n");
	
	_delay_ms(5000);
	printf("AT+CWMODE=1\r\n"); 
	
	_delay_ms(5000);
	printf("AT+CWJAP=\"Last_CPE301_Midterm\",\"CpE301!!!\"\r\n"); 
/************************************************************************************************/
    while (1) 
    {
		_delay_ms(5000);
		printf("AT+CIPMUX=0\r\n");
		
		_delay_ms(5000);
		printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
		
		_delay_ms(5000);
		readColor(&red, &green, &blue); // will read and update RGB colors
		printf("AT+CIPSEND=104\r\n");
	print out RGB colors and upload them to thingspeak
	// 
		printf("GET https://api.thingspeak.com/update?api_key=AUNLC6UQ6YFVDNTE&field1=%05u&field2=%05u&field3=%05u\r\n", red, green, blue); 
		
		_delay_ms(3000); // delay
    }
}


