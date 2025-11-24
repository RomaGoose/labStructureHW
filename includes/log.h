#pragma once

#include <stdio.h>
#include <windows.h>

#define LOG_FILE_NAME "..\\lab2\\build\\logs.txt"
#define _LOG(lvl, log) _LOGF(lvl, " %s", log) 
#define _LOGF(lvl, fmt, ...) do{FILE * log_file = fopen(LOG_FILE_NAME, "a"); \
            fprintf(log_file, "[%s] | [%s:%s:%d] " fmt " PID: %lu\n", lvl, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__,  \
            GetCurrentProcessId()); fflush(log_file);fclose(log_file);}  while (0)