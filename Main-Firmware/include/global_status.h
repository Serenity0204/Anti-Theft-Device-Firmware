#ifndef GLOBAL_STATUS_H
#define GLOBAL_STATUS_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 0 = unlocked, 1 = locked
extern volatile int locked;
// 0 = not being stolen, 1 = being stolen
extern volatile int is_stolen;
extern volatile int did_buzz;
extern volatile TickType_t buzzer_on_time;

extern volatile float gps_latitude;
extern volatile float gps_longitude;

#endif