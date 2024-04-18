#include "gpiote.h"
#include "gpio.h"

void gpiote_init()
{
    // Konfigurerer kanal 0
    // GPIOTE->CONFIG[CHANNEL] = Mode | (GPIO PIN SELECT) | (POLARITY);
    //  13 for knapp
    //  2 gir HiToLo

    // KNAPP
    GPIOTE->CONFIG[0] = 1 | (13 << 8) | (2 << 16);

    GPIOTE->CONFIG[1] = 3 | (17 << 8) | (3 << 16) | (1 << 20);

    GPIOTE->CONFIG[2] = 3 | (18 << 8) | (3 << 16) | (1 << 20);

    GPIOTE->CONFIG[3] = 3 | (19 << 8) | (3 << 16) | (1 << 20);

    GPIOTE->CONFIG[4] = 3 | (20 << 8) | (3 << 16) | (1 << 20);
}
