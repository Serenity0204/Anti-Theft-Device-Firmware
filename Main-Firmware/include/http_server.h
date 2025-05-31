#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "WiFi.h"
#include "const.h"
#include <stdio.h>
#include <string.h>

httpd_handle_t start_webserver(void);
esp_err_t unlock_mode_handler(httpd_req_t* req);
esp_err_t lock_mode_handler(httpd_req_t* req);

#endif