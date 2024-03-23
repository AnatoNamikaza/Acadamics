#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 20

void modifyString(char* str) {
    //-----
    //TO DO
    //-----
}

int main (){
    
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char data[] = "123456789|.abcdefjhi";

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

    if (pid == 0) { // Child process

        printf("____P1 Child Started____\n");

        //-----
        //TO DO
        //-----

        printf("____P1 Child Ended____\n");

        exit(EXIT_SUCCESS);
        
    } else { // Parent process

        printf("____P1 Parent Started____\n");

        //-----
        //TO DO
        //-----

        printf("Child received string from parent: %s\n", buffer);
        
        //-----
        //TO DO
        //-----

        printf("Child send string to parent: %s\n", buffer);
        
        printf("____P1 Parent Ended____\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}

