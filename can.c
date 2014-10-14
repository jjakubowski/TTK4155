#include "Can.h"
#include "mcp.h"
#include "Spi.h"
#include <avr/io.h>

#define BUFFER_OFFSET(REGISTER,BUFFER_NUMBER) (REGISTER + BUFFER_NUMBER*0x10)


uint8_t CanInit(void)
{

	uint8_t value;

	SPIinit(); MCPreset();
	PORTD|=(1<<PD2); //pullup for interrupt

	value = MCPread(MCP_CANSTAT);

	if((value & MODE_MASK) != MODE_CONFIG)
	{
		printf("Eror - MCP2515 NOT in config mode after rst! \n\r");
		return -1;
	}
	MCPmodify(MODE_LOOPBACK, MODE_MASK, MCP_CANCTRL);
	
	MCPwrite(MCP_RX_INT, MCP_CANINTE);
	DeselectSlave();	//deselect MCP


	return 0;
}

void CanSendMsg(can_message_t* message,uint8_t buffer,uint8_t buffer_priority)
{
	uint8_t block[] = {(uint8_t) (message->id >> 3), (uint8_t) (message->id <<5), 0x00, 0x00, 2};
	MCPwrite(buffer_priority,BUFFER_OFFSET(MCP_TXB0CTRL, buffer));
	MCPloadTX(block, MCP_LOAD_TX0+buffer*2, NONE);
	
	MCPloadTX(message->data, MCP_LOAD_TX0+buffer*2, ONLY_DATA);
	
	//MCPrequest(MCP_RTS_TX2 ); // add req for rest buffers
}


void CanReceiveMsg(can_message_t *message,uint8_t buffer)
{
	
	uint8_t temp[13];
	int i;
	
	
	MCPreadRX(temp, MCP_READ_RX0+buffer*4,NONE);
	
	message->id = (temp[0]<<3) | (temp[1] >>5 );
	message->length = (temp[4] & 0x0F );
	
	for(i=0;i<message->length;i++)
	{
		message->data[i] = temp[i+5];	
	}
	
	
	
	
	
}