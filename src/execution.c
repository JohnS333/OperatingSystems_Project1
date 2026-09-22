#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
void execute_command(char *path, char *argv[]) {
	int status;
	// what happens if you don't fork? try running execv without it!
	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0) {
		execv(path, argv);
		perror("Exec failed");
		_exit(127);
	}
	if (waitpid(pid, &status, 0) < 0) {
		perror("Waitpid failed");
	}

}

