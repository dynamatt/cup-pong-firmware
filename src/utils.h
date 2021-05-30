#include <Arduino.h>

static inline void delay_ms(long duration_ms) {
 unsigned long t = millis();
 while (millis() - t < duration_ms) {
   // do nothing
 }
}