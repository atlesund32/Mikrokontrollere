#include "uart.h"
#include "gpio.h"
#include <stdint.h>

#define UART ((NRF_UART_REG *)0x40002000)
#define output 6
#define input 8

typedef struct
{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TDXRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

// Initialisere de nødvendige GPIO-pinnene som input/output
void uart_init()
{
    // Configure pins
    GPIO->PIN_CNF[output] = 1;
    GPIO->PIN_CNF[input] = 1;

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->PSELTXD = 0xFFFFFFFF;
    UART->PSELRXD = 0xFFFFFFFF;

    UART->BAUDRATE = 0x00275000; // baudrate på 9600

    UART->ENABLE = 4;

    UART->TASKS_STARTRX = 1;
}

// Ta imot en enkel bokstav, for å sende den over til datamaskinen
void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (UART->EVENTS_RXDRDY != 1)
    {
    }
    UART->EVENTS_TDXRDY = 0; // cleare interruptet som genereres når man er ferdig å sende

    UART->TASKS_STOPTX = 1;
}

//--------------------------------------RIKTIG FREM HIT------------------------------------------------

// Lese en bokstav fra datamaskinen og returnere den
void uart_read()
{
    UART->TASKS_STARTRX = 1;

    char letter;
    if (!UART->EVENTS_RXDRDY)
    {
        UART->RXD = '\0';
    }
    else if (UART->EVENTS_RXDRDY)
    {
        letter = UART->TXD;
    }

    UART->RXD = letter;

    UART->TASKS_STOPRX;
}