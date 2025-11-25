#include "input_cmd.h"
#include "macros.h"

typedef union cmd_value {
  unsigned char tab_count;
  char prog_name[MAX_PROG_NAME_LEN];
  char *err;
} cmd_value;

typedef struct Command {
  cmd_value value;
  cmd_type type;
} Command;
