#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_prompt(void){ 

    //set usrname, machine name and PWD

    char *usr = getenv("USER"); 
    char *machine = getenv("MACHINE");
    char *pwd = getenv("PWD");
    //error checking

    if (usr == NULL){
        usr = "unknown";
    }

    if (machine == NULL){
        machine = getenv("HOSTNAME");
        if(machine == NULL){
            machine = "localhost";
        }
    }

    char cwd_buffer[1024];
    if (pwd == NULL) {
        if (getcwd(cwd_buffer, sizeof(cwd_buffer)) != NULL) {
            pwd = cwd_buffer;
        } else {
            pwd = "unknown";
        }
    }

    printf("%s@%s:%s> ", usr, machine, pwd);
    fflush(stdout); //flush stdout to prevent newline
}

