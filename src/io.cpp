#include <Arduino.h>
#include "cup.h"
#include "io.h"

void IO_initialise() {
    pinMode(RX_PIN, INPUT);
    pinMode(TX_PIN, OUTPUT);
    analogReference(DEFAULT);
}

uint16_t IO_readReceiver() {
    return analogRead(RX_PIN);
}

void IO_enableTransmitter() {
    digitalWrite(TX_PIN, HIGH);
}

void IO_disableTransmitter() {
    digitalWrite(TX_PIN, LOW);
}
