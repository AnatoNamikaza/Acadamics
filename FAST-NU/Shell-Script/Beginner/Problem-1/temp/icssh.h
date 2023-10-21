#ifndef ICSSH_H
#define ICSSH_H

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define RD_ERR "REDIRECTION ERROR: Invalid operators or file combination.\n"
#define BG_TERM "Background process %d: %s, has terminated.\n"
#define DIR_ERR "DIRECTORY ERROR: Directory does not exist.\n"
#define EXEC_ERR "EXEC ERROR: Cannot execute %s.\n"
#define WAIT_ERR "WAIT ERROR: An error ocured while waiting for the process.\n"
#define PID_ERR "PROCESS ERROR: Process pid does not exist.\n"
#define PIPE_ERR "PIPE ERROR: Invalid use of pipe operators.\n"

#ifdef DEBUG
#define SHELL_PROMPT "<53shell>$ "
#else
#define SHELL_PROMPT "<53shell >$"
#endif

typedef struct proc_info {
	char *in_file;                // name of file that stdin redirects from
	char *out_file;               // name of file that stdout redirects to
	char *err_file;               // name of file that stderr redirects to
	char *outerr_file;            // name of file that both stderr and stdout redirect to
	int argc;                     // number of args
	char **argv;                  // arguments for program; argv[0] is the program to run
	char *cmd;                    // name of the program (argv[0])
	struct proc_info *next_proc;  // next program (process) in job; NULL if this is the last one
} proc_info;

typedef struct {
	bool bg;           // is this a background job?
	char *line;        // original commandline for this job
	int nproc;         // number of processes in this job
	proc_info *procs;  // list of processes in this job
} job_info;

typedef struct bgentry {
	job_info *job;   // the job that the bgentry refers to
	pid_t pid;       // pid of the (first) background process
	time_t seconds;  // time at which the command recieved by the shell
} bgentry_t;

/*
 * Print a job_info stuct for information and debugging purposes
 */
void debug_print_job(job_info *job);

/*
 * Free a job_info struct
 */
void free_job(job_info *job);

/* 
 * Accepts a command line and validates it.
 * Returns a valid job_info struct if successful, 
 * returns NULL if any error occurs.
 */
job_info *validate_input(char *line);

/* 
 * Prints out a single bgentry struct to STDERR
 */
void print_bgentry(bgentry_t *p);

/*
 * Prints message to STDERR prior to termination. 
 * Let's you know the SEGFAULT occured in your shell code, not the grader.
 */
void sigsegv_handler();

#endif
