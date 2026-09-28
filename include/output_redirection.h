#ifndef OUTPUT_REDIRECTION_H
#define OUTPUT_REDIRECTION_H

#include <stdbool.h>

void handle_redirection(char *path, char *argv[], bool is_background, char *command_line);

#endif