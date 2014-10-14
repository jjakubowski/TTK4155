/*
 * SRAMtest.c
 *
 * Created: 09.09.2014 13:21:44
 *  Author: majapo
 */ 

#include "SRAMtest.h"
#include "stdlib.h"

void SRAM_test(void)
{
	volatile char *ext_ram= (char *) 0x1800; // volatile--cannot be changed by software, for compiler
	//Start address for the SRAM
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;
	printf("Starting SRAM test...\r\n");
	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
	}
	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		if (ext_ram[i] != testvalue
		) {
			printf("SRAM error (read phase): ext_ram[%d] = %02X (should be%02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in readphase\r\n", werrors, rerrors);
}

