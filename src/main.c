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
#include "pipe.h"
#include "output_redirection.h"




int main(void) {
    
    while (true){
        char *buffer = NULL;
        size_t bufsize = 0; 
        ssize_t characters;
        bool has_redirection = false;
        print_prompt();
        //Read the complete line from standard input and store it in the buffer
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
            if (strchr(argv[0], '/') == NULL) {
                // The command is not a path, search in PATH
                
                if (search_path(argv[0]) != 0) {
                    fprintf(stderr, "Command not found: %s\n", argv[0]);
                    continue; // Skip to the next iteration of the while loop if the command is not found in PATH
                }
            }
            // Check if the command has io redirection at all
            for (int i = 0; argv[i] != NULL; i++) {
                if (strcmp(argv[i], "<") == 0 || strcmp(argv[i], ">") == 0) {
                    has_redirection = true;
                    break;
                }
            }
            // Check if the command has piping at all
            bool has_piping = false;
            for (int i = 0; argv[i] != NULL; i++) {
                if (strcmp(argv[i], "|") == 0) {
                    has_piping = true;
                    break;
                }
            }
            bool is_background = false;
            for (int i = 0; argv[i] != NULL; i++) {
                if (strcmp(argv[i], "&") == 0) {
                    is_background = true;
                    break;
                }
            }

            if (has_piping) {
                // handle_pipes finds the path for every command in the pipeline.
                handle_pipes(argv);
            } else {
                if (has_redirection) {
                    char *path = find_command_path(argv[0]);
                    if (path == NULL) {
                        fprintf(stderr, "%s: command not found\n", argv[0]);
                        free(buffer);
                        continue;
                    }
                    handle_redirection(path, argv);
                    free(path);
                } else {
                    char *path = find_command_path(argv[0]);
                    if (path == NULL) {
                        fprintf(stderr, "%s: command not found!\n", argv[0]);
                        free(buffer);
                        continue;
                    }
                        execute_command(path, argv);
                    free(path);
                }
            }
                
        }

        free(buffer);
    }

    return 0;
}

