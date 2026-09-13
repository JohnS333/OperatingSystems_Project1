#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_tokenization(void) {
	// show example of string tokenization
	char x[] = "ls -l -a";
	char *y = strtok(x, " ");
	while(y != NULL) {
		printf("%s\n", y);
		y = strtok(NULL, " ");
	}
}
