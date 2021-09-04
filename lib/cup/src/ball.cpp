#include <stdint.h>
#include "ball.h"
#include "io.h"

uint8_t notificationPending = 0;
uint8_t notificationComplete = 0;
uint16_t threshold;

void BallDetector_initialise(uint16_t thresh)
{
    threshold = thresh;
    IO_initialise();
}

bool BallDetector_isBallDetected(uint16_t *adc)
{
    // turn on the IR transmitter
    IO_enableTransmitter();

    // read the IR receiver value
    uint16_t sensorValue = IO_readReceiver();
    *adc = sensorValue;

    // turn off the IR transmitter
    IO_disableTransmitter();

    if (sensorValue <= threshold && notificationPending == 0)
    {
        notificationPending = 1;
    }
    else if (sensorValue > threshold)
    {
        notificationPending = 0;
        notificationComplete = 0;
    }

    if (notificationPending != 0 && notificationComplete == 0)
    {
        notificationComplete = 1;
        return true;
    }
    
    return false;
}