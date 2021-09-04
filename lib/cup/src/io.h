#ifndef IO_H
#define IO_H

#include <stdint.h>

void IO_initialise();
uint16_t IO_readReceiver();
void IO_enableTransmitter();
void IO_disableTransmitter();

#endif