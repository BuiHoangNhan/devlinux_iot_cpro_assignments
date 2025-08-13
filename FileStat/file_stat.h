#ifndef __FILE_STAT_H__
#define __FILE_STAT_H__

// ---------- include header files ----------
#include <stdio.h>

// ---------- Constant ----------
#define LOG_I(fmt, ...) (printf("[INFO][Line: %d][Function: %s]: " fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__))
#define LOG_E(fmt, ...) (printf("[ERROR][Line: %d][Function: %s]: " fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__))
#define LOG_W(fmt, ...) (printf("[WARNING][Line: %d][Function: %s]: " fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__))

#define DIRECTORY_BUFFER_MAX 10000
#define TIME_STAMP_BUFFER_MAX 1000

/**
 * @brief This enum use to enumerate the status or result of a function
 */
typedef enum
{
    STATUS_OK,
    STATUS_ERROR
} err_def_t;

/**
 *   @brief This is the enum describe the file types.
 */
typedef enum
{
    REGULAR_FILE,
    DIRECTORY,
    SYMBOLIC_LINK
} file_typedef_t;

/**
 * @brief This struct is using for storing the stat of the a file
 */
typedef struct
{
    char dr[DIRECTORY_BUFFER_MAX]; // This buffer stores the directory that is receive from the command
    file_typedef_t file_type;
    char time_stamp[TIME_STAMP_BUFFER_MAX];
} custom_stat_t;
// ---------- Global variables ----------

// ---------- Function prototypes ----------

err_def_t run_filestat(char *arr);
#endif // __FILE_STAT_H__
