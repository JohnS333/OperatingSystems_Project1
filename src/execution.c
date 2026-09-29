#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jobs.h"


void execute_command(char *path, char *argv[], bool is_background,
					 char *command_line) {
	int status;
	// what happens if you don't fork? - The shell will convert into the executed command, losing its own identity, 
	// no longer allowing the shell to continue executing other commands.
	//therefore we must fork
	pid_t pid = fork();

	if (pid < 0) { //if fork failed
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0) { //if this is the child process
		execv(path, argv);
		perror("Exec failed");
		_exit(127);
	}
	if (!is_background) {
		if (waitpid(pid, &status, 0) < 0) {
			perror("Waitpid failed");
		}
	} else {
		check_jobs();
		int jobnum = add_job(pid, command_line);
		if (jobnum < 0) {
			perror("Failed to add job to array");
		}
		else {
		printf("[%d] %d\n", jobnum, pid);
		}
	}
}

