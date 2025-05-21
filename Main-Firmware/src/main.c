#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "http_client.h"
#include "mpu6050_driver.h"
#include "neo6m_gps_driver.h"
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
    mpu6050_init();
    mpu6050_wake();
    neo6m_gps_init();
}

void app_main(void)
{
    setup();

    // int16_t data_x, data_y, data_z;
    // while (1)
    // {
    //     mpu6050_read_data(&data_x, &data_y, &data_z);
    //     ESP_LOGI(TAG, "X_value = %d | Y_value = %d | Z_value = %d", data_x, data_y, data_z);
    //     vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms (1 second)
    // }

    while (1)
    {
        neo6m_gps_read();
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms (1 second)
    }
}