#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdbool.h>

void execute_command(char *path, char *argv[], bool is_background, char *command_line);

#endif