#include <stdlib.h>
#include "llists_internal.h"

char* get_prog_name(Task_list* task){
    return task->prog_name;
}

void insert(char* prog_name, Task_list** active_task_ptr){
    Task_list* new_ptr = malloc(sizeof(Task_list));
    
    if (!new_ptr){
        puts("Не удалось выделить память");
        memory_clear(*active_task_ptr);
        exit(1);
    }

    if(*active_task_ptr != NULL){
        new_ptr->next = *active_task_ptr;
        new_ptr->prev = (*active_task_ptr)->prev;
        (*active_task_ptr)->prev->next = new_ptr;
        (*active_task_ptr)->prev = new_ptr;
    }
    else{
        new_ptr->next = new_ptr;
        new_ptr->prev = new_ptr;
    }
    memcpy(new_ptr->prog_name, prog_name, sizeof(char)*MAX_PROG_NAME_LEN);  
    
    *active_task_ptr = new_ptr;
    // for(unsigned char i = 0; i < MAX_PROG_NAME_LEN; ++i)
    //     new_ptr->prog_name[i]=prog_name[i];
}

void shift(unsigned short index,  Task_list** active_task_ptr){
    Task_list* chosen_ptr = *active_task_ptr;
    
    for (unsigned short i = 0; i<index; ++i)
        chosen_ptr = chosen_ptr->next;
    
    chosen_ptr->next->prev = chosen_ptr->prev;
    chosen_ptr->prev->next = chosen_ptr->next;
    
    chosen_ptr->next=*active_task_ptr;
    chosen_ptr->prev=(*active_task_ptr)->prev;

    (*active_task_ptr)->prev->next = chosen_ptr;
    (*active_task_ptr)->prev = chosen_ptr;

    *active_task_ptr = chosen_ptr;
}

void memory_clear(Task_list* task){
    if (task == NULL) return;
    Task_list* temp;
    task->prev->next=NULL;
    while (task != NULL){
        temp = task->next;
        free(task);
        task = temp;
    }
}
