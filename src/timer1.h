#ifndef TIMER1_H
#define TIMER1_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER1_RESOLUTION 256UL  // Timer1 is 8 bit

class TimerOne
{

  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
      TCCR1 = _BV(CTC1);              //clear timer1 when it matches the value in OCR1C
      TIMSK |= _BV(OCIE1A);           //enable interrupt when OCR1A matches the timer value
      setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {   
      const unsigned long cycles = microseconds * ratio;
      if (cycles < TIMER1_RESOLUTION) {
        clockSelectBits = _BV(CS10);
        pwmPeriod = cycles;
      } else
      if (cycles < TIMER1_RESOLUTION * 2UL) {
        clockSelectBits = _BV(CS11);
        pwmPeriod = cycles / 2;
      } else
      if (cycles < TIMER1_RESOLUTION * 4UL) {
        clockSelectBits = _BV(CS11) | _BV(CS10);
        pwmPeriod = cycles / 4;
      } else
      if (cycles < TIMER1_RESOLUTION * 8UL) {
        clockSelectBits = _BV(CS12);
        pwmPeriod = cycles / 8;
      } else
      if (cycles < TIMER1_RESOLUTION * 16UL) {
        clockSelectBits = _BV(CS12) | _BV(CS10);
        pwmPeriod = cycles / 16;
      } else
      if (cycles < TIMER1_RESOLUTION * 32UL) {
        clockSelectBits = _BV(CS12) | _BV(CS11);
        pwmPeriod = cycles / 32;
      } else
      if (cycles < TIMER1_RESOLUTION * 64UL) {
        clockSelectBits = _BV(CS12) | _BV(CS11) | _BV(CS10);
        pwmPeriod = cycles / 64UL;
      } else
      if (cycles < TIMER1_RESOLUTION * 128UL) {
        clockSelectBits = _BV(CS13);
        pwmPeriod = cycles / 128;
      } else
      if (cycles < TIMER1_RESOLUTION * 256UL) {
        clockSelectBits = _BV(CS13) | _BV(CS10);
        pwmPeriod = cycles / 256;
      } else
      if (cycles < TIMER1_RESOLUTION * 512UL) {
        clockSelectBits = _BV(CS13) | _BV(CS11);
        pwmPeriod = cycles / 512;
      } else
      if (cycles < TIMER1_RESOLUTION * 1024UL) {
        clockSelectBits = _BV(CS13) | _BV(CS11) | _BV(CS10);
        pwmPeriod = cycles / 1024;
      } else
      if (cycles < TIMER1_RESOLUTION * 2048UL) {
        clockSelectBits = _BV(CS13) | _BV(CS12);
        pwmPeriod = cycles / 2048;
      } else
      if (cycles < TIMER1_RESOLUTION * 4096UL) {
        clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS10);
        pwmPeriod = cycles / 4096;
      } else
      if (cycles < TIMER1_RESOLUTION * 8192UL) {
        clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11);
        pwmPeriod = cycles / 8192;
      } else
      if (cycles < TIMER1_RESOLUTION * 16384UL) {
        clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
        pwmPeriod = cycles / 16384;
      } else {
        clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
        pwmPeriod = TIMER1_RESOLUTION - 1;
      }
      OCR1A = pwmPeriod;
      OCR1C = pwmPeriod;
      TCCR1 = _BV(CTC1) | clockSelectBits;
    }
  
    //****************************
    //  Run Control
    //****************************  
    void start() __attribute__((always_inline)) {
      TCCR1 = 0;
      TCNT1 = 0;    
      resume();
    }
    void stop() __attribute__((always_inline)) {
      TCCR1 = _BV(CTC1);
    }
    void restart() __attribute__((always_inline)) {
      start();
    }
    void resume() __attribute__((always_inline)) {
      TCCR1 = _BV(CTC1) | clockSelectBits;
    }
  
    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
      isrCallback = isr;
      TIMSK |= _BV(OCIE1A);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
      if(microseconds > 0) setPeriod(microseconds);
        attachInterrupt(isr);
      }
    void detachInterrupt() __attribute__((always_inline)) {
      //TIMSK = 0; // Timer 0 and Timer 1 both use TIMSK register so setting it to 0 will override settings for Timer1 as well
      TIMSK &= ~_BV(OCIE1A);
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;
    static const uint8_t ratio = (F_CPU)/ ( 1000000 );
    
};

extern TimerOne Timer1;

#endif
