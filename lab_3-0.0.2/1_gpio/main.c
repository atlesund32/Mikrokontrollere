#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS *)0x50000000)
#define btn1 13
#define btn2 14
#define led1 17
#define led2 18
#define led3 19
#define led4 20

typedef struct
{
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main()
{
	// Configure LED Matrix
	for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[btn1] = (3 << 2);
	GPIO->PIN_CNF[btn2] = (3 << 2);

	int sleep = 0;
	while (1)
	{

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13)))
		{
			GPIO->OUTCLR = (1 << 17);
			GPIO->OUTCLR = (1 << 18);
			GPIO->OUTCLR = (1 << 19);
			GPIO->OUTCLR = (1 << 20);
		}
		if (!(GPIO->IN & (1 << 14)))
		{
			GPIO->OUTSET = (1 << 17);
			GPIO->OUTSET = (1 << 18);
			GPIO->OUTSET = (1 << 19);
			GPIO->OUTSET = (1 << 20);
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while (--sleep)
			; // Delay
	}
	return 0;
}
