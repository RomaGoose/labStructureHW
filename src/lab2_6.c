#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h> 
#include "..\includes\macros.h"
#include "..\includes\include.h"
#include "..\includes\log.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    FILE* log_file= fopen(LOG_FILE_NAME, "a");
    
    if(log_file == NULL){
        printf("Не удалось открыть фалй для журналирования: %s\n", LOG_FILE_NAME);
        Sleep(2000);
        exit(1);
    }
    
    _LOG("DBG", "запуск программы (START)");
    // ask if tab_number or progname is correct if not try to scan again
    // also the first command shiould be start i guess
    
    char buff[MAX_INPUT_LEN];
    unsigned short N;
    
    int scan = scanf("%u", &N);
    while (scan != 1 || !(MIN_NUMBER_OF_INPUTS <= N && N <= MAX_NUMBER_OF_INPUTS)){
        _LOG("WRN", "введено некорректное значение N");
        puts("Введите корректное значение N:");
        Clear();
        scan = scanf("%u", &N);
    }
    
    char (*output)[MAX_PROG_NAME_LEN] = calloc(N, sizeof(char)*MAX_PROG_NAME_LEN);
    Command cmd;
    Task_list* active_task = NULL;
    char first_cmd_failed;
    for (unsigned short i= 0; i < N; ++i){
        cmd = easy_scan(buff);
        first_cmd_failed = 0;
        switch (cmd.type){
            case(ALT):
                if (i == 0){
                    _LOG("WRN","ввел альт таб первой командой");
                    puts("Нельзя вводить АльтТаб без открытых окон. Введите снова:");
                    first_cmd_failed = 1;
                    --i;
                    break;
                }
                shift(cmd.value.tab_count, &active_task);
                break;
            case(START):
                insert(buff+START_OFFSET, &active_task);
                break;
            default:
                memory_clear(active_task);
                puts("непредвиденная ошибка");
                
                _LOG("DBG", "конец программы");
                exit(1);
                break;
        }
        
        if(!first_cmd_failed){
        memcpy(output[i], active_task->prog_name, MAX_PROG_NAME_LEN);
        output[i][MAX_PROG_NAME_LEN] = '\0';
        }
    }
    
    puts("-------------------------------");
    memory_clear(active_task);
    for(unsigned short i= 0; i < N; ++i)
        printf("%s\n", output[i]);

    _LOG("DBG", "конец программы (END)");
    free(output);
    return 0;

}