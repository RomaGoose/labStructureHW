#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "log.h"
#include "macros.h"
#include "include.h"

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

Command cmd_process(char* cmd_text){
    Command cmd;
    cmd.type = CMD_ERR;
    
    switch (cmd_text[0]){
        case('A'):
            if (*(cmd_text+1) == 'l' && *(cmd_text+2) == 't'){
                unsigned char curr_index = ALT_OFFSET;
                unsigned char tab_count = 0;
                
                while(curr_index < MAX_INPUT_LEN){
                    for (unsigned char i = 0; i < TAB_OFFSET; ++i){
                        if(cmd_text[curr_index + i] != TAB_SUBSTR[i]){
                                if(i == 0){
                                    cmd.type = ALT;
                                    cmd.value.tab_count = (curr_index - ALT_OFFSET)/TAB_OFFSET;
                                    return cmd;
                                }
                                cmd.type = LEN_WARN;
                                cmd.value.tab_count = (curr_index - ALT_OFFSET)/TAB_OFFSET;
                                return cmd;
                            }
                        }
                    curr_index += TAB_OFFSET;
                } 
                cmd.type = LEN_WARN;
                cmd.value.tab_count = (curr_index - ALT_OFFSET)/TAB_OFFSET;
                return cmd;
            }
            return cmd;
        case('S'):
            for (unsigned char i = 1; i < START_OFFSET; ++i)
                if(cmd_text[i] != START_SUBSTR[i]) return cmd;
            
            memcpy(cmd.value.prog_name, cmd_text+START_OFFSET, sizeof(char)*MAX_PROG_NAME_LEN);
                // for (unsigned char i = 0; i < MAX_PROG_NAME_LEN; ++i)
                //     cmd.value.prog_name[i] = cmd_text[START_OFFSET + i];
            cmd.type = START;
            return cmd;
        default:
            return cmd;
    }
}

Command easy_scan(char* buff){
    setlocale(LC_ALL, "ru-RU.UTF-8");
    Clear();
    scanf("%[^\n]s", buff);
    Command cmd = cmd_process(buff);

    if (cmd.type == CMD_ERR){
        puts("Введена некорректная команда(доступны Start, Alt Tab). Учитывается регистр. Введите снова:");
        _LOG("WRN", "неверно введена команда");
        cmd = easy_scan(buff);
    }
    if (cmd.type == LEN_WARN){
        printf("При чтении команды возникла неоднозначность. Прочитанное кол-во Tab'ов: %u. Верно? (y или n) \n", cmd.value.tab_count);
        Clear();
        char answer;
        int scan = scanf("%[yn]c", &answer);
        while (scan!=1){
            printf("entered: %c\n", answer);
            puts("Введите ответ на вопрос. \"y\" или \"n\"");
            _LOG("WRN", "неверно на вопрос отвечает");
            Clear();
            scan = scanf("%[yn]c", &answer);
        }
        if (answer == 'y'){
            cmd.type = ALT;
            return cmd;
        }
        else {
            puts("Введите команду снова:");
            cmd = easy_scan(buff);
            return cmd;
        }
    }
    if (cmd.type == ALT || cmd.type == START) return cmd;
}
