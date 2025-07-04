#include "config.h"
#include <stdio.h>
#include <stdint.h>

/* Pump simulated driver */

/*
*	@brief This function is using for turning Pump ON.
*/
void turn_pump_on(void)
{
	pump_state = PUMP_ON;
	LOG("GPIO %d: Pump turned ON.\r\n", GPIO_PUMP);
	return;
}

/*
* @brief This function is using for turning Pump OFF
*/
void turn_pump_off(void)
{
	pump_state = PUMP_OFF;
	LOG("GPIO %d: Pump turned OFF.\r\n", GPIO_PUMP);
	return;
}




