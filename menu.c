#include "menu.h"
#include "Oled.h"

char menu[8][30]={"  Position1","  Position2","  Position3","  Position4","  Position5","  Position6","  Position7","  Position8"};

void ShowMenu(void)
{
	int i;
	OledClearDisplay();
	for(i=0;i<8;i++)
	{
	OledGotoLine(i);
	OledPrintString(menu[i]);
	
	}
	ShowMenuPointer();	
}


void PrintPointer(void)
{
	OledWriteData(0x3E);
	OledWriteData(0x1C);
	OledWriteData(0x08);
}

void ShowMenuPointer(void)
{
	OledGoto(menupointer,0);
	PrintPointer();
}

void MenuInit(void)
{
	OledClearDisplay();
	menupointer=0;
	ShowMenu();
	
}

void ShowChoice()
{
	OledClearDisplay();
	OledGotoLine(menupointer);
	OledPrintString("This is your choice - ");
	OledPrintCharacter(menupointer+1+48);
}