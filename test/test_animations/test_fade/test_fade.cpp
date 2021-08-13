#include <unity.h>
#include <stdio.h>
#include "animation.h"
#include "animations/fade.h"
#include "timer.h"

#define TEST_ASSERT_LEDS(i, r, g, b) TEST_ASSERT_EQUAL_UINT8_MESSAGE(pixels_live[(i)].red, (r), "Red index "#i);TEST_ASSERT_EQUAL_UINT8_MESSAGE(pixels_live[(i)].green, (g), "Green index "#i);TEST_ASSERT_EQUAL_UINT8_MESSAGE(pixels_live[(i)].blue, (b), "Blue index "#i)

extern uint8_colour pixels_live[LED_COUNT];
extern void MockTimer_tick();

void print_pixels_live()
{
    printf("0[R%3d G%3d B%3d] 1[R%3d G%3d B%3d] 2[R%3d G%3d B%3d] 3[R%3d G%3d B%3d] 4[R%3d G%3d B%3d] 5[R%3d G%3d B%3d] 6[R%3d G%3d B%3d] 7[R%3d G%3d B%3d]\n", 
        pixels_live[0].red, pixels_live[0].green, pixels_live[0].blue,
        pixels_live[1].red, pixels_live[1].green, pixels_live[1].blue,
        pixels_live[2].red, pixels_live[2].green, pixels_live[2].blue,
        pixels_live[3].red, pixels_live[3].green, pixels_live[3].blue,
        pixels_live[4].red, pixels_live[4].green, pixels_live[4].blue,
        pixels_live[5].red, pixels_live[5].green, pixels_live[5].blue,
        pixels_live[6].red, pixels_live[6].green, pixels_live[6].blue,
        pixels_live[7].red, pixels_live[7].green, pixels_live[7].blue);
}

void test_fade_in()
{
    AnimationController_initialise(1);

    // set pixels to off initially
    for (int i=0; i<LED_COUNT; i++) {
        LedController_setColour(i, 0, 0, 0);
    }
    LedController_refresh();

    FadeParams params = {
        {10, 100, 200},
        10
    };

    AnimationController_setAnimation(0x02, (uint8_t*)&params, sizeof(FadeParams));

    print_pixels_live();

    for (int i=10; i>=0; i--)
    {
        MockTimer_tick();
        print_pixels_live();
    }
    
    for (int i=0; i<LED_COUNT; i++) {
        TEST_ASSERT_LEDS(i, 10, 100, 200);
    }
}

void test_fade_out()
{
    TEST_IGNORE_MESSAGE("Not implemented");
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_fade_in);
    RUN_TEST(test_fade_out);
    UNITY_END();
}