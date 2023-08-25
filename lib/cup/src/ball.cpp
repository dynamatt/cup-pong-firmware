#include <limits.h>
#include <stdint.h>
#include "ball.h"
#include "io.h"

uint8_t notificationPending = 0;
uint8_t notificationComplete = 0;
uint16_t threshold;
uint16_t min_adc = UCHAR_MAX;
uint16_t max_adc = 0;

void BallDetector_initialise()
{
    IO_initialise();
}

void BallDetector_setThreshold(uint16_t thresh)
{
    threshold = thresh;
}

void BallDetector_measure()
{
    // turn on the IR transmitter
    IO_enableTransmitter();

    // read the IR receiver value
    uint16_t sensorValue = IO_readReceiver();
    if (sensorValue > max_adc)
    {
        max_adc = sensorValue;
    }
    if (sensorValue < min_adc)
    {
        min_adc = sensorValue;
    }

    // turn off the IR transmitter
    IO_disableTransmitter();
}

bool BallDetector_isBallDetected(uint16_t *min, uint16_t *max)
{
    *min = min_adc;
    *max = max_adc;

    bool detected = min_adc <= threshold;

    min_adc = USHRT_MAX;
    max_adc = 0;

    return detected;
}