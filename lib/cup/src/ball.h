#ifndef BALL_H
#define BALL_H

void BallDetector_initialise(uint16_t threshold);
bool BallDetector_isBallDetected(uint16_t *adc);

#endif