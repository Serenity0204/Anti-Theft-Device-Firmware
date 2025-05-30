#include "neo6m_gps_driver.h"
#include "minmea.h"

static char buffer[BUFFER_SIZE];

void neo6m_gps_init()
{
    uart_config_t uart_config = {
        .baud_rate = NEO6M_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    ESP_ERROR_CHECK(uart_param_config(NEO6M_UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(NEO6M_UART_NUM, NEO6M_TXD_PIN, NEO6M_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(NEO6M_UART_NUM, BUFFER_SIZE, 0, 0, NULL, 0));
}

static void read_raw_nmea(char* buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    uart_read_bytes(NEO6M_UART_NUM, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);
}

gps_data_t neo6m_gps_read()
{
    gps_data_t data = {
        .valid = false,
        .latitude = 0.0f,
        .longitude = 0.0f,
    };

    read_raw_nmea(buffer);

    char* line = strtok(buffer, "\n");
    while (line != NULL)
    {
        if (minmea_sentence_id(line, false) == MINMEA_SENTENCE_RMC)
        {
            struct minmea_sentence_rmc frame;
            if (minmea_parse_rmc(&frame, line) && frame.valid)
            {
                data.valid = true;
                data.latitude = minmea_tocoord(&frame.latitude);
                data.longitude = minmea_tocoord(&frame.longitude);
                // Found valid fix, no need to parse more
                break;
            }
        }
        line = strtok(NULL, "\n");
    }
    return data;
}
