#include "timer.h"

TimerOne Timer1;              // preinstatiate

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
