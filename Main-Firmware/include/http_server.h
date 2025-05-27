#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "WiFi.h"
#include "const.h"
#include <stdio.h>
#include <string.h>

// Starts the HTTP server and registers /high and /low handlers
httpd_handle_t start_webserver(void);

// Handles GET /high (turns LED ON)
esp_err_t high_handler(httpd_req_t* req);

// Handles GET /low (turns LED OFF)
esp_err_t low_handler(httpd_req_t* req);

#endif