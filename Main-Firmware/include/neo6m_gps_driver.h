#ifndef NEO6M_GPS_H
#define NEO6M_GPS_H

#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>

#define NEO6M_UART_NUM UART_NUM_2
#define NEO6M_TXD_PIN 17
#define NEO6M_RXD_PIN 16
#define NEO6M_BAUD_RATE 9600
#define BUFFER_SIZE 1024

typedef struct
{
    bool valid;
    float latitude;
    float longitude;
} gps_data_t;

void neo6m_gps_init();
gps_data_t neo6m_gps_read();

#endif