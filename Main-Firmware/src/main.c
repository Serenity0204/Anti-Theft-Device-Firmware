#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "http_client.h"
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

    while (1)
    {
        // vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 1000 ms (1 second)
    }
}