#pragma once 
#include "macros.h"

typedef enum {ALT, START, CMD_ERR, LEN_WARN} cmd_type;

typedef union {
    unsigned char tab_count;
    char prog_name[MAX_PROG_NAME_LEN];
    char* err;
} cmd_value;

typedef struct {
    cmd_value value;
    cmd_type type;
} Command;

typedef struct _Task_list Task_list;
typedef struct _Task_list{
    Task_list* next;
    Task_list* prev;
    char prog_name[MAX_PROG_NAME_LEN];
} Task_list;

Command cmd_process(char* cmd_text);
Command easy_scan(char* buff);

void insert(char* prog_name, Task_list** active_task_ptr);
void shift(unsigned short index, Task_list** active_task_ptr);

void memory_clear(Task_list* task);