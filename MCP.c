#include <avr/io.h>

#include "MCP.h"
#include "SPI.h"




void MCPmodify(uint8_t Data, uint8_t Mask, uint8_t Address){

	SelectSlave();	//selectMCP

	SPIsend(MCP_BITMOD);		//send bit modify command
	SPIsend(Address);	//send register address
	SPIsend(Mask);		//send mask
	SPIsend(Data);		//send data
	DeselectSlave();	//deselect MCP


}
/** @brief Function returning information abouut tx and rx functions
 *
 * @todo might be a good idea to add checking the repeated output
 *
 *
 *
 *
 */
uint8_t MCPstatus(void){

	uint8_t Byte;
	SelectSlave();	//selectMCP
	SPIsend(MCP_READ_STATUS);		//send read statud command
	Byte = SPIreceive();		//send data
	DeselectSlave();	//deselect MCP
	return Byte;

}

/**
 *
 * @param Transmit_buffer Choose buffer 0,1,2 or all
 *
 *
 */


void MCPrequest(uint8_t Transmit_buffer){

	SelectSlave();	//selectMCP
	SPIsend(Transmit_buffer);	//define which buffers are enabled to transmit

	DeselectSlave();	//deselect MCP


}

void MCPloadTX(uint8_t Data, uint8_t Buffer,uint8_t start_point){

	SelectSlave();	//selectMCP
	SPIsend( Buffer | ( start_point) );	//send write address
	SPIsend(Data);		//send data
	DeselectSlave();	//deselect MCP

}

void MCPwrite(uint8_t Data, uint8_t Address){

	SelectSlave();	//selectMCP
	SPIsend(MCP_WRITE);		//send write command
	SPIsend(Address);	//send write address
	SPIsend(Data);		//send data
	DeselectSlave();	//deselect MCP

}

uint8_t MCPreadRX(uint8_t Buffer,uint8_t start_point){

	uint8_t Byte;

	SelectSlave();	//selectMCP
	SPIsend(Buffer | ( start_point <<1));
	Byte = SPIreceive();//read byte
	DeselectSlave();	//deselect MCP
	return Byte;

}

uint8_t MCPread(uint8_t Address){

	uint8_t Byte;

	SelectSlave();	//selectMCP
	SPIsend(MCP_READ);		//send reading command
	SPIsend(Address);	//send address
	Byte = SPIreceive();//read byte
	DeselectSlave();	//deselect MCP
	return Byte;

}

void MCPreset(void){

	SelectSlave();	//select MCP
	SPIsend(MCP_RESET);		//send RESET vector
	DeselectSlave();	//deselect MCP

}
