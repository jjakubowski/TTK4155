/*
 * ExtMem.c
 *
 * Created: 09.09.2014 13:23:49
 *  Author: majapo
 */ 


#include "ExtMem.h"



void ExtMemInit(void)
{
	
	//EMCUCR |= (0<<SRW11) | (1<<SRW10);
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMBK);
	
	SFIOR |= (1<<XMM2);
	//DDRA = 0xFF;
}