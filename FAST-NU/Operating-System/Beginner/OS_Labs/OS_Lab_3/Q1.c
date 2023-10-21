#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	pid_t PID;
	PID = fork();

	if (PID == 0)
		for (int i = 0; i < 100; i++)
			printf("%d\t[ I am a child process ]\n", i + 1);
	else
	{
		wait(NULL);
		printf("====================================\n");
		for (int i = 0; i < 100; i++)
			printf("%d\t[ I am a parent process ]\n", i + 1);
	}

	return 0;
}
