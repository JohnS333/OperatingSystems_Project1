#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void tokenize(char *input, char *tokens[]) {
    int i = 0;
    char *token = strtok(input, " \t");
    
    while (token != NULL && i < 1024 - 1) {
        tokens[i] = token; 
        i++;
        token = strtok(NULL, " \t"); 
    }
    
    tokens[i] = NULL; 
}

void handle_environment_variables(char *input) {
    char *tokens[1024];

    tokenize(input, tokens);
    
    for (int i = 0; tokens[i] != NULL; i++) {
        if (tokens[i][0] == '$') {
            
            char *var_name = tokens[i] + 1;
            char *env_val = getenv(var_name);
            
            if (env_val != NULL) {
                tokens[i] = env_val;    
            } else {
                tokens[i] = "";
            }
        }
    }

    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");
}
