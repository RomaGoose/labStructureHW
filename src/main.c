#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h> 

#include "macros.h"
#include "log.h"
#include "llist.h"
#include "input_cmd.h"

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    FILE* log_file= fopen(LOG_FILE_NAME, "a");
    
    if(log_file == NULL){
        printf("Не удалось открыть фалй для журналирования: %s\n", LOG_FILE_NAME);
        Sleep(2000);
        exit(1);
    }
    
    _LOG("DBG", "запуск программы (START)");
    
    unsigned short N;
    get_N(&N);
    
     
    char (*output)[MAX_PROG_NAME_LEN] = calloc(N, sizeof(char)*MAX_PROG_NAME_LEN);
    process_input_to_output(N, output);

    for(unsigned short i= 0; i < N; ++i)
        printf("%s\n", output[i]);

    _LOG("DBG", "конец программы (END)");
    free(output);
    return 0;

}