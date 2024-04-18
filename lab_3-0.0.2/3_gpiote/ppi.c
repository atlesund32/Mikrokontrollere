#include "ppi.h"
#include "gpiote.h"
// PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[4]);
// PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[0]);

PPI->PPI_CH[0].EEP = (uint32_t) & (GPIOTE->IN[]);   // Read GPIO port
PPI->PPI_CH[0].TEP = (uint32_t) & (GPIOTE->OUT[1]); // Write GPIO port
