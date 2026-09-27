#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void handle_redirection(char *path, char *argv[])
{
	char *input_file = NULL;
	char *output_file = NULL;
	char *command_argv[1024];
	int command_argc = 0;

	for (int i = 0; argv[i] != NULL; i++) {
		if (strcmp(argv[i], "<") == 0) {
			if (argv[i + 1] == NULL) {
				fprintf(stderr, "redirection: missing input file\n");
				return;
			}

			input_file = argv[++i];
				
		}

		else if (strcmp(argv[i], ">") == 0) {
			if (argv[i + 1] == NULL) {
				fprintf(stderr, "redirection: missing output file\n");
				return;
			}

			output_file = argv[++i];
		} 

		else {
			command_argv[command_argc++] = argv[i];
		}

	}

	command_argv[command_argc] = NULL;

	if (command_argc == 0) {
		fprintf(stderr, "redirection: missing command\n");
		return;
	}
    // Create child process to handle redirection and execute command
	pid_t pid = fork();

   	if (pid < 0) {
		perror("Fork failed");
		return;
	}
    //Child process
	if (pid == 0) {
		//Input redirection
		if (input_file != NULL) {
		int fd = open(input_file, O_RDONLY);

			if (fd < 0) {
				perror("Open failed");
				_exit(1);
			}
		
		struct stat file_info;

		if (fstat(fd, &file_info) < 0) {
			perror("Fstat failed");
			close(fd);
			_exit(1);
		}

		if (!S_ISREG(file_info.st_mode)) {
			fprintf(stderr, "redirection: input file is not a regular file\n");
			close(fd);
			_exit(1);
		}

		if (dup2(fd, STDIN_FILENO) < 0) {
			perror("Dup2 failed");
			close(fd);
			_exit(1);
		}

		close(fd);

	}
 
    //Output redirection
	if (output_file != NULL) {
		int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);

		if (fd < 0) {
			perror("Open output file failed");
			_exit(1);
		}

		if (fchmod(fd, 0600) < 0) {
                perror("Fchmod failed");
                close(fd);
                _exit(1);
        }

		if (dup2(fd, STDOUT_FILENO) < 0) {
			perror("Dup2 stdout failed");
			close(fd);
			_exit(1);
		}

		close(fd);
	}


	execv(path, command_argv);

		perror("Exec failed");
		_exit(127);
	}


	if (waitpid(pid, NULL, 0) < 0) {
		perror("Waitpid failed");
	}
	//^^ TODO:see if we can use execute_command() from execution.c here. instead 

	// Parent process continues here after the child has executed or failed
}
