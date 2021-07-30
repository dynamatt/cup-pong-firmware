#include <unity.h>
#include <stdint.h>
#include "colour.h"

void test_create()
{
    uint32_t in = 0x12345678;
    uint8_colour out = create(in);
    TEST_ASSERT_EQUAL_UINT8(0x34, out.red);
    TEST_ASSERT_EQUAL_UINT8(0x56, out.green);
    TEST_ASSERT_EQUAL_UINT8(0x78, out.blue);
}

void test_add()
{
    uint16_colour a = { 10, 20, 30};
    uint16_colour b = { 0, 100, 200};
    uint16_colour c = add(a, b);
    TEST_ASSERT_EQUAL_UINT16(10, c.red);
    TEST_ASSERT_EQUAL_UINT16(120, c.green);
    TEST_ASSERT_EQUAL_UINT16(230, c.blue);
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_create);
    RUN_TEST(test_add);
    UNITY_END();
}