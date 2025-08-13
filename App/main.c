// ---------- include header files ----------
#include <stdio.h>
#include <string.h>
#include "file_stat.h"
// ---------- local constants ----------
#define INPUT_BUFFER_SIZE 100
// ---------- local data type ----------

// ---------- local variables ----------
char arr[INPUT_BUFFER_SIZE] = {0};

// ---------- local function prototype ----------

// local function definition
int main(void)
{
    int ret = 0;
    // 1. Take the input string from stdin
    printf("Enter command line: ");
    fgets(arr, INPUT_BUFFER_SIZE, stdin);
    // printf("Input string is: %.*s", (int)strlen(arr), arr);

    // 2. Call stat to print out Metadata
    run_filestat(arr);

    return 0;
}
