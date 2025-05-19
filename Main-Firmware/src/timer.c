#include "timer.h"

static bool IRAM_ATTR on_timer_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t* edata, void* user_ctx)
{
    // Toggle buzzer
    static bool on = false;
    if (on)
        buzzer_on();
    else
        buzzer_off();
    on = !on;

    return true;
}

void timer_init()
{
    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000,
    };
    gptimer_new_timer(&timer_config, &gptimer);

    gptimer_event_callbacks_t timer_callback = {
        .on_alarm = on_timer_alarm_cb,
    };
    gptimer_register_event_callbacks(gptimer, &timer_callback, NULL);
    gptimer_enable(gptimer);

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 1000000,             // 5 seconds (5,000,000 microseconds)
        .reload_count = 0,                  // start from 0
        .flags.auto_reload_on_alarm = true, // auto reload on
    };
    gptimer_set_alarm_action(gptimer, &alarm_config);
    gptimer_start(gptimer);
}