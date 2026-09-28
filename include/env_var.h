#ifndef ENV_VAR_H
#define ENV_VAR_H

void handle_environment_variables(char *tokens[], char *allocated_tokens[]);
void free_expanded_tokens(char *allocated_tokens[]);
void tokenize(char *input, char *tokens[]);

#endif