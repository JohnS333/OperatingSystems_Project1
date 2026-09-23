#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "prompt.h"
#include "env_var.h"


int main(void) {
    
    while (true){
        char *buffer = NULL;
        size_t bufsize = 0; 
        ssize_t characters;

        print_prompt();
    
        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1) {
            free(buffer);
            printf("\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (strlen(buffer) > 0){
            handle_environment_variables(buffer);
        }

        free(buffer);
    }

    return 0;
}

