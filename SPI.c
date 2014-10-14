/*
 * SPI.c
 *
 * Created: 01.10.2014 12:31:19
 *  Author: milorads
 */

#include "SPI.h"

uint8_t SPIreceive(void){

	SPDR = 0xAA;			// a dummy byte
	while(!(SPSR&(1<<SPIF)));//wait for reception
	return SPDR;

}

void SPIinit(void){

	
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);				//MOSI, SCK is output, SS output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	//SPI enable, Master, clk rate fclk/16
	//MSB transmitted first, SPI interrupt disabled, Sampling on the first clk rising edge, 

}


void DeselectSlave(void)
{
	
	PORTB |= (1<<PB4);
}

void SelectSlave(void)
{
	
	PORTB &= ~(1<<PB4);
}

void SPIsend(uint8_t Data) {

	SPDR = Data;				//start conversion
	while(!(SPSR&(1<<SPIF)));	//wait for transmission to complete 

}