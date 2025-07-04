#include <stdio.h>
#include <config.h>
#include <stdlib.h>
#include <time.h>

/* Global variables definitions */
SENSOR_DATA_t sensor_data;
uint8_t pump_state = PUMP_OFF;
uint8_t led_status = LED_NORMAL;

SYS_CONFIG_t sys_config = {
    .min_moist = WATER_REQ_MIN_MOIST,
    .max_moist = WATER_REQ_MAX_MOIST,
    .water_max_time = WATER_REQ_MAX_TIME,
    .sensor_read_peri_time = SENSOR_READ_PERI_TIME,
    .sys_curr_state = MODE_AUTO
};

bool manual_water_request = false;


int main() {
    srand(time(NULL));
    LOG("SPWS System Initialized.");

    simulate_button_input();
    while (1) {
        check_manual_button();
        if (sys_config.sys_curr_state == MODE_AUTO) {
            handle_auto_mode();
        }
        for (int i = 0; i < 1000; i++);
        getchar();
    }
    return 0;
}
