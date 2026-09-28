//This file handles searching for executables in the PATH environment variable
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char *find_command_path(const char *command) {
	//This function searches for the given command in the directories listed in the PATH environment variable, and returns a pointer to the full path of the command if found, or NULL if not found.

	//first check if the input contains /'s already, in which case we can directly check if it is executable
	if (strchr(command, '/') != NULL) {
		if (access(command, X_OK) == 0) {
			return strdup(command); // we just return it as is
		}
		return NULL;
	}

	char *path = getenv("PATH");
	if (path == NULL) {
		fprintf(stderr, "PATH environment variable not set\n");
		return NULL;
	}
	char *path_copy = strdup(path);
	if (path_copy == NULL) {
		fprintf(stderr, "Failed to duplicate PATH string\n");
		return NULL;
	}
	char *token = strtok(path_copy, ":"); //Char* because strtok returns a pointer to the next token in the string
	while (token != NULL) {
		char full_path[1024];  //1024 is the maximum length of the full path
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0) {
			free(path_copy);
			return strdup(full_path); // Return a copy of the full path of the found command
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL; // Command not found in the PATH
}


int search_path(const char *executable) {
	//This function searches for the given executable in the directories listed in the PATH environment variable, and returns 0 if found, -1 if not found.
    char *path = find_command_path(executable);

    if (path == NULL) {
        return -1;
    }

    free(path);
    return 0;
}
