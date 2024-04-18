#include "gpio.h"

void button_init()
{
    GPIO->PIN_CNF[13] = (3 << 2);
}