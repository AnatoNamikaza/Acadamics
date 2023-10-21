//#include <unistd.h>
//#include <stdio.h>
//#include <sys/wait.h>
//#include <semaphore.h>
//#include <sys/shm.h>
//#include <stdlib.h>
//#include <pthread.h>
//
//struct sems {
//	sem_t child1, child2, child3;
//	int *c;
//};
//
//void* thread1(void *ptr){
//	sems* semPtr = (sems *) ptr;
//	while(1){
//		sem_wait(&semPtr->child1);
//		printf("a\n");
//		sem_getvalue(&semPtr->child1, semPtr->c);
//		if (*(semPtr->c) == 0)
//			sem_post(&semPtr->child2);
//	}
//}
//
//void* thread2(void *ptr){
//	sems* semPtr = (sems *) ptr;
//	while(1){
//		sem_wait(&semPtr->child2);
//		printf("b\n");
//		sem_getvalue(&semPtr->child1, semPtr->c);
//		if (*(semPtr->c) == 0)
//			sem_post(&semPtr->child3);
//	}
//}
//
//void* thread3(void *ptr){
//	sems* semPtr = (sems *) ptr;
//	while(1){
//		sem_wait(&semPtr->child3);
//		printf("c\n");
//		sem_getvalue(&semPtr->child1, semPtr->c);
//		if (*(semPtr->c) == 0){
//			sem_post(&semPtr->child1);
//			sem_post(&semPtr->child1);
//			sem_post(&semPtr->child1);
//		}
//	}
//}
//
//int main(){
//	int shmid = shmget(78, sizeof(struct sems), IPC_CREAT | 0666);
//	if (shmid == -1){
//		fprintf(stderr, "Unable to create SHM region!\n");
//		return 1;
//	}
//
//	sems *semPtr = (sems *) shmat(shmid, NULL, 0);
//
//	sem_init(&semPtr->child1, 0, 3);
//	sem_init(&semPtr->child2, 0, 0);
//	sem_init(&semPtr->child3, 0, 0);
//
//	semPtr->c = (int *) malloc(sizeof(int));
//
//	pthread_t threads[3];
//
//	if (pthread_create(&threads[0], NULL, &thread1, semPtr) != 0 ||
//		pthread_create(&threads[1], NULL, &thread2, semPtr) != 0 ||
//		pthread_create(&threads[2], NULL, &thread3, semPtr) != 0){
//		fprintf(stderr, "Thread creation failed!\n");
//		return 1;
//	}
//
//	pthread_join(threads[0], NULL);
//	pthread_join(threads[1], NULL);
//	pthread_join(threads[2], NULL);
//}
