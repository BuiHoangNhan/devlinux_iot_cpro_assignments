#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
* @brief This function is using for simulating the sensor reading.
* @param none
* @return none
*/
void simulate_sensor_reading(void)
{
	sensor_data.moistSensor = rand() % 101; // 0 - 100%
	sensor_data.tempSensor = 20 + (rand() % 1500) / 100; // 20 - 35
	LOG("Moisture: %u%%, Temp: %uC\n", sensor_data.moistSensor, sensor_data.tempSensor);
	return;
}

