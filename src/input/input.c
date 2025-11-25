#include "input_cmd_internal.h"
#include "llist.h"
#include "log.h"
#include "macros.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>

Command cmd_process(char *cmd_text) {
  Command cmd;
  cmd.type = CMD_ERR;

  switch (cmd_text[0]) {
  case ('A'):
    if (*(cmd_text + 1) == 'l' && *(cmd_text + 2) == 't') {
      unsigned char curr_index = ALT_OFFSET;
      unsigned char tab_count = 0;

      while (curr_index < MAX_INPUT_LEN) {
        for (unsigned char i = 0; i < TAB_OFFSET; ++i) {
          if (cmd_text[curr_index + i] != TAB_SUBSTR[i]) {
            if (i == 0) {
              cmd.type = ALT;
              cmd.value.tab_count = (curr_index - ALT_OFFSET) / TAB_OFFSET;
              return cmd;
            }
            cmd.type = LEN_WARN;
            cmd.value.tab_count = (curr_index - ALT_OFFSET) / TAB_OFFSET;
            return cmd;
          }
        }
        curr_index += TAB_OFFSET;
      }
      cmd.type = LEN_WARN;
      cmd.value.tab_count = (curr_index - ALT_OFFSET) / TAB_OFFSET;
      return cmd;
    }
    return cmd;
  case ('S'):
    for (unsigned char i = 1; i < START_OFFSET; ++i)
      if (cmd_text[i] != START_SUBSTR[i])
        return cmd;

    memcpy(cmd.value.prog_name, cmd_text + START_OFFSET,
           sizeof(char) * MAX_PROG_NAME_LEN);
    // for (unsigned char i = 0; i < MAX_PROG_NAME_LEN; ++i)
    //     cmd.value.prog_name[i] = cmd_text[START_OFFSET + i];
    cmd.type = START;
    return cmd;
  default:
    return cmd;
  }
}

Command easy_scan(char *buff) {
  setlocale(LC_ALL, "ru-RU.UTF-8");
  Clear();
  scanf("%[^\n]s", buff);
  Command cmd = cmd_process(buff);

  if (cmd.type == CMD_ERR) {
    puts("Введена некорректная команда(доступны Start, Alt Tab). Учитывается "
         "регистр. Введите снова:");
    _LOG("WRN", "неверно введена команда");
    cmd = easy_scan(buff);
  }
  if (cmd.type == LEN_WARN) {
    printf("При чтении команды возникла неоднозначность. Прочитанное кол-во "
           "Tab'ов: %u. Верно? (y или n) \n",
           cmd.value.tab_count);
    Clear();
    char answer;
    int scan = scanf("%[yn]c", &answer);
    while (scan != 1) {
      printf("entered: %c\n", answer);
      puts("Введите ответ на вопрос. \"y\" или \"n\"");
      _LOG("WRN", "неверно на вопрос отвечает");
      Clear();
      scan = scanf("%[yn]c", &answer);
    }
    if (answer == 'y') {
      cmd.type = ALT;
      return cmd;
    } else {
      puts("Введите команду снова:");
      cmd = easy_scan(buff);
      return cmd;
    }
  }
  if (cmd.type == ALT || cmd.type == START)
    return cmd;
}

void get_N(unsigned short *N) {
  char buff[MAX_INPUT_LEN];
  int scan = scanf("%u", N);
  while (scan != 1 ||
         !(MIN_NUMBER_OF_INPUTS <= *N && *N <= MAX_NUMBER_OF_INPUTS)) {
    _LOG("WRN", "введено некорректное значение N");
    puts("Введите корректное значение N:");
    Clear();
    scan = scanf("%u", N);
  }
}

void process_input_to_output(unsigned short N,
                             char (*output)[MAX_PROG_NAME_LEN]) {
  char buff[MAX_INPUT_LEN];
  Command cmd;
  Task_list *active_task = NULL;
  char first_cmd_failed;
  for (unsigned short i = 0; i < N; ++i) {
    cmd = easy_scan(buff);
    first_cmd_failed = 0;
    switch (cmd.type) {
    case (ALT):
      if (i == 0) {
        _LOG("WRN", "ввел альт таб первой командой");
        puts("Нельзя вводить АльтТаб без открытых окон. Введите снова:");
        first_cmd_failed = 1;
        --i;
        break;
      }
      shift(cmd.value.tab_count, &active_task);
      break;
    case (START):
      insert(buff + START_OFFSET, &active_task);
      break;
    default:
      memory_clear(active_task);
      puts("непредвиденная ошибка");

      _LOG("DBG", "конец программы");
      exit(1);
      break;
    }

    if (!first_cmd_failed) {
      memcpy(output[i], get_prog_name(active_task), MAX_PROG_NAME_LEN);
      output[i][MAX_PROG_NAME_LEN] = '\0';
    }
  }

  memory_clear(active_task);
  puts("-------------------------------");
}
