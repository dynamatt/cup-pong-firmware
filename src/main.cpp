#include <Arduino.h>
#include <Wire.h>
#include "cup.h"
#include "animation.h"
#include "ball.h"
#include "leds.h"

#define BUFFER_SIZE 15

DataPacket data;

uint8_t buffer[BUFFER_SIZE];
int buffer_index;

void processCommand()
{
    if (buffer_index < 2) {
        // don't process until we have enough data to read length
        return;
    }

    command_t command = (command_t)buffer[0];
    uint8_t length = buffer[1];

    if (buffer_index < length + 2) {
        // don't process until we have enough data
        return;
    }

    switch (command) {
        case SET_ANIMATION:
            uint8_t animation = buffer[2];
            AnimationController_setAnimation(animation, (uint8_t*)(buffer+3), length-1);
            break;
    }

    buffer_index = 0;
}

void requestEvent()
{
    data.count++;
    Wire.write((uint8_t*)&data, sizeof(DataPacket));
    data.ballDetected = 0;
}

void receiveEvent(int bytes_received) 
{
    while (Wire.available()) {
        buffer[buffer_index] = Wire.read();
        buffer_index++;
    }
    
    processCommand();
}

void setup() 
{
    LedController_initialise();
    BallDetector_initialise();
    AnimationController_initialise(LED_REFRESH_INTERVAL_us);

    data.header = PACKET_HEADER;

    Wire.begin(I2C_SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop() 
{
    if (BallDetector_isBallDetected(&data.adc)) 
    {
      data.ballDetected = 1;
    }
}
