#include <Arduino.h>
#include "cup.h"
#include "ball.h"

uint8_t notificationPending = 0;
uint8_t notificationComplete = 0;

void BallDetector_initialise()
{
    pinMode(RX_PIN, INPUT);
    pinMode(TX_PIN, OUTPUT);
}

bool BallDetector_isBallDetected(uint16_t *adc)
{
    // turn on the IR transmitter
    digitalWrite(TX_PIN, HIGH);

    // read the IR receiver value
    uint16_t sensorValue = analogRead(RX_PIN);
    *adc = sensorValue;

    // turn off the IR transmitter
    digitalWrite(TX_PIN, LOW);

    if (sensorValue <= BALL_DETECTION_THRESHOLD && notificationPending == 0)
    {
        notificationPending = 1;
    }
    else if (sensorValue > BALL_DETECTION_THRESHOLD)
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