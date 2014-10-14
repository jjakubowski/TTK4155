/*
 * MCP.c
 *
 * Created: 01.10.2014 14:11:12
 *  Author: milorads
 */

#include <avr/io.h>

#include "MCP.h"
#include "SPI.h"

void MCPinit(void){

	//CANCTRL: 0x0F
	//CANSTAT: 0x0E
	//Call this after reset
	//Configure here: CNF1, CNF2, CNF3, TXRTSCTRL, filter regs, mask regs
	SPIinit(); MCPreset();
	//SelectSlave();	//selectMCP
	PORTB &= ~(1<<PB4);
	MCPwrite(0x46, 0x0f);
	//send write command
	//send address 0x0f
	//configure CANCTRL: loop back mode, clk enable, fclk/4
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP
}


void MCPmodify(uint8_t Data, uint8_t Mask, uint8_t Address){

	//SelectSlave();	//selectMCP
	PORTB &= ~(1<<PB4);
	SPIsend(0x05);		//send bit modify command
	SPIsend(Address);	//send register address
	SPIsend(Mask);		//send mask
	SPIsend(Data);		//send data
	//DeselectSlave();	//deselect MCP
	PORTB |= (1<<PB4);

}

uint8_t MCPstatus(void){

	uint8_t Byte;
	//SelectSlave();	//selectMCP
	PORTB &= ~(1<<PB4);
	SPIsend(0xA0);		//send read statud command
	Byte = SPIreceive();		//send data
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP
	return Byte;

}

void MCPrequest(uint8_t Address){

	PORTB &= ~(1<<PB4);
	//SelectSlave();	//selectMCP
	SPIsend(Address);	//define which buffers are enabled to transmit
						// 0x80 for non
						// 0x81 for T0
						// 0x82 for T1
						// 0x84 for T2
	//DeselectSlave();	//deselect MCP
	PORTB |= (1<<PB4);

}

void MCPloadTX(uint8_t Data, uint8_t Address){

	PORTB &= ~(1<<PB4);
	//SelectSlave();	//selectMCP
	SPIsend(Address);	//send write address:
						// 0x40 for 0x31
						// 0x41 for 0x32
						// 0x42 for 0x41
						// 0x43 for 0x46
						// 0x44 for 0x51
						// 0x45 for 0x56
	SPIsend(Data);		//send data
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP

}

void MCPwrite(uint8_t Data, uint8_t Address){

	PORTB &= ~(1<<PB4);
	//SelectSlave();	//selectMCP
	SPIsend(0x02);		//send write command
	SPIsend(Address);	//send write address
	SPIsend(Data);		//send data
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP

}

uint8_t MCPreadRX(uint8_t Address){

	uint8_t Byte;
	//SelectSlave();	//selectMCP
	PORTB &= ~(1<<PB4);
	SPIsend(Address);	//send address:0x90 for 0x61 or 0x91 for 0x66 or 0x92 for 0x71 or 0x93 for 0x76
	Byte = SPIreceive();//read byte
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP
	return Byte;

}

uint8_t MCPread(uint8_t Address){

	uint8_t Byte;
	PORTB &= ~(1<<PB4);
	//SelectSlave();	//selectMCP
	SPIsend(0x03);		//send reading command
	SPIsend(Address);	//send address
	Byte = SPIreceive();//read byte
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP
	return Byte;

}

void MCPreset(void){

	PORTB &= ~(1<<PB4);
	//SelectSlave();	//select MCP 
	SPIsend(0xC0);		//send RESET vector
	PORTB |= (1<<PB4);
	//DeselectSlave();	//deselect MCP

}