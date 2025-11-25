#pragma once

typedef struct _Task_list Task_list;

void insert(char* prog_name, Task_list** active_task_ptr);
void shift(unsigned short index, Task_list** active_task_ptr);

char* get_prog_name(Task_list* task);
void memory_clear(Task_list* task);
