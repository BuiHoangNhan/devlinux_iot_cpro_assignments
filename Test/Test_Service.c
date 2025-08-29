// ---------- include header files ----------
#include <stdio.h>
#include <stdint.h>
#include "Test_Service.h"

// ---------- local constants ----------
#define AMP_CONSTANT 10U
#define SENSOR_DATA_ARRAY_SIZE 5

// ---------- local data type ----------

// ---------- local variables ----------
FILE *fp;
static uint8_t sensor_data[SENSOR_DATA_ARRAY_SIZE];
// ---------- local function prototype ----------

// ---------- global function definition ----------
uint8_t check_sum(ads1115_final_res_t final_res)
{
    uint8_t h_high = (final_res.humidity >> 0x8) & 0xFF;
    uint8_t h_low = (final_res.humidity) & 0xFF;

    uint8_t t_high = (final_res.temperature >> 0x8) & 0xFF;
    uint8_t t_low = (final_res.temperature) & 0xFF;

    return (h_high + h_low + t_high + t_low) & 0xFF;
}

void convert_to_data_stream(float temp, float humidity)
{
    int sign = 1;
    ads1115_final_res_t final_res;

    // 0. Signed validation, whether the temperature is positve or negativeS
    if (temp < 0)
        sign = -1;

    // 1. Multiply the Amplifier constant
    temp *= sign;
    temp *= AMP_CONSTANT;
    humidity *= AMP_CONSTANT;

    // 2. Prepare the final result
    final_res.temperature = (uint16_t)temp;
    if (sign < 0)
    {
        final_res.temperature |= (0x1 << 15); // Set the MSB bit to 1 for negative value
    }
    final_res.humidity = (uint16_t)humidity;
    final_res.check_sum = check_sum(final_res);

    // 3. Store in sensor_data array
    sensor_data[0] = (final_res.humidity >> 0x8) & 0xFF;
    sensor_data[1] = (final_res.humidity) & 0xFF;
    sensor_data[2] = (final_res.temperature >> 0x8) & 0xFF;
    sensor_data[3] = (final_res.temperature) & 0xFF;
    sensor_data[4] = final_res.check_sum;
}

void Create_Data_Test(const char *filename, float temp, float humidity)
{
    // 1. Open the file with name "filename"
    fp = fopen(filename, "wb+");
    if (fp == NULL)
    {
        printf("[ERROR][%s: %d]: Failed to open the file \"%s\".", __FUNCTION__, __LINE__, filename);
        return;
    }

    // 2. Convert the input data to data stream
    convert_to_data_stream(temp, humidity);

    // 3. Write into the data_log.txt file
    fwrite(sensor_data, sizeof(uint8_t), SENSOR_DATA_ARRAY_SIZE, fp);
    rewind(fp);

    // 4. Read back what I've written for debugging
    size_t read = 0;
    uint16_t h_res = 0;
    uint16_t t_res = 0;
    uint8_t check_sum = 0;
    uint8_t buffer[5] = {0};

    read = fread(buffer, sizeof(uint8_t), 5, fp);

    h_res = ((uint16_t)buffer[0] << 0x8) | buffer[1];
    t_res = ((uint16_t)buffer[2] << 0x8) | buffer[3];
    check_sum = buffer[4];

    printf("You have written %d elements = {%d, %d, %d} to %s\n", read, h_res, t_res, check_sum, filename);
    fclose(fp);
}