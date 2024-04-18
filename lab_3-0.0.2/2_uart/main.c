#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <sys/types.h> // For ssize_t

ssize_t _write(int fd, const void *buf, size_t count)
{
    char *letter = (char *)(buf);
    for (int i = 0; i < count; i++)
    {
        uart_send(*letter);
        letter++;
    }
    return count;
}

int main()
{
    uart_init();
    button_init();
    led_init();
    int sleep = 0;
    int lightOn = 1;

    while (1)
    {
        /* Check if button 1 is pressed;
         * turn on LED matrix if it is. */
        if (!(GPIO->IN & (1 << 13)))
        {
            uart_send('A');
        }

        if (!(GPIO->IN & (1 << 14)))
        {
            uart_send('B');
        }

        if (uart_read() != '\0')
        {
            if (lightOn)
            {
                for (int i = 17; i < 21; i++)
                {
                    // Bitwise OR-ing, safer
                    GPIO->OUTSET |= (1 << i);
                    lightOn = 0;
                }
            }
            else
            {
                for (int i = 17; i < 21; i++)
                {
                    GPIO->OUTCLR |= (1 << i);
                    lightOn = 1;
                }
            }
        }

        /* Check if button 2 is pressed;
         * turn off LED matrix if it is. */

        sleep = 10000;
        while (--sleep)
            ; // Delay

        iprintf("The average grade in TTK%d was in %d was: %c\n\r", 4235, 2022, 'B');
    }
    return 0;
}