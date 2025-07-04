#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
* @brief This function is using check the manual button
*/
void check_manual_button(void)
{
	if (sys_config.sys_curr_state == MODE_MANUAL && manual_water_request)
	{
		LOG("Manual watering request.");
		update_led_status(LED_WATERING);
		turn_pump_on();
		for (int i = 0; i < 1000; i++); // Simulate 10 seconds delay
		turn_pump_off();
		update_led_status(LED_NORMAL);
		manual_water_request = false;
	}
	return;
}


void simulate_button_input() {
	printf("\n[INPUT] Press key: [1] AUTO mode, [2] MANUAL mode, [m] Manual water, [q] Quit\n> ");
	char ch = getchar();
	while (getchar() != '\n'); // flush
	if (ch == '1') set_mode(MODE_AUTO);
	else if (ch == '2') set_mode(MODE_MANUAL);
	else if (ch == 'm') manual_water_request = true;
	else if (ch == 'q') exit(0);
}
