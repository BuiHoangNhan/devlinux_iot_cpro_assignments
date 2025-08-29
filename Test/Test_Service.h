#ifndef __TEST_SERVICE_H__
#define __TEST_SERVICE_H__

// ---------- include header files ----------
#include <stdint.h>
// ---------- constant ----------

// ---------- data type ----------
typedef struct
{
    uint8_t check_sum;
    uint16_t humidity;
    uint16_t temperature;
} ads1115_final_res_t;

// ---------- function prototype ----------
void Create_Data_Test(const char *filename, float temp, float humidity);

#endif // __TEST_SERVICE_H__
