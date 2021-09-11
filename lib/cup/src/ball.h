#ifndef BALL_H
#define BALL_H

void BallDetector_initialise(uint16_t threshold);
void BallDetector_measure();
bool BallDetector_isBallDetected(uint16_t *min, uint16_t *max);

#endif