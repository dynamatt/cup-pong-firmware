#include <unity.h>
#include <stdbool.h>
#include "ball.h"
#include "io.h"

extern uint16_t analogue_value;
extern uint8_t transmitter_enabled;

void test_ball_detection()
{
    uint16_t adc;
    bool detected;

    BallDetector_initialise(10);

    // no detection
    analogue_value = 11;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(11, adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "No detection");

    // ball first detected
    analogue_value = 10;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(10, adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "Ball first detected");

    // don't detect again yet
    analogue_value = 9;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(9, adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "Ball still present");

    // ball gone
    analogue_value = 20;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(20, adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "Ball gone");

    // still gone
    analogue_value = 20;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(20, adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "Still gone");

    // detect again
    analogue_value = 8;
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(8, adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "Detect again");

    // stay low for a few cycles
    for (int i=0; i<10; i++) {
        analogue_value = i;
        detected = BallDetector_isBallDetected(&adc);
        TEST_ASSERT_EQUAL(i, adc);
        TEST_ASSERT_FALSE_MESSAGE(detected, "Staying low");
    }

    // stay high for a few cycles
    for (int i=20; i<30; i++) {
        analogue_value = i;
        detected = BallDetector_isBallDetected(&adc);
        TEST_ASSERT_EQUAL(i, adc);
        TEST_ASSERT_FALSE_MESSAGE(detected, "Staying high");
    }

    // set a new threshold
    BallDetector_initialise(40);
    detected = BallDetector_isBallDetected(&adc);
    TEST_ASSERT_EQUAL(29, adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "New threshold");
}


int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_ball_detection);
    UNITY_END();
}