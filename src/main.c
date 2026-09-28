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
#include "pipe.h"
#include "output_redirection.h"
#include "cd.h"
#include "jobs.h"

const int MAX_JOBS = 10;

#define MAX_HISTORY 3
#define MAX_COMMAND_LENGTH 200

static char command_history[MAX_HISTORY][MAX_COMMAND_LENGTH];
static int history_count = 0;
static void add_command_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        strncpy(command_history[history_count], command, MAX_COMMAND_LENGTH - 1);
        command_history[history_count][MAX_COMMAND_LENGTH - 1] = '\0'; // Ensure null termination
        history_count++;
    } else {
        // Shift commands up to make room for the new command
        for (int i = 1; i < MAX_HISTORY; i++) {
            strncpy(command_history[i - 1], command_history[i], MAX_COMMAND_LENGTH);
        }
        strncpy(command_history[MAX_HISTORY - 1], command, MAX_COMMAND_LENGTH - 1);
        command_history[MAX_HISTORY - 1][MAX_COMMAND_LENGTH - 1] = '\0'; // Ensure null termination
    }
}

static void print_command_history(void) {
    if (history_count == 0) {
        printf("No valid commands.\n");
        return;
    }
    for (int i = 0; i < history_count; i++) {
        printf("%s\n", command_history[i]);
    }
}

struct job {
    int job_number;       // 1, 2, 3...
    pid_t pid;             // or process group ID
    char *command;         // display text for jobs
    int status;            // running, done, stopped, etc.
};


int main(void) {
    
    while (true){
        char *buffer = NULL;
        size_t bufsize = 0; 
        ssize_t characters;
        bool has_redirection = false;
        check_jobs();
        print_prompt();
        //Read the complete line from standard input and store it in the buffer
        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1) {
            free(buffer);
            printf("\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // this removes the newline character from the end of the buffer (replaced with a null terminator)
        char *command_line = strdup(buffer);
        if (command_line == NULL) {
            perror("strdup");
            free(buffer);
            continue;
        }
        if (strlen(buffer) > 0){
            char *argv[1024];   //establish the array of tokenized command arguments
            char *allocated_tokens[1024] = {NULL};
            tokenize(buffer, argv);
            handle_environment_variables(argv, allocated_tokens); // this function modifies argv and tracks allocated expansions
            if (argv[0] == NULL) {
                free_expanded_tokens(allocated_tokens);
                free(command_line);
                free(buffer);
                continue;
            }
            // Check if the command is "cd" and handle it separately
            if (strcmp(argv[0], "cd") == 0) {
                handle_cd(argv);
                free_expanded_tokens(allocated_tokens);
                free(command_line);
                free(buffer);
                continue;
            }
            // Check if the command is "exit" and handle it separately
            if (strcmp(argv[0], "exit") == 0) {
                wait_for_jobs();
                print_command_history();

                free_expanded_tokens(allocated_tokens);
                free(command_line);
                free(buffer);
                break;
            }
            // Check if the command is "jobs" and handle it separately
            if (strcmp(argv[0], "jobs") == 0) {
                check_jobs();
                print_jobs();
                free_expanded_tokens(allocated_tokens);
                free(command_line);
                free(buffer);
                continue;
            }

            //Is the command a path or just a command name?
            if (strchr(argv[0], '/') == NULL) {
                // The command is not a path, search in PATH
                
                if (search_path(argv[0]) != 0) {
                    fprintf(stderr, "Command not found: %s\n", argv[0]);
                    free_expanded_tokens(allocated_tokens);
                    free(command_line);
                    free(buffer);
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
            // Add the command to history after passing through validation
            add_command_history(command_line);
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
                    argv[i] = NULL; // Remove the '&' from the argument list
                    break;
                }
            }

            if (has_piping) {
                // handle_pipes finds the path for every command in the pipeline.
                handle_pipes(argv, is_background, command_line);
            } else {
                if (has_redirection) {
                    char *path = find_command_path(argv[0]);
                    if (path == NULL) {
                        fprintf(stderr, "%s: command not found\n", argv[0]);
                        free_expanded_tokens(allocated_tokens);
                        free(command_line);
                        free(buffer);
                        continue;
                    }
                    handle_redirection(path, argv, is_background, command_line);
                    free(path);
                } else {
                    char *path = find_command_path(argv[0]);
                    if (path == NULL) {
                        fprintf(stderr, "%s: command not found!\n", argv[0]);
                        free_expanded_tokens(allocated_tokens);
                        free(command_line);
                        free(buffer);
                        continue;
                    }
                        execute_command(path, argv, is_background, command_line);
                    free(path);
                }
            }
            free_expanded_tokens(allocated_tokens);
        }

        free(command_line);
        free(buffer);
    }

    return 0;
}

