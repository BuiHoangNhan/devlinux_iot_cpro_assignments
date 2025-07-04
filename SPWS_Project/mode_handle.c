#include <stdint.h>
#include <stdio.h>
#include "config.h"

void handle_auto_mode(void) {
    simulate_sensor_reading();

    if (sensor_data.moistSensor < sys_config.min_moist) {
        LOG("Low moisture detected. Starting watering.");
        update_led_status(LED_WATERING);
        turn_pump_on();

        int elapsed = 0;
        while (sensor_data.moistSensor < sys_config.max_moist && elapsed < sys_config.water_max_time) {
            for (int i = 0; i < 1000; i ++) // Simulate 10s for watering
            elapsed++;
            simulate_sensor_reading();
        }

        turn_pump_off();
        update_led_status(LED_NORMAL);
        LOG("Watering complete.");
    }
    else {
        update_led_status(LED_NORMAL);
    }
}

void set_mode(uint8_t mode) {
    sys_config.sys_curr_state = mode;
    LOG(mode == MODE_AUTO ? "Switched to AUTO mode." : "Switched to MANUAL mode.");
    if (mode == MODE_MANUAL && pump_state == PUMP_ON) {
        turn_pump_off();
    }
}