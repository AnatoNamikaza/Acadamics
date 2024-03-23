#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 20

void modifyString(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isalnum(str[i]))
        {
            if (i % 2)
                str[i] = '.';
            else
                str[i] = '-';
        }
    }
}
#define fl fflush(stdout), fflush(stdin);
int main()
{

    pid_t pid;
    char buffer[BUFFER_SIZE];
    char data[] = "123456789|.abcdefjhi";
    int pipe1[2];
    pipe(pipe1);
    int pipe2[2];
    pipe(pipe2);

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { // Child process
        sleep(1);
        printf("____P1 Child Started____\n");
        close(pipe1[1]);
        read(pipe1[0], buffer, sizeof(buffer));
        close(pipe1[0]);
        int fd = open("R3.txt", O_RDONLY);
        ssize_t byt = read(fd, buffer, sizeof(buffer));

        modifyString(buffer);

        close(pipe2[0]);
        write(pipe2[1], buffer, byt);
        close(pipe2[1]);

        printf("____P1 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }
    else
    { // Parent process

        printf("____P1 Parent Started____\n");
        int fd = open("R1.txt", O_CREAT | O_WRONLY, 0644);
        write(fd, data, sizeof(data) - 1);
        close(fd);
        close(pipe1[0]);
        char buf[] = "Sent Data\0";
        write(pipe1[1], buf, 11);
        close(pipe1[1]);

        //-----
        // TO DO
        //-----

        printf("Child received string from parent: %s\n", buf);
        wait(NULL);
        close(pipe2[1]);
        ssize_t byt = read(pipe2[0], buffer, sizeof(buffer));
        buffer[byt] = '\0';
        close(pipe2[0]);

        printf("Child send string to parent: %s\n", buffer);

        fd = open("Results.txt", O_CREAT | O_WRONLY, 0644);
        write(fd, buffer, byt);
        close(fd);

        printf("____P1 Parent Ended____\n");
        exit(0);
    }

    return 0;
}
