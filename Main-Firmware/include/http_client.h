#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

// HTTP Client - FreeRTOS ESP IDF - GET

#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "nvs_flash.h"
#include <stdio.h>

#define SSID "iPhone"
#define PASS "12345678"

void wifi_connection();
esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt);
void rest_get();

#endif