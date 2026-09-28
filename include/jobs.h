// jobs.h
#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>


int add_job(pid_t pid, const char *command);
void check_jobs(void);
int print_jobs(void);

#endif