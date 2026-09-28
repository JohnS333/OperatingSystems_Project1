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


void handle_tilde_expansion(char *tokens[], char *allocated_tokens[]) {
    char *home = getenv("HOME");
    if (!home) home = "";

    for (int i = 0; tokens[i] != NULL; i++) {
        
        if (strcmp(tokens[i], "~") == 0) { //standalone case
            tokens[i] = home;
        } 
        
        else if (tokens[i][0] == '~' && tokens[i][1] == '/') {
            
            size_t size = strlen(home) + strlen(tokens[i]);
            char *expanded = malloc(size);
            if (expanded) {
                snprintf(expanded, size, "%s%s", home, tokens[i] + 1);
                tokens[i] = expanded; 
                allocated_tokens[i] = expanded;
            }
        }
    }
}

void handle_environment_variables(char *tokens[], char *allocated_tokens[]) {
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

    handle_tilde_expansion(tokens, allocated_tokens);
}

void free_expanded_tokens(char *allocated_tokens[]) {
    for (int i = 0; i < 1024; i++) {
        free(allocated_tokens[i]);
    }
}


