#pragma once
#include <stdio.h>

#define ALT_OFFSET 3
#define TAB_OFFSET 4
#define TAB_SUBSTR " Tab"
#define START_OFFSET 6
#define START_SUBSTR "Start "

#define MAX_NUMBER_OF_INPUTS 10000-1
#define MIN_NUMBER_OF_INPUTS 1
#define MAX_INPUT_LEN 32
#define MAX_PROG_NAME_LEN MAX_INPUT_LEN-START_OFFSET

#define Clear() do{char c; while((c=getchar())!=EOF && c != '\n');} while(0)


