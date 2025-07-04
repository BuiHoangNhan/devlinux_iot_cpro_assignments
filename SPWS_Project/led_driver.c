#include <stdio.h>
#include <stdint.h>
#include "config.h"

/*
* @brief This function is using for triggering the led status base on the status of the system
* @param status This is the status of the system
* @return none
*/
void update_led_status(uint8_t status)
{
	led_status = status;
	const char* colors[] =
	{
		"Green (Normal)",
		"Yellow (Watering)",
		"Red (Low Moisture)",
		"Red (Error)"
	};
	uint8_t gpio_pin;
	switch (led_status)
	{
	case LED_NORMAL:
		gpio_pin = GPIO_LED_GREEN;
		break;
	case LED_WATERING:
		gpio_pin = GPIO_LED_YELLOW;
		break;
	default:
		gpio_pin = GPIO_LED_RED;
		break;
	}
	LOG("GPIO %d: Status LED: %s.\r", gpio_pin, colors[status]);
	return;
}
