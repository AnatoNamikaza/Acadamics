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
    for(int i=0; i<BUFFER_SIZE; i++)
    {
        if(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')))
        {
            if(i%2==0)  str[i] = '-';
            if(i%2==1) str[i] = '.';
        }
    }

}

int main (){
    
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char data[] = "123456789|.abcdefjhi";

    // Create pipe
    //-----
    //TO DO
    //-----
    int p[2];

    if (pipe(p) == -1)
    {
        printf("error in opening pipe!\n");
        exit(1);
    }

    // Fork a child process
    // Create pipe
    //-----
    // TO DO
    //-----


    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    int len = BUFFER_SIZE;

    if (pid == 0)
    { // Child process
        int signal = 0;
        int fdread = open("R3.txt", O_RDONLY);

        printf("____P1 Child Started____\n");

        //-----
        //TO DO
        //-----
        read(p[0], &signal, sizeof(int));
        close(p[0]);
        // check if signal recieved from parent
        if(signal) 
        {
            // reading contents of file R3.txt
            read(fdread, buffer, len);
            buffer[len] = '\0';
        
            printf("Child received string from parent: %s\n", buffer);
            modifyString(buffer);

            printf("Child send string to parent: %s\n", buffer);

            // sending results back to parent
            write(p[1], buffer, len);
            sleep(1);
            close(p[1]);
        }

        printf("____P1 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }
    else
    { // Parent process
        int signal = 1;

        printf("____P1 Parent Started____\n");

        //-----
        //TO DO
        //-----
        int fdwrite = open("R1.txt", O_WRONLY);
        if(!fdwrite)
        {
            printf("Error in opening file R1.txt!\n");
            exit(1);
        }

        write(fdwrite, data, len);
        sleep(1);

        // send signal to child
        write(p[1], &signal, sizeof(int));
        sleep(1);

        //-----
        //TO DO
        //-----
        read(p[0], buffer, len);

        int fdwriteresults = open("Results.txt", O_WRONLY);
        if (!fdwriteresults)
        {
            printf("Error in opening file Results.txt!\n");
            exit(1);
        }

        // writing to file
        write(fdwriteresults, buffer, len);
        sleep(1);

        // displaying the results
        write(1, buffer, len);
        sleep(1);
        printf("\n");

        printf("____P1 Parent Ended____\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}

