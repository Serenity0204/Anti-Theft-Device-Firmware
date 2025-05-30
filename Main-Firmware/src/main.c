#include "WiFi.h"
#include "buzzer.h"
#include "esp_netif_ip_addr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global_status.h"
#include "http_client.h"
#include "http_server.h"
#include "motion_detection.h"
#include "mpu6050_driver.h"
#include "neo6m_gps_driver.h"
#include "timer.h"

#define DEBUG_ON 1

void setup()
{
    if (DEBUG_ON)
    {
        esp_netif_ip_info_t ip_info;
        esp_netif_t* netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
        if (esp_netif_get_ip_info(netif, &ip_info) == ESP_OK) printf("My IP: " IPSTR "\n", IP2STR(&ip_info.ip));
    }

    // wifi_init();
    // rest_get();

    buzzer_init();
    // timer_init();
    mpu6050_init();
    neo6m_gps_init();
}

void gps_task(void* pvParameters)
{
    while (1)
    {
        if (!is_stolen)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        // read only when it's stolen
        gps_data_t gps = neo6m_gps_read();
        if (gps.valid)
        {
            gps_latitude = gps.latitude;
            gps_longitude = gps.longitude;

            if (DEBUG_ON) printf("GPS: Latitude = %.6f, Longitude = %.6f\n", gps.latitude, gps.longitude);
        }
        else
        {
            if (DEBUG_ON) printf("GPS data not valid.\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void motion_detection_task(void* pvParameters)
{
    int16_t data_x, data_y, data_z;

    while (1)
    {
        if (!locked)
        {
            vTaskDelay(pdMS_TO_TICKS(5000));
            continue;
        }

        mpu6050_read_data(&data_x, &data_y, &data_z);
        printf("X = %d | Y = %d | Z = %d\n", data_x, data_y, data_z);

        if (detect_movement(data_x, data_y, data_z))
        {
            is_stolen = 1;

            printf("Motion detected!\n");
            printf("%d %d %d \n", data_x, data_y, data_z);
            // send the gps_latitude and gps_longitude to the webserver
            // TODO

            // turn on buzzer
            buzzer_on();
        }
        else
        {
            buzzer_off();
            is_stolen = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(5000)); // Run every 5s
    }
}

void app_main(void)
{
    // initialize everything
    setup();

    // start HTTP server in background
    // start_webserver();

    // create motion detection task
    xTaskCreate(motion_detection_task, "motion_detection_task", 4096, NULL, 20, NULL);
    xTaskCreate(gps_task, "gps_task", 4096, NULL, 5, NULL);
}