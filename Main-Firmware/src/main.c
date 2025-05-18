#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "http_client.h"

void app_main(void)
{
    nvs_flash_init();
    wifi_connection();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("WIFI was initiated ...........\n\n");
    rest_get();
}