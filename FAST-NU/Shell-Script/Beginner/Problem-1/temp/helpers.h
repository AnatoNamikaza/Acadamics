#ifndef helper_h
#define helper_h

#define EXIT_FAILURE 1
int no;
int back_g;
char hist[20][1000];
int hist_i;
pid_t SHELL_ID;

//char CURR_JOB[2000];

struct bg_job {
    char job_name[300];
    pid_t PID;  
};

typedef struct bg_job bg_job;
bg_job jobs[50];

// A header file for helpers.c
// Declare any additional functions in this file
/*******************HELPER FUNCTION************************/
int countDirectories(char * path); // return how many backslash exit in a path for indicate directories
int isPipingExist(char *str); // check is pipe symbol present in command line argument
void removeSpaces(char *str); // it will remove spaces from the command
char* copyStr(char* str);
int totalSpace(char* str); // return total Number of arguments
char* concatinate(char* str1, char *str2);
char** tokenizeSpace(const char* userCommand);
/**********************************************************/

int executeCd(char **argv); // it will execute cd command
void redirections(job_info* job); //redirection >, < etc
void resetRedirections(job_info* job); // reset redirection <, >

char **pipe_elements(char *input);
void piping(job_info*job, char *command);
void run(char **args, int no_args, int bg); // it will execute back ground and foreground processes
void executeExternalCommand(char * line,job_info * job); // it will execute external commands

void recursiveExecute(job_info * job, char* command); //this function will execute cd, redirection operators, piping and background Jobs
int executeCommand(job_info * job);

#endif
