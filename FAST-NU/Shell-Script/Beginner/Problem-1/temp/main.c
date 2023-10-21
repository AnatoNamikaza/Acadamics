#include "icssh.h"
#include "helpers.h"
#include <readline/readline.h>
#include<readline/history.h>

int main(int argc, char* argv[]) {
	int exec_result;
	char* line;
#ifdef GS
    rl_outstream = fopen("/dev/null", "w");
#endif

	// Setup segmentation fault handler
	if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
		perror("Failed to set signal handler");
		exit(EXIT_FAILURE);
	}

    // print the prompt & wait for the user to enter commands string
	while (1) {
		line = readline(SHELL_PROMPT);
		add_history(line);
		// MAGIC HAPPENS! Command string is parsed into a job struct
		// Will print out error message if command string is invalid
		if(line != NULL){
			job_info* job = validate_input(line);
			
			if (job == NULL) { // Command was empty string or invalid
				free(line);
				continue;
			}
			debug_print_job(job);
			
			if(executeCommand(job)){ // //this function will execute cd, redirection operators, piping and background Jobs

				// example built-in: exit
				if (strcmp(job->procs->cmd, "exit") == 0) {
					// Terminating the shell
					free(line);
					free_job(job);
					validate_input(NULL);
					return 0;
				}
				executeExternalCommand(line, job); // execute external command;
				free_job(job);  // if a foreground job, we no longer need the data
			}
			resetRedirections(job); // reset directions
		}
	}
    // calling validate_input with NULL will free the memory it has allocated
    validate_input(NULL);

#ifndef GS
	fclose(rl_outstream);
#endif
	return 0;
}
