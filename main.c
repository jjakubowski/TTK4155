/*
 * main.c
 *
 * Created: 11.10.2014 16:01:02
 *  Author: milorads
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>


#include "USART.h"
#include "SRAMtest.h"
#include "ExtMem.h"
#include "ExtInt.h"
#include "Adc.h"
#include "SliderJoystick.h"
#include "Oled.h"
#include "SPI.h"
#include "MCP.h"
#include "menu.h"

#include <util/delay.h>

int main(void)
{
	
	uint8_t menu_level;	
	
	DDRC |= (1<<PC0); //set pin as an output  blinking led purpose
	USART_Init(MY_UBRR);
	
	
	//ExtIntInit();
	//sei(); // global enable interrupts (set I bit in  SREG)
	
	
	fdevopen(&USART_Transmit, 0);      
	
	ExtMemInit();	
	
	SRAM_test();
	OledInit();
	
	
	
	/*OledClearDisplay();
	OledPrintCharacter('X');
	OledGoto(1,0);
	OledPrintCharacter('Y');*/
	//OledGotoLine(7);
	//OledPrintString("hello");
	
	/*int t = 1024;
	t=10;
	while(t > 0) {
	OledPrintCharacter('A'); t--;}*/
	
	MenuInit();
	PORTB|=(1<<PB1); //pullup
	menu_level=0;
	
	JoystickCalibrate();
	
	struct JoystickOutput Joy;
	
	uint8_t a,b;
	
	
	MCPinit();
	
	a = MCPread(0x0f);
	printf("%x \n",a);
	_delay_ms(500);
	a = MCPread(0x0f);
	printf("%x \n",a);
	MCPrequest(0x81);
	
	/*MCPloadTX(0xb2, 0x40);
	a = MCPreadRX(0x90);
	
	MCPloadTX(0xc8, 0x40);
	b = MCPreadRX(0x90);
	
	printf("%x, %x \n", a, b);*/
	
    while(1)
    { 
		
		MCPwrite(0xb2, 0x31);
		
		a = MCPread(0x61);
		
		printf("%x \r \n",a);
		_delay_ms(500);
		
		
		/*uint8_t direction;

		JoystickRead(&Joy);
		
		
		printf("X axis - %4d%% ",(int8_t) Joy.JoyAnalogOut.X_axis);
		printf("Y axis - %4d%% ",(int8_t) Joy.JoyAnalogOut.Y_axis);
		direction = Joy.JoystickDigitalOut;
		if(direction == NEUTRAL) printf("Neutral ");
		else if(direction == RIGHT) printf("Right   ");
		else if(direction == LEFT) printf("Left    ");
		else if(direction == UP) printf("Up      ");
		else if(direction == DOWN) printf("Down    ");
		
		
		printf("Slider left - %3d ",SliderRead(LEFT));
		printf("Slider Right - %3d",SliderRead(RIGHT));
		
		printf("\r"); //
		
		//direction = Joy.JoystickDigitalOut;
		if(menu_level == 0){
			if(direction == DOWN) { if (menupointer==7) menupointer=0; else menupointer+=1; }
			else if(direction == UP) { if (menupointer==0) menupointer=7; menupointer-=1;}
		}
		
		
		
		if(!(PINB &&(1<<PB1))) 
		{
			_delay_ms(30); //wait for debounce
			
			if(!(PINB &&(1<<PB1)))
			{
			if (menu_level == 0) menu_level = 1;
			else menu_level = 0;
			}
		}
		if (menu_level==1) ShowChoice();
		else ShowMenu();
		*/
		
		_delay_ms(100); //refreshing period
    }
}