// jobs.c
#include "jobs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_CONCURRENT_JOBS 10

struct job {
    int job_number;
    pid_t pid;
    char *command;
    bool running;
};

static struct job jobs[MAX_CONCURRENT_JOBS];
static int job_count = 0;
static int next_job_number = 1;

int add_job(pid_t pid, const char *command) {
    if (job_count >= MAX_CONCURRENT_JOBS) {
        fprintf(stderr, "Maximum number of jobs reached\n");
        return -1;
    }
    struct job *job = &jobs[job_count];
    job->job_number = next_job_number++;
    job->pid = pid;
    job->command = strdup(command);
    job->running = true;
    job_count++;
    return job->job_number;
}

void check_jobs(void) { // this function checks the status of all jobs and removes completed ones
    // only prints the done status of completed jobs, and then removes them from the job list
    for (int i = 0; i < job_count;) {
        int status;
        pid_t result = waitpid(jobs[i].pid, &status, WNOHANG);

        if (result == jobs[i].pid) {
            printf("[%d] + done %s\n",
                   jobs[i].job_number,
                   jobs[i].command);

            free(jobs[i].command);

            for (int j = i; j < job_count - 1; j++) {
                jobs[j] = jobs[j + 1];
            }

            job_count--;
        } else {
            i++;
        }
    }
}


int print_jobs(void) {
    bool has_active_jobs = false;

    for (int i = 0; i < job_count; i++) {
        if (jobs[i].running) {
            printf("[%d]+ %d %s\n",
                   jobs[i].job_number,
                   jobs[i].pid,
                   jobs[i].command);
            has_active_jobs = true;
        }
    }

    if (!has_active_jobs) {
        printf("No active background processes.\n");
    }

    return 0;
}

void wait_for_jobs(void)
{
    for (int i = 0; i < job_count; i++) {
        int status;

        if (waitpid(jobs[i].pid, &status, 0) == -1) {
            perror("waitpid");
        }

        free(jobs[i].command);
    }

    job_count = 0;
}