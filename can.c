#include "Can.h"
#include "mcp.h"
#include "Spi.h"
#include <avr/io.h>


uint8_t CanInit(void)
{

	uint8_t value;

	SPIinit(); MCPreset();

	value = MCPread(MCP_CANSTAT);

	if((value & MODE_MASK) != MODE_CONFIG)
	{
		printf("Eror - MCP2515 NOT in config mode after rst! \n\r");
		return -1;
	}
	MCPmodify(MODE_LOOPBACK, MODE_MASK, MCP_CANCTRL);
	DeselectSlave();	//deselect MCP


	return 0;
}

void CanSendMsg(can_message_t* message)
{
	MCPwrite(,MCP_TXB0CTRL);

}
