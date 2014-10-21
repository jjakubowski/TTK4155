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
#include "can.h"
#include "menu.h"

#include <util/delay.h>


can_message_t message_rx;
can_message_t message_tx;

uint8_t Done_flag, go_on;
uint8_t status; // move to int0

int main(void)
{
	
	uint8_t menu_level;	
	
	DDRC |= (1<<PC0); //set pin as an output  blinking led purpose
	USART_Init(MY_UBRR);
	
	

	sei(); // global enable interrupts (set I bit in  SREG)
	
	
	fdevopen(&USART_Transmit, 0);      
	
	ExtMemInit();	
	
	SRAM_test();
	OledInit();
	
	Done_flag=0;go_on=0;
	
	
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
	
	CanInit();
	PORTB|=(1<<PB1); //pullup
	menu_level=0;
	
	JoystickCalibrate();
	
	struct JoystickOutput Joy;
	
	uint8_t a,b,i;

		
	message_tx.id= 0x0A;
	message_tx.length =2;
	
	

	
	
    while(1)
    { 
		
		_delay_ms(1000);
		JoystickRead(&Joy);
		message_tx.data[0] =Joy.JoyAnalogOut.X_axis;
		message_tx.data[1] =Joy.JoyAnalogOut.Y_axis;
		
		CanSendMsg(&message_tx,2);
		
		printf("X axis - %4d%% ",(int8_t) Joy.JoyAnalogOut.X_axis);
		printf("Y axis - %4d%% \r\n",(int8_t) Joy.JoyAnalogOut.Y_axis);
		//
		
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
		//if(Done_flag)
		//{
			//printf("id - %x ",message_rx.id);
			//printf("length - %x ",message_rx.length);
			//printf("d1 %x ",message_rx.data[0]);
			//printf("d2 %x \r\n",message_rx.data[1]);
			//printf("d3 %x \r\n",message_rx.data[2]);
			//printf("d4 %x \r\n",message_rx.data[3]);
			//
			//Done_flag=0;
			//
					//
		//}
		//
		//
		
			
		
	//	_delay_ms(500); //refreshing period
    }
}



ISR(INT0_vect)
{
	
	status = MCPstatus();

	if(status & (1<<1)) CanReceiveMsg(&message_rx,1);
	else if(status & (1<<0)) CanReceiveMsg(&message_rx,0);
	Done_flag=1;
	status = MCPstatus();
}


ISR(BADISR_vect)
{

}
