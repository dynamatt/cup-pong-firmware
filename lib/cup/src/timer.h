#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void Timer_initialize(uint64_t microseconds);
void Timer_start();
void Timer_stop();
void Timer_attachInterrupt(void (*isr)());

#endif