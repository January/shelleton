#ifndef SHELLETON_H
#define SHELLETON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "execute.h"

typedef struct ShelletonState
{
  bool running;
  bool is_a_tty;
  char* parsed_str;
} ShelletonState;

ShelletonState initial_state();

char* get_command_string();

bool is_running();

void end_main_loop();

#endif
