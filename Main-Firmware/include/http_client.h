#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

// HTTP Client - FreeRTOS ESP IDF - GET

#include "WiFi.h"
#include "const.h"

esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt);
void rest_get();

#endif