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
    for(int i=0; i<BUFFER_SIZE; i++)
    {
        str[i] = str[i] + incrementer_value;
    }
}

int main() {

    pid_t pid;
    char buffer[BUFFER_SIZE];
    char data[] = "ihjfedcba.|987654321";

    // Create pipe
        //-----
        // TO DO
        //-----
    int p[2];

    if (pipe(p) == -1)
    {
        printf("error opening pipe!\n");
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

        printf("____P3 Parent Started____\n");

        //-----
        //TO DO
        //-----
        int fdread = open("R2.txt", O_RDONLY);

        read(fdread, buffer, len);

        write(p[1], buffer, len);
        sleep(1);

        read(p[0], buffer, len);

        int fdwrite = open("R3.txt", O_WRONLY);
        write(fdwrite, buffer, len);
        sleep(1);

        printf("____P3 Parent Ended____\n");

        exit(EXIT_SUCCESS);

    } else { // Child process
        
        printf("____P3 Child Started____\n");

        //-----
        //TO DO
        //-----
        read(p[0], buffer, len);
        buffer[len] = '\0';
        printf("Child received string from parent: %s\n", buffer);
        
        //-----
        //TO DO
        //-----

        // check for match of strings
        int f=0;
        for(int i=0; i<BUFFER_SIZE; i++)
        {
            if(buffer[i] != data[i])
            {
                f=1;
                break;
            }
        }

        if(f==0)
        {
            modifyString(buffer, 3);
        }
        else
        {
            modifyString(buffer, 2);
        }

        // sending results back to parent
        write(p[1], buffer, len);
        sleep(1);

        printf("Child send string to parent: %s\n", buffer);
        
        printf("____P3 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
