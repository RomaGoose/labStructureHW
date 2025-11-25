#pragma once
#include "macros.h"
#include <string.h>
typedef enum { ALT, START, CMD_ERR, LEN_WARN } cmd_type;

typedef struct _Task_list Task_list;

typedef struct _Task_list {
  Task_list *next;
  Task_list *prev;
  char prog_name[MAX_PROG_NAME_LEN];
} Task_list;

void insert(char *prog_name, Task_list **active_task_ptr);
void shift(unsigned short index, Task_list **active_task_ptr);

void memory_clear(Task_list *task);
