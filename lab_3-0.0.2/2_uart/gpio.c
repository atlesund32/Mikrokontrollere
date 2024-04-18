#include "gpio.h"

#define btn1 13
#define btn2 14
#define led1 17
#define led2 18
#define led3 19
#define led4 20

void button_init(){
    // Configure buttons
	GPIO->PIN_CNF[btn1] = (3 << 2);
	GPIO->PIN_CNF[btn2] = (3 << 2);
}

void led_init(){
    for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
}