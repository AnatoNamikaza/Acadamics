#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <string>
using namespace std;

struct sems {
	sem_t binarySem, writerSem, readerSem, binarySemReader;
	char data[100];
	int i;
};

void* writer(void *arg){
	sems *sem = (struct sems *) arg;

	for (int i = 0; i < 100; i++){
		sem_wait(&sem->writerSem);
		srand((unsigned) time(0));
		char *num = new char[2];
		num[0] = (rand() % 6) + 1;
		num[1] = '\0';
		sem->data[sem->i++] = num[0];
		num[0] += 48;
		write(1, "Number ", strlen("Number "));
		write(1, num, strlen(num));
		write(1, "\n", strlen("\n"));
		delete[] num;
		sem_post(&sem->readerSem);
	}

	return NULL;
}

void* reader(void *arg) {
	sems *sem = (struct sems *) arg;

	for (int i = 0; i < 100; ){
		sem_wait(&sem->readerSem);
		sem_wait(&sem->binarySem);
		i++;

		int sum = 0;
		for (int j = 0; j < sem->i; j++)
			sum += sem->data[j];

		string str = to_string(sum);
		write(1, "Sum ", strlen("Sum "));
		write(1, str.data(), str.size());
		write(1, "\n", strlen("\n"));

		sem_post(&sem->binarySem);
		sem_post(&sem->writerSem);
	}

	return NULL;
}

int main(){
	//Creating SHM for struct sems
	int semID = shmget(80, sizeof(struct sems), IPC_CREAT | 0666);
	if (semID == -1){
		fprintf(stderr, "SHM creation failed!\n");
		return 1;
	}

	sems *sem = (sems *) shmat(semID, NULL, 0);

	//Initializing all semaphores
	sem_init(&sem->binarySem, 0, 1);
	sem_init(&sem->writerSem, 0, 1);
	sem_init(&sem->readerSem, 0, 0);
	sem_init(&sem->binarySemReader, 0, 1);

	pthread_t writerThread, readerThread;
	if (pthread_create(&writerThread, NULL, &writer, sem) != 0 || pthread_create(&readerThread, NULL, &reader, sem) != 0){
		fprintf(stderr, "Thread creation failed!\n");
		return 1;
	}

	pthread_join(writerThread, NULL);
	pthread_join(readerThread, NULL);

	//Destroying all semaphores
	sem_destroy(&sem->binarySem);
	sem_destroy(&sem->writerSem);
	sem_destroy(&sem->readerSem);
	sem_destroy(&sem->binarySemReader);

	//Detaching and removing SHMs
	shmdt(sem);

	shmctl(semID, IPC_RMID, NULL);
	return 0;
}