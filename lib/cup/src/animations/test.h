#ifndef TEST_H
#define TEST_H

#include "colour.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t duration;
} TestParams;
#pragma pack(pop)

typedef struct {
    uint16_t count;
    bool tx_enabled;
    uint8_t color_index;
} TestState;

void test_init(TestParams *params, TestState *state);
void test_refresh(TestParams *params, TestState *state);

#endif