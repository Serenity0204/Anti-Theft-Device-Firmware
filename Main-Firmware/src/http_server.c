#include "http_server.h"
#include "buzzer.h"

// /high request handler
esp_err_t high_handler(httpd_req_t* req)
{
    buzzer_on();
    httpd_resp_send(req, "BUZZER ON", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// /low request handler
esp_err_t low_handler(httpd_req_t* req)
{
    buzzer_off();
    httpd_resp_send(req, "BUZZER OFF", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// Start web server with only /high and /low
httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_uri_t uri_high = {
            .uri = "/high",
            .method = HTTP_GET,
            .handler = high_handler,
            .user_ctx = NULL};
        httpd_register_uri_handler(server, &uri_high);

        httpd_uri_t uri_low = {
            .uri = "/low",
            .method = HTTP_GET,
            .handler = low_handler,
            .user_ctx = NULL};
        httpd_register_uri_handler(server, &uri_low);
    }

    return server;
}
