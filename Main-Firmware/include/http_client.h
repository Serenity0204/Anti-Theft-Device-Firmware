#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "WiFi.h"
#include "const.h"
#include <stdio.h>

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt);
void send_gps_location(const char* location);

#endif