#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_background(void) {
	int status;
	pid_t pid = fork();

	if(pid == 0) { //if this is the child process
		sleep(3);
		printf("Child process\n");
	}
	else { //if this is the parent process
		waitpid(pid, &status, WNOHANG);
		printf("Parent process\n");
	}
}
