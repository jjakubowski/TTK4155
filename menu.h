
#ifndef MENU_H_
#define MENU_H_

#include <avr/io.h>

void ShowMenu(void);
void ShowMenuPointer(void);
void PrintPointer(void);
void MenuInit(void);
void ShowChoice(void);

uint8_t menupointer;


#endif /* MENU_H_ */