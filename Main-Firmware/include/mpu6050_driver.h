#ifndef MPU6050_DRIVER_H
#define MPU6050_DRIVER_H

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SDA_IO 21
#define SCL_IO 22
#define MPU6050_ADDR 0x68
#define TAG "MPU6050"
#define I2C_FREQ 100000
#define I2C_MASTER_NUM I2C_NUM_0 

esp_err_t mpu6050_init();
esp_err_t mpu6050_wake();
esp_err_t mpu6050_read_data(int16_t *x,int16_t *y,int16_t *z);

#endif