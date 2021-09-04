#include "io.h"

uint16_t analogue_value;
uint8_t transmitter_enabled;

void IO_initialise() {
}

uint16_t IO_readReceiver() {
    return analogue_value;
}

void IO_enableTransmitter() {
    transmitter_enabled = 1;
}

void IO_disableTransmitter() {
    transmitter_enabled = 0;
}
