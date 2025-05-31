#include "http_server.h"
#include "buzzer.h"
#include "global_status.h"

esp_err_t unlock_mode_handler(httpd_req_t* req)
{
    locked = 0;
    is_stolen = 0;
    buzzer_on_time = 0;
    buzzer_off();
    httpd_resp_send(req, "UNLOCK MODE SUCCESS", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t lock_mode_handler(httpd_req_t* req)
{
    locked = 1;
    did_buzz = 0;
    httpd_resp_send(req, "LOCK MODE SUCCESS", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_uri_t uri_unlock_mode = {
            .uri = "/unlock-mode",
            .method = HTTP_GET,
            .handler = unlock_mode_handler,
            .user_ctx = NULL};

        httpd_register_uri_handler(server, &uri_unlock_mode);
        httpd_uri_t uri_lock_mode = {
            .uri = "/lock-mode",
            .method = HTTP_GET,
            .handler = lock_mode_handler,
            .user_ctx = NULL};

        httpd_register_uri_handler(server, &uri_lock_mode);
    }

    return server;
}
