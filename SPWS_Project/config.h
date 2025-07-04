#ifndef __HEADER_FILE_CONFIG_H__
#define __HEADER_FILE_CONFIG_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* System state definitions */
#define MODE_AUTO 0
#define MODE_MANUAL 1

/* Water pump state definitions */
#define PUMP_OFF 0
#define PUMP_ON 1

/* LED state definitions */
#define LED_NORMAL 0
#define LED_WATERING 1 // The system is watering
#define LED_LOW_MOISTURE_ALERT 2 // The moisture of soil is too low
#define LED_ERROR 3 // System Errors

/* Watering Requirements */
#define WATER_REQ_MIN_MOIST 10U // Minimum moisture is 10%
#define WATER_REQ_MAX_MOIST 50U // Maximum moisture is 50%
#define WATER_REQ_MAX_TIME	10U // Maximum time for watering is 10 seconds

/* Sensor Requirements */
#define SENSOR_READ_PERI_TIME 5U // 5 Minutes read the data from sensor 1 time.

/* Simulated GPIO Pin definitions */
#define GPIO_PUMP 0U
#define GPIO_LED_GREEN 1U
#define GPIO_LED_YELLOW	2U
#define GPIO_LED_RED 3U
#define GPIO_BTN_MODE 4U
#define GPIO_BTN_MANUAL 5U

/* Logging macros */
#define LOG(...) printf("[LOG][%s:%d] ", __func__, __LINE__); printf(__VA_ARGS__)

// -------------------------------------------------------------------------------------

/* System configuration structure */
typedef struct
{
	uint32_t moistSensor; // For storing data from moisture sensor
	uint32_t tempSensor;  // For storing data from temperature sensor
}SENSOR_DATA_t;

/* System Configurations structure*/
typedef struct
{
	uint8_t min_moist;
	uint8_t max_moist;
	uint8_t water_max_time;
	uint8_t sensor_read_peri_time;
	uint8_t sys_curr_state;
}SYS_CONFIG_t;

/* Global variables */
extern SENSOR_DATA_t sensor_data;
extern SYS_CONFIG_t sys_config;
extern uint8_t pump_state;
extern uint8_t led_status;
extern bool manual_water_request;

/* Simulated Hardware APIs */
void turn_pump_on(void);
void turn_pump_off(void);
void update_led_status(uint8_t status);
void simulate_sensor_reading(void);

/* Logic Functions */
void check_manual_button(void);
void handle_auto_mode(void);
void toggle_mode(void);
void simulate_button_input(void);

#endif // __HEADER_FILE_CONFIG_H__
