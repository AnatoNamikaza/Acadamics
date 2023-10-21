#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int Integer_Sum(int* arr, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += arr[i];

	return sum;
}

int Integer_Max(int* arr, int size) {
	int max = -1;
	for (int i = 0; i < size; i++)
		if (max < arr[i])
			max = arr[i];

	return max;
}


int main(int arg, char* argv[]) {

	if (arg == 1)
		printf("Integer array was not given.\n");
	else
	{
		printf("No of integers in the given array:%d \n", arg);
		int* arr = malloc((arg - 1) * sizeof * arr);
		for (int i = 0; i < arg - 1; i++)
			arr[i] = atoi(argv[i + 1]);
		printf("Given Array: \n");
		for (int i = 0; i < arg - 1; i++)
			printf("%d ", arr[i]);
		printf("\n");

		pid_t PID;
		PID = fork();

		if (PID == 0)  //  child process
			printf("\n1st child process:\nSum of all element of Array: %d \n\n",
				Integer_Sum(arr, arg - 1));

		else if (PID > 0) { // PARENT PROCESS
			pid_t PID2 = fork();

			if (PID2 == 0)  // second child
				printf("\n2nd child process:\nAvg. of all element of Array: %d \n\n",
					Integer_Sum(arr, arg - 1) / (arg - 1));

			else if (PID2 > 0) {// parent process
				wait(NULL);
				pid_t PID3 = fork(); // third child;
				if (PID3 == 0) { // third child
					printf("\n3rd child process:\nMax of all element of Array: %d \n",
						Integer_Max(arr, arg - 1));
				}
			}
		}
		free(arr);
	}

	return 0;
}
