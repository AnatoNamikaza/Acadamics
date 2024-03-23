#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 30

void reverseString(char *str)
{

    char rev[strlen(str)];
    for (int i = 0; str[i] != '\0'; i++)
    {
        rev[i] = str[i];
    }
    int n = strlen(str);
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = rev[n - i - 1];
    }
}

int main()
{

    pid_t pid;
    char buffer[BUFFER_SIZE];
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

    if (pid > 0)
    { // Parent process

        printf("____P2 Parent Started____\n");
        int fd = open("R1.txt", O_RDONLY);

        ssize_t byt = read(fd, buffer, sizeof(buffer));
        close(fd);
        close(pipe2[0]);
        write(pipe2[1], buffer, byt);
        close(pipe2[1]);

        close(pipe1[1]);
        byt = read(pipe1[0], buffer, sizeof(buffer));
        close(pipe1[0]);

        fd = open("R2.txt", O_CREAT | O_WRONLY, 0644);
        write(fd, buffer, byt);
        close(fd);
        wait(NULL);

        printf("____P2 Parent Ended____\n");

        exit(EXIT_SUCCESS);
    }
    else
    { // Child process

        printf("____P2 Child Started____\n");

        close(pipe2[1]);
        ssize_t byt = read(pipe2[0], buffer, sizeof(buffer));
        close(pipe2[0]);
        buffer[byt] = '\0';

        printf("Child received string from parent: %s\n", buffer);

        reverseString(buffer);

        close(pipe1[0]);
        write(pipe1[1], buffer, byt);
        close(pipe1[1]);

        printf("Child send string to parent: %s\n", buffer);

        printf("____P2 Child Ended____\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}
