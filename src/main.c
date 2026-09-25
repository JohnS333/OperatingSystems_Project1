#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "prompt.h"
#include "path_search.h"
#include "env_var.h"
#include "execution.h"
#include "env_var.h"



int main(void) {
    
    while (true){
        char *buffer = NULL;
        size_t bufsize = 0; 
        ssize_t characters;

        print_prompt();
        //Read the complete line from standard input
        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1) {
            free(buffer);
            printf("\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // this removes the newline character from the end of the buffer (replaced with a null terminator)
        
        if (strlen(buffer) > 0){
            char *argv[1024];   //establish the array of tokenized command arguments
            tokenize(buffer, argv);
            handle_environment_variables(argv); // this is function modifies the argv array by replacing environment variable names with their corresponding values
            if (argv[0] == NULL) {
                free(buffer);
                continue;
            }
            //Is the command a path or just a command name?
            if (strchr(buffer, '/') == NULL) {
                // The command is not a path, search in PATH
                
                if (search_path(buffer) != 0) {
                    fprintf(stderr, "Command not found: %s\n", buffer);
                    continue; // Skip to the next iteration of the while loop if the command is not found in PATH
                }
            }


            char *path = find_command_path(argv[0]); // the first command argument is the command name. we find the path

            if (path == NULL) {
                fprintf(stderr, "%s: command not found\n", argv[0]);
            } else {
                // External command execution
                execute_command(path, argv);
                free(path);
            }
                
        }

        free(buffer);
    }

    return 0;
}

