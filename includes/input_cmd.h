#pragma once

typedef enum { ALT, START, CMD_ERR, LEN_WARN } cmd_type;
typedef union cmd_value cmd_value;
typedef struct Command Command;

Command cmd_process(char *cmd_text);
Command easy_scan(char *buff);
void get_N(unsigned short *N);

void process_input_to_output(unsigned short N, char (*output)[]);
