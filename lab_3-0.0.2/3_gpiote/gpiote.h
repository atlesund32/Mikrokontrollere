#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG *)0x40006000)

typedef struct
{
	// Tasks
	volatile uint32_t OUT[5];
	// Events
	volatile uint32_t RESERVED0[59];
	volatile uint32_t IN[5];
	volatile uint32_t RESERVED1[123];
	// volatile uint32_t PORT;
	//  Registers
	// volatile uint32_t RESERVED2[96];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED3[129];
	volatile uint32_t CONFIG[5];
} NRF_GPIOTE_REG;

#endif
