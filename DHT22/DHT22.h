#ifndef __DHT22_H__
#define __DHT22_H__

// ---------- include header files ----------
#include <stdbool.h>
#include <stdint.h>
// ---------- constant ----------
#define LOG_I(fmt, ...) (printf("[INFO][%s: %d] " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define LOG_E(fmt, ...) (printf("[ERROR][%s: %d] " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define LOG_W(fmt, ...) (printf("[WARNING][%s: %d] " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
// ---------- data type ----------

// ---------- function prototype ----------
bool DHT_Init(const char *filename);
bool DHT_Read_Temperature(float *temp);
bool DHT_Read_Humidity(float *humidity);

#endif
