#include "mpu6050_driver.h"

esp_err_t mpu6050_init()
{
    i2c_config_t conf =
        {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_IO,
            .scl_io_num = SCL_IO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = I2C_FREQ,
        };
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

// wake up MPU6050 from default sleep mode
esp_err_t mpu6050_wake()
{
    uint8_t data[2] = {0x6B, 0x00};
    return i2c_master_write_to_device(I2C_MASTER_NUM, MPU6050_ADDR, data, 2, pdMS_TO_TICKS(1000));
}

esp_err_t mpu6050_read_data(int16_t* x, int16_t* y, int16_t* z)
{
    uint8_t reg = 0x3B;
    uint8_t data[6];

    esp_err_t result = i2c_master_write_read_device(I2C_MASTER_NUM, MPU6050_ADDR, &reg, 1, data, 6, pdMS_TO_TICKS(1000));
    if (result != ESP_OK) return result;

    *x = (int16_t)(data[0] << 8 | data[1]);
    *y = (int16_t)(data[2] << 8 | data[3]);
    *z = (int16_t)(data[4] << 8 | data[5]);

    return ESP_OK;
}
