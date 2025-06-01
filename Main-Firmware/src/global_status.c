#include "global_status.h"

// 0 = unlocked, 1 = locked
volatile int locked = 1;

// 0 = not being stolen, 1 = being stolen
volatile int is_stolen = 0;
volatile int did_buzz = 0;
volatile TickType_t buzzer_on_time = 0;

volatile float gps_latitude = -200.0f;
volatile float gps_longitude = 200.0f;