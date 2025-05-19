#ifndef TIMER_H
#define TIMER_H

#include "buzzer.h"
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void timer_init();

#endif