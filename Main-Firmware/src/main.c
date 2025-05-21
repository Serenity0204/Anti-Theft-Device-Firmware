#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "http_client.h"
#include "mpu6050_driver.h"
#include "timer.h"

#define WIFI_ON 0

void setup()
{
    if (WIFI_ON)
    {
        nvs_flash_init();
        wifi_connection();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        printf("WIFI was initiated ...........\n\n");
        rest_get();
    }
    buzzer_init();
    timer_init();
}

void app_main(void)
{
    setup();
    ESP_ERROR_CHECK(mpu6050_init());
    ESP_ERROR_CHECK(mpu6050_wake());

    int16_t data_x, data_y, data_z;

    while (1)
    {
        if (mpu6050_read_data(&data_x, &data_y, &data_z) == ESP_OK)
        {
            ESP_LOGI(TAG, "X_value = %d | Y_value = %d | Z_value = %d", data_x, data_y, data_z);
        }
        else
        {
            ESP_LOGE(TAG, "failed to read!");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms (1 second)
    }
}