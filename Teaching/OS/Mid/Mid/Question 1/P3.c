#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 20

void modifyString(char* str, int incrementer_value) {
    //-----
    //TO DO
    //-----
}

int main() {

    pid_t pid;
    char buffer[BUFFER_SIZE];
    char data[] = "ihjfedcba.|987654321";
    
    // Create pipe
    //-----
    //TO DO
    //-----

    // Fork a child process
    //-----
    //TO DO
    //-----
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process

        printf("____P3 Parent Started____\n");

        //-----
        //TO DO
        //-----

        printf("____P3 Parent Ended____\n");

        exit(EXIT_SUCCESS);

    } else { // Child process
        
        printf("____P3 Child Started____\n");

        //-----
        //TO DO
        //-----

        printf("Child received string from parent: %s\n", buffer);
        
        //-----
        //TO DO
        //-----

        printf("Child send string to parent: %s\n", buffer);
        
        printf("____P3 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }
    
    return 0;
}