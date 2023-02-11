#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
	int shmid = shmget(77, 20, 0666 | IPC_CREAT);

	if (shmid != -1)
	{

		pid_t pid = fork();

		if (pid < 0)
		{
			std::cout << "Error!! Fork not working (-_-)\n";
			return 1;
		}

		else if (pid == 0)
		{
			std::cout << "\n------------ Child Process ------------\n";
			//Get a pointer to the shared memory region.
			int* Int_Arr = (int*)shmat(shmid, NULL, 0);

			std::cout << "Enter 5 integers: ";
			for (int i = 0; i < 5; i++)
				std::cin >> Int_Arr[i];

			std::cout << "Finished storing 5 integers in shared memory.\nThe 5 integers are:\n";
			for (int i = 0; i < 5; i++)
				std::cout << Int_Arr[i] << '\t';

			std::cout << std::endl;
			//Detaching shared memory region
			shmdt(Int_Arr);
		}

		else
		{
			wait(NULL);
			std::cout << "\n----------- Parent Process ------------\n";

			//Get a pointer to the shared memory region.
			int* Int_Arr = (int*)shmat(shmid, NULL, 0);

			int sum = 0;
			for (int i = 0; i < 5; i++)
				sum += Int_Arr[i];

			std::cout << "Sum of those 5 integers:\t" << sum << '\n';
			std::cout << "Average of those 5 integers:\t" << (sum / 5) << "\n\n";


			shmctl(shmid, IPC_RMID, NULL); //mark the shared region for deletion

			//detach
			shmdt(Int_Arr);
		}

	}

	return 0;
}