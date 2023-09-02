#include <unity.h>
#include <stdbool.h>
#include "ball.h"
#include "io.h"

extern uint16_t analogue_value;
extern uint8_t transmitter_enabled;

void test_ball_detection()
{
    uint16_t min_adc;
    uint16_t max_adc;
    bool detected;

    BallDetector_initialise();
    BallDetector_setThreshold(10);

    // no detection
    analogue_value = 11;
    BallDetector_measure();
    analogue_value = 31;
    BallDetector_measure();
    analogue_value = 25;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(11, min_adc);
    TEST_ASSERT_EQUAL(31, max_adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "No detection");

    // min and max value are reset after check
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(255, min_adc);
    TEST_ASSERT_EQUAL(0, max_adc);

    // ball first detected
    analogue_value = 10;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(10, min_adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "Ball first detected");

    // // don't detect again yet
    analogue_value = 9;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(9, min_adc);
    // TEST_ASSERT_FALSE_MESSAGE(detected, "Ball still present");

    // ball gone
    analogue_value = 20;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(20, min_adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "Ball gone");

    // still gone
    analogue_value = 20;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(20, min_adc);
    TEST_ASSERT_FALSE_MESSAGE(detected, "Still gone");

    // detect again
    analogue_value = 8;
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(8, min_adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "Detect again");

    // stay low for a few cycles
    for (int i=0; i<10; i++) {
        analogue_value = i;
        BallDetector_measure();
        detected = BallDetector_isBallDetected(&min_adc, &max_adc);
        TEST_ASSERT_EQUAL(i, min_adc);
        // TEST_ASSERT_FALSE_MESSAGE(detected, "Staying low");
    }

    // stay high for a few cycles
    for (int i=20; i<30; i++) {
        analogue_value = i;
        BallDetector_measure();
        detected = BallDetector_isBallDetected(&min_adc, &max_adc);
        TEST_ASSERT_EQUAL(i, min_adc);
        TEST_ASSERT_FALSE_MESSAGE(detected, "Staying high");
    }

    // set a new threshold
    BallDetector_setThreshold(40);
    BallDetector_measure();
    detected = BallDetector_isBallDetected(&min_adc, &max_adc);
    TEST_ASSERT_EQUAL(29, min_adc);
    TEST_ASSERT_TRUE_MESSAGE(detected, "New threshold");
}


int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_ball_detection);
    UNITY_END();
}