#include <stdint.h>
#include "timer.h"

void (*isrCallback)();
uint64_t timer_period;
uint64_t time;
bool is_enabled;

void Timer_initialize(uint64_t period)
{
    time = 0;
    timer_period = period;
}

void Timer_start()
{
    is_enabled = true;
}

void Timer_stop()
{
    is_enabled = false;
}

void Timer_attachInterrupt(void (*isr)())
{
    isrCallback = isr;
}

void MockTimer_tick()
{
    if (is_enabled)
    {
        time += timer_period;
        isrCallback();
    }
}