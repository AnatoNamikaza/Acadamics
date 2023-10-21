#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <wait.h>

using namespace std;

int compute2017balance(char* file)
{
	FILE *fin = fopen(file,"r");
	if(fin)
	{
		int sum = 0;
		for(int i  ; fscanf(fin,"%d", &i) == 1; )
		{
			sum = sum + i;
		}
		return sum;
	}
	else
	{
		cout << "File not opened" << endl;
		return -1;
	}
}

int compute2018balance(char* file)
{
	FILE *fin = fopen(file,"r");
	if(fin)
	{
		int sum = 0;
		for(int i  ; fscanf(fin,"%d", &i) == 1; )
		{
			sum = sum + i;
		}
		return sum;
	}
	else
	{
		cout << "File not opened" << endl;
		return -1;
	}
}

int main(int argc , char *argv[]) {

	int id_m_r_sem = shmget(5678 , sizeof(sem_t) * 2 , IPC_CREAT | 0666);
	sem_t *sem = (sem_t*)shmat(id_m_r_sem , NULL , 0);
	if (id_m_r_sem == -1)
	{
		cout<<"ERROR!" << endl;
		return 1;
	}
	sem_init(&sem[0] , 1 , 0);
	sem_init(&sem[1] , 1 , 1);

	int shmid = shmget(1234, 4 , IPC_CREAT | 0666);

	int fid = fork();
	if(fid < 0)
	{
		cout << "\nfork failed" << endl;
		return -1;
	}
	else if(fid > 0)
	{
		int* shm = (int*)shmat(shmid, NULL , 0);
		int sum = compute2018balance(argv[2]);
		wait(NULL);
		sem_wait(&sem[0]);
		sum = sum + shm[0];
		cout << "\nBalance at the end of 2018 = " << sum;
		cout << "\n(^-^)";
	}
	else  if (fid == 0)
	{
		int* shm = (int*)shmat(shmid, NULL , 0);
		sem_wait(&sem[1]);
		cout << "\nBalance at the start of 2017 = 0";
		*shm = compute2017balance(argv[1]);
		cout << "\nBalance at the end of 2017 = " << *shm;
		sem_post(&sem[0]);
	}
}