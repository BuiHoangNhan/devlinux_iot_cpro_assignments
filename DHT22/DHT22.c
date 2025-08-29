// ---------- include header files ----------
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "DHT22.h"

// ---------- local constants ----------
#define AMP_CONSTANT 10
#define SENSOR_DATA_ARRAY_SIZE 5

// ---------- local data type ----------

// ---------- local variables ----------
FILE *fp;
static uint8_t sensor_data[SENSOR_DATA_ARRAY_SIZE];
// ---------- local function prototype ----------
bool read_sensor_data(const char *filename);
uint8_t sum_checking(uint8_t data[]);

// ---------- global function definition ----------
bool DHT_Init(const char *filename)
{
    // 1. Simulate the GPIO initialization
    LOG_I("GPIO initialized successfully!");

    // 2. Open the file for reading
    fp = fopen(filename, "rb");
    if (NULL == fp)
    {
        LOG_E("Failed to open the file for reading sensor_data!");
        return false;
    }

    // 3. Read the sensor_data from filename
    if (read_sensor_data(filename) == false)
    {
        return false;
    }

    // 4. Close the file for avoiding data leakage
    fclose(fp);

    LOG_I("Successfully initialized DHT22!");
    return true;
}

bool DHT_Read_Temperature(float *temp)
{
    int sign = 1;
    uint16_t t_res = 0;

    // 1. Sign validation, whether it is a negative or positive number
    if (sensor_data[2] & (0x1 << 7))
    {
        sign = -1;
        sensor_data[2] &= ~(0x1 << 7);
    }

    // 2. Change the data from binary to decimal
    t_res = ((uint16_t)sensor_data[2] << 0x8) | sensor_data[3];

    // 3. Change the data from decimal to float
    *temp = t_res / AMP_CONSTANT;
    *temp += (float)(t_res % AMP_CONSTANT) / AMP_CONSTANT;
    *temp *= sign;

    // 3. Print out the result
    LOG_I("Successfully read temperature = %.01f(oC)", *temp);
    return true;
}

bool DHT_Read_Humidity(float *humidity)
{
    uint16_t h_res = 0;

    // 1. Change the data from binary to decimal
    h_res = ((uint16_t)sensor_data[0] << 0x8) | sensor_data[1];

    // 2. Change the data from decimal to float
    *humidity = h_res / AMP_CONSTANT;
    *humidity += (float)(h_res % AMP_CONSTANT) / AMP_CONSTANT;

    // 3. Print out the result
    LOG_I("Successfully read humidity = %.01f(%%RH)", *humidity);
    return true;
}

bool read_sensor_data(const char *filename)
{
    size_t read = fread(sensor_data, sizeof(uint8_t), SENSOR_DATA_ARRAY_SIZE, fp);
    if (read == 0)
    {
        LOG_E("This file does not have any data!, please re-check the file or open another file!");
        return false;
    }

    if (sum_checking(sensor_data) != sensor_data[4])
    {
        LOG_E("Check_sum validation failed, the data is not integrity");
        return false;
    }
    return true;
}

uint8_t sum_checking(uint8_t data[])
{
    return (data[0] + data[1] + data[2] + data[3]) & 0xFF;
}