/*
 * ExtInt.c
 *
 * Created: 09.09.2014 13:29:13
 *  Author: majapo
 */ 
#include "ExtInt.h"



void ExtIntInit(void)
	{
	MCUCR|=(1<<ISC01);
	GICR|=(1<<INT0);	
	}
	
	
