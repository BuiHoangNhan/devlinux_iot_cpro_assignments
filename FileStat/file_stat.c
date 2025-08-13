// ---------- include header files ----------
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "file_stat.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// ---------- local constants ----------
#define COMMAND_STRING ("./filestat ")
// ---------- local data type ----------

// ---------- local variables ----------
custom_stat_t st;
struct stat info;
// ---------- local function prototype ----------
/**
 * @brief   This function is using for assess the input command, whether it is valid or not
 *          and stores the directory to the directory buffer
 * @param arr This is the pointer point to the input string
 * @return the result of the function. STATUS_OK for success and STATUS_ERROR for failure
 */
err_def_t command_validation(char *arr);

// ---------- global function definition ----------
err_def_t command_validation(char *arr)
{
    char *pos = strstr(arr, COMMAND_STRING);
    // 1. Input validation
    if (pos == NULL)
    {
        LOG_E("Unvalid command!, please retry with: ./filestat <file_path>.\r\n");
        return STATUS_ERROR;
    }

    // 2. Take the directory from input
    pos += strlen(COMMAND_STRING); // Point to the command with format ./filestat <file_path>

    /*  Copy the directory to the directory buffer (This is a safe way to do).
        It automatically assisn the last character to '\0'  */
    snprintf(st.dr, sizeof(st.dr), "%s", pos);

    return STATUS_OK;
}

err_def_t type_sorting(void)
{
    int ret = 0;

    // 1. Check whether it is a regular file or not
    ret = S_ISREG(info.st_mode);
    if (ret)
    {
        LOG_I("TYPE: This is a Regular File\r\n");
        return STATUS_OK;
    }

    // 2. Check whether it is a directory or not
    ret = S_ISDIR(info.st_mode);
    if (ret)
    {
        LOG_I("TYPE: This is a Directory\r\n");
        return STATUS_OK;
    }

    // 3. Check whether it is a symbolic link or not
    ret = S_ISLNK(info.st_mode);
    if (ret)
    {
        LOG_I("TYPE: This is a Symbolic Link\r\n");
        return STATUS_OK;
    }
    LOG_E("Unsupported type or unvalid type!\r\n");
    return STATUS_ERROR;
}

err_def_t run_filestat(char *arr)
{
    int ret = 0; // To store the result of the function
    // 1. Input validation and copy the directory to st.dr
    ret = command_validation(arr);
    if (ret != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    // 2. Take the metadata using lstat function
    //* Prototypes of lstat: int lstat(const char *pathname, struct stat *statbuf);
    ret = lstat(st.dr, &info);
    if (ret)
    {
        LOG_E("Failed to read metadata with lstat\r\n");
        return STATUS_ERROR;
    }
    printf("---------- Metadata from directory ----------\r\n");

    // 3. Sort and printing type of the file
    ret = type_sorting();
    if (ret == STATUS_ERROR)
    {
        return STATUS_ERROR;
    }

    // 4. Print the size of the file in byte
    LOG_I("SIZE: The size of file in bytes = %d\r\n", (int)info.st_size);

    // 5. Print out the last time modified
    LOG_I("TIME: The last modified time is: %s", ctime(&info.st_mtime));
}