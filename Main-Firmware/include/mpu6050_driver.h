#ifndef MPU6050_DRIVER_H
#define MPU6050_DRIVER_H

#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define SDA_IO 21
#define SCL_IO 22
#define MPU6050_ADDR 0x68
#define TAG "MPU6050"
#define I2C_FREQ 100000
#define I2C_MASTER_NUM I2C_NUM_0

void mpu6050_init();
void mpu6050_read_data(int16_t* x, int16_t* y, int16_t* z);

#endif