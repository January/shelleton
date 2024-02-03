#include "shelleton.h"

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "command.h"
#include "execute.h"
#include "parsing_interface.h"
#include "memory_pool.h"

static ShelletonState state;

static void print_prompt()
{
  bool should_free = false;
  char *cwd = get_current_directory(&should_free);
  int current_directory_index = 0;

  char hostname[HOST_NAME_MAX];

  gethostname(hostname, HOST_NAME_MAX);

  for (int i = 0; hostname[i] != '\0'; ++i)
  {
    if (hostname[i] == '.')
    {
      hostname[i] = '\0';
      break;
    }
  }

  char* login = getlogin();

  assert(cwd != NULL);

  for (int i = 0; cwd[i] != '\0'; ++i)
  {
    if (cwd[i] == '/' && cwd[i] != '\0')
    {
      current_directory_index = i + 1;
    }
  }

  printf("[%s@%s: %s]$ ", login, hostname, cwd + current_directory_index);
  fflush(stdout);

  if (should_free)
  {
    free(cwd);
  }
}

ShelletonState initial_state()
{
  return (ShelletonState)
  {
    true,
    isatty(STDIN_FILENO),
    NULL};
}

bool is_running()
{
  return state.running;
}

char *get_command_string()
{
  return strdup(state.parsed_str);
}

bool is_tty()
{
  return state.is_a_tty;
}

void end_main_loop(int exit_status)
{
  state.running = false;
}

int main(int argc, char **argv)
{
  state = initial_state();
  construct_background_job_queue();

  if (is_tty())
  {
    puts("Hello and welcome to Shelleton, a simple shell made by Drew Fink.");
    puts("Type \"exit\" or \"quit\" to exit Shelleton.");
    puts("======================================");
    fflush(stdout);
  }

  atexit(destroy_parser);
  atexit(destroy_memory_pool);

  while (is_running())
  {
    if (is_tty())
    {
      print_prompt();
    }

    initialize_memory_pool(1024);

    CommandHolder *script;

    while ((script = parse(&state)) == NULL)
      ;
    run_script(script);

    destroy_memory_pool();
  }

  return EXIT_SUCCESS;
}
