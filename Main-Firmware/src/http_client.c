#include "http_client.h"

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char*)evt->data);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void send_gps_location(const char* location)
{
    char full_url[100];
    sprintf(full_url, "%s/esp32/send-gps-location/", ESP32_API_ENDPOINT);

    esp_http_client_config_t config_post = {
        .url = full_url,
        .method = HTTP_METHOD_POST,
        .event_handler = client_event_post_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, location, strlen(location));

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}
