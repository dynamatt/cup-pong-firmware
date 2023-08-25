#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "cup.h"
#include "animation.h"
#include "ball.h"
#include "leds.h"


#define BUFFER_SIZE 29

static DataPacket data;

static uint8_t buffer[BUFFER_SIZE];
static int buffer_index;


// method definitions
void requestEvent();
void receiveEvent(int bytes_received);


void initialiseWire()
{
    //uint8_t address = EEPROM.read(ADDR_I2C_SLAVE_ADDRESS);
    uint8_t address = I2C_SLAVE_ADDRESS;
    data.header = address;

    Wire.begin(address);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

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
        {
            uint8_t animation = buffer[2];
            AnimationController_setAnimation(animation, (uint8_t*)(buffer+3), length-1);
            break;
        }
        case SET_BALL_DETECTION_THRESHOLD:
        {
            uint8_t new_threshold = buffer[2];
            EEPROM.write(ADDR_BALL_DETECTION_THRESHOLD, new_threshold);
            BallDetector_setThreshold(new_threshold);
            break;
        }
    }

    buffer_index = 0;
}

void requestEvent()
{
    data.count++;
    BallDetector_isBallDetected(&data.min_adc, &data.max_adc);
    Wire.write((uint8_t*)&data, sizeof(DataPacket));
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
    BallDetector_setThreshold(EEPROM.read(ADDR_BALL_DETECTION_THRESHOLD));
    AnimationController_initialise(LED_REFRESH_INTERVAL_us);
    initialiseWire();

    data.header = I2C_SLAVE_ADDRESS;

}

void loop() 
{
    BallDetector_measure();
}
