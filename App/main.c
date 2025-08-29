// ---------- include header files ----------
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DHT22.h"
#include "Test_Service.h"
// ---------- local constants ----------

#define FILENAME_MAX_LENGTH 100

// ---------- local data type ----------
float temp;
float humidity;
char filename[FILENAME_MAX_LENGTH];

float dht_temp_res;
float dht_humid_res;
// ---------- local variables ----------

// ---------- local function prototype ----------

bool test_input(void);

// ---------- global function definition ----------
int main(void)
{
    // 1. Input testing value
    if (test_input() == false)
    {
        return -1;
    }
    printf("---------- Input values ----------\r\n");
    LOG_I("Input temperature = %.01f", temp);
    LOG_I("Input humidity = %.01f", humidity);

    // 2. Create data file from that inputs
    Create_Data_Test(filename, temp, humidity);

    // 3. DHT initialization
    printf("---------- DHT Simulation ----------\r\n");
    if (DHT_Init(filename) == false)
    {
        return -1;
    }

    if (DHT_Read_Temperature(&dht_temp_res) == false)
    {
        return -1;
    }

    if (DHT_Read_Humidity(&dht_humid_res) == false)
    {
        return -1;
    }

    return 0;
}

// ---------- local function definition ----------
bool test_input(void)
{
    // 1. Input the file's name
    printf("Please input the filename for testing: ");
    fgets(filename, FILENAME_MAX_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    printf("\n");

    // 2. Input the humidity
    printf("Please input the humidity for testing: ");
    scanf("%f", &humidity);
    printf("\n");
    if (humidity < 0 || humidity > 100)
    {
        LOG_E("Humidity should be in range 0 to 100%%");
        return false;
    }

    // 3. Input the temperature
    printf("Please input the temperature for testing: ");
    scanf("%f", &temp);
    printf("\n");

    return true;
}
