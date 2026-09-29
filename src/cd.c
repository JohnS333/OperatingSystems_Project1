#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int handle_cd(char *argv[]) 
{
    const char *target;
    if (argv[1] != NULL && argv[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
        return -1;
    }

    if (argv[1] == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return -1;
        }
    }else {
        target = argv[1];
    }

    if (chdir(target) != 0) {
        perror("cd failed");
        return -1;
    }

    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if (setenv("PWD", cwd, 1) != 0) {
            perror("cd: could not set PWD environment variable");
        }
    }

    return 0;
}