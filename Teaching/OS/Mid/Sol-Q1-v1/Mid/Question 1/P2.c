#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>


#define BUFFER_SIZE 20

void reverseString(char* str) {
    //-----
    //TO DO
    //-----
    int m = 0;

    for(int i=BUFFER_SIZE-1; i>BUFFER_SIZE/2; i--)    {
        char temp = str[i];
        str[i] = str[m];
        str[m] = temp;
        m++;
    }
}

int main() {

    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create pipe
    //-----
    // TO DO
    //-----
    int p[2];

    if (pipe(p)==-1)
    {
        printf("error creating pipe!\n");
        exit(1);
    }

    // Fork a child process
    // Create pipe
    //-----
    // TO DO
    //-----

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    int len = BUFFER_SIZE;

    if (pid > 0) { // Parent process

        printf("____P2 Parent Started____\n");

        //-----
        //TO DO
        //-----
        int fdread = open("R1.txt", O_RDONLY);

        read(fdread, buffer, len);
        buffer[len] = '\0';

        write(p[1], buffer, len);
        sleep(1);

        read(p[0], buffer, len);

        int fdwrite = open("R2.txt", O_WRONLY);
        write(fdwrite, buffer, len);
        sleep(1);

        printf("____P2 Parent Ended____\n");

        exit(EXIT_SUCCESS);

    } else { // Child process
        
        printf("____P2 Child Started____\n");

        //-----
        //TO DO
        //-----
        read(p[0], buffer, len);
        buffer[len] = '\0';

        printf("Child received string from parent: %s\n", buffer);
        
        //-----
        //TO DO
        //-----
        reverseString(buffer);

        printf("Child send string to parent: %s\n", buffer);
        write(p[1], buffer, len);
        sleep(1);

        
        printf("____P2 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
