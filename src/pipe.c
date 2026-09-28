#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "path_search.h"

void handle_pipes(char *argv[], bool is_background) {
    int first_pipe = -1;
    int second_pipe = -1;

    // Find the two |s in the tokenized command.
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            if (first_pipe == -1) {
                first_pipe = i;
            } else if (second_pipe == -1) {
                second_pipe = i;
            } else {
                fprintf(stderr, "A maximum of two pipes is supported\n");
                return;
            }
        }
    }

    if (first_pipe == -1 || argv[first_pipe + 1] == NULL ||
        (second_pipe != -1 && (argv[second_pipe + 1] == NULL || second_pipe == first_pipe + 1))) {
        fprintf(stderr, "Invalid pipe\n");
        return;
    }

    // Replace each | with NULL so each command has its own argv array.
    char **commands[3]; // this is an array of argv arrays for each command in the pipeline. 
    argv[first_pipe] = NULL; // this replaces the first pipe with a NULL terminator to separate the first command from the rest
    commands[0] = argv;

    if (second_pipe == -1) {
        commands[1] = &argv[first_pipe + 1];
        commands[2] = NULL;
    } else {
        argv[second_pipe] = NULL;
        commands[1] = &argv[first_pipe + 1]; //this sets the pointer to the position after the first pipe
        commands[2] = &argv[second_pipe + 1]; //this sets the pointer to the position after the second pipe
    }

    int command_count = second_pipe == -1 ? 2 : 3;
    char *paths[3] = {NULL, NULL, NULL};

    // Find a full path for every command before creating the children.
    for (int i = 0; i < command_count; i++) {
        paths[i] = find_command_path(commands[i][0]);
        if (paths[i] == NULL) {
            fprintf(stderr, "Command not found: %s\n", commands[i][0]);
            for (int j = 0; j <= i; j++) {
                free(paths[j]);
            }
            return;
        }
    }

    // Two commands need one pipe; three commands need two pipes.
    int pipes[2][2];
    // the initial values of the pipes array are undefined, so we need to create the pipes before using them.
    // this array will store the file descriptors for the pipes used in the pipeline.
    // pipes[i][0]  read end
    // pipes[i][1]  write end
    for (int i = 0; i < command_count - 1; i++) { // for every command
        if (pipe(pipes[i]) == -1) { // create pipe and check for failure
            perror("pipe");
            for (int j = 0; j < i; j++) {
                 close(pipes[j][0]);
                 close(pipes[j][1]);
             }
            for (int j = 0; j < command_count; j++) {
                free(paths[j]);
            }
            return;
        }
        // if pipe succeeded to create then 
        // pipe[i][0] == read end desc 
        // pipe[i][1] == write end desc.
    }

    pid_t children[3]; //this array will store the PIDs of the child processes created for each command in the pipeline.
    for (int command = 0; command < command_count; command++) {
        children[command] = fork();
        // each child process continues from the point where it was forked.

        if (children[command] == -1) {
            perror("fork");
            for (int i = 0; i < command_count - 1; i++) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            for (int j = 0; j < command_count; j++) {
                free(paths[j]);
            }
            return;
        }

        if (children[command] == 0) {
            // children[command #] should return 0 if it is the child process for the current command.
            // Every command after the first reads from the previous pipe.
            if (command > 0) {
                dup2(pipes[command - 1][0], STDIN_FILENO);
                // this only executes on the 2nd command and beyond, not on the first command.
                //This ensures that the current command reads from the previous command's output.
                //Make standard input (STDIN_FILENO, descriptor 0) read from the previous pipe.
            }

            // Every command before the last writes to the next pipe.
            if (command < command_count - 1) {  // this only executes on all commands except the last one, which does not write to any pipe.
                dup2(pipes[command][1], STDOUT_FILENO);
                //This ensures that the current command writes to the next command's input.
                //Make standard output (STDOUT_FILENO, descriptor 1) write to the next pipe.
            }

            // The duplicates now replace stdin/stdout, so close all originals.
            for (int i = 0; i < command_count - 1; i++) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            execv(paths[command], commands[command]);
            perror("execv");
            _exit(127);
        }
    }

    // The shell parent must close its copies and wait for all pipeline commands.
    for (int i = 0; i < command_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    if (!is_background) {
    for (int i = 0; i < command_count; i++) { // if this process is not background, wait for all child processes
        waitpid(children[i], NULL, 0);
        
    }
    }
    for (int i = 0; i < command_count; i++) {
        free(paths[i]);
    }

}

}