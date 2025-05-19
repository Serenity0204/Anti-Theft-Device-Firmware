#ifndef BUZZER_H
#define BUZZER_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define BUZZER_PIN GPIO_NUM_23

void buzzer_init();
void buzzer_on();
void buzzer_off();

#endif