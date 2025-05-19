#include "buzzer.h"

void buzzer_init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUZZER_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
    gpio_set_level(BUZZER_PIN, 0);
}

void buzzer_on()
{
    gpio_set_level(BUZZER_PIN, 1);
}

void buzzer_off()
{
    gpio_set_level(BUZZER_PIN, 0);
}