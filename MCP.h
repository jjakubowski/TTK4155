/*
 * MCP.h
 *
 * Created: 01.10.2014 14:10:51
 *  Author: milorads
 */

#include <stdio.h>
 
#ifndef MCP_H_
#define MCP_H_

void MCPinit(void);

void MCPmodify(uint8_t Data, uint8_t Mask, uint8_t Address);

uint8_t MCPstatus(void);

void MCPrequest(uint8_t Address);

void MCPloadTX(uint8_t Data, uint8_t Address);

void MCPwrite(uint8_t Data, uint8_t Address);

uint8_t MCPread(uint8_t Address);

uint8_t MCPreadRX(uint8_t Address);

void MCPreset(void);

#endif