

/*
 * USART.c
 *
 * Created: 09.09.2014 13:18:31
 *  Author: majapo
 */ 

#include "USART.h"

void USART_Init(unsigned int baud )
{
	/*
	Set baud rate
	*/
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/*
	Enable receiver and transmitter
	*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/*
	Set frame format: 8data, 2stop bit
	*/
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}


void USART_Transmit(unsigned char data )
{
	/*
	Wait for empty transmit buffer
	*/
	while
	( !( UCSR0A & (1<<UDRE0)) )
	;
	/*
	Put data into buffer, sends the data
	*/
	UDR0 = data;
}



unsigned char USART_Receive(void )
{
	/*
	Wait for data to be received
	*/
	while( !(UCSR0A & (1<<RXC0)) )
	;
	/*
	Get and return received data from buffer
	*/
	return UDR0;
}
