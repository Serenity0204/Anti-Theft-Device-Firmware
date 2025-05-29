#ifndef MOTION_DETECTION_H
#define MOTION_DETECTION_H

#include "mpu6050_driver.h"
#define lower_bound 16500
#define upper_bound 17050

uint32_t fast_sqrt(uint32_t x);
int16_t detect_movement(int16_t x, int16_t y, int16_t z);

#endif