#include "macros.h"
#include "input_cmd.h"

typedef union {
    unsigned char tab_count;
    char prog_name[MAX_PROG_NAME_LEN];
    char* err;
} cmd_value;

typedef struct {
    cmd_value value;
    cmd_type type;
} Command;
