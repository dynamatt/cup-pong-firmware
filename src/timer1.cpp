#include <stdint.h>
#include "timer1.h"
#include "timer.h"

TimerOne Timer1;              // preinstantiate

unsigned short TimerOne::pwmPeriod = 0;
unsigned char TimerOne::clockSelectBits = 0;
void (*TimerOne::isrCallback)() = TimerOne::isrDefaultUnused;

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER1_COMPA_vect)
{
  Timer1.isrCallback();
}


void TimerOne::isrDefaultUnused()
{
}

void Timer_initialize(uint64_t microseconds)
{
  Timer1.initialize(microseconds);
}

void Timer_start()
{
  Timer1.start();
}

void Timer_stop()
{
  Timer1.stop();
}

void Timer_attachInterrupt(void (*isr)())
{
  Timer1.attachInterrupt(isr);
}