#include "uart.h"
#include "gpio.h"
#include <stdint.h>

#define UART ((NRF_UART_REG *)0x40002000)
#define output 8
#define input 6

// Initialisere de nødvendige GPIO-pinnene som input/output
void uart_init()
{
    // Configure pins
    GPIO->PIN_CNF[output] = 1;
    GPIO->PIN_CNF[input] = 0;

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->PSELTXD = ~0;
    UART->PSELRXD = ~0;

    UART->BAUDRATE = 0x00275000; // baudrate på 9600

    UART->ENABLE = 4;

    UART->TASKS_STARTRX = 1;
}

// Ta imot en enkel bokstav, for å sende den over til datamaskinen
void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (!(UART->EVENTS_TDXRDY))
    {
    }
    UART->EVENTS_TDXRDY = 0; // cleare interruptet som genereres når man er ferdig å sende

    UART->TASKS_STOPTX = 1;
}

//--------------------------------------RIKTIG FREM HIT------------------------------------------------

// Lese en bokstav fra datamaskinen og returnere den
char uart_read()
{
    char letter;
    if (UART->EVENTS_RXDRDY)
    {
        UART->EVENTS_RXDRDY = 0;
        // letter = UART->TXD;
        letter = UART->RXD;
        return letter;
    }
    return '\0';
}