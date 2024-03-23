#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


#define NUM_THREADS 3

// Function executed by each thread
void *thread_function(void *arg) {
    int Var2_numb = (int)arg;
    int random_number = rand() % 100; // Generate random number between 0 and 99

    // Display the result on the screen
    // For Debugging
    printf("Var2_numb: %d, Subtracted value: %d\n", Var2_numb, random_number);

    // Add random number to Var
    Var2_numb -= random_number;

    // Display the result on the screen
    printf("Thread ID: %ld, Result value: %d\n", (long)pthread_self(), Var2_numb);

    // Store the result in the file "Sub_of_3s.txt"
    FILE *file = fopen("Sub_of_3s.txt", "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        pthread_exit(NULL);
    }
    fprintf(file, "%d\n", Var2_numb);
    fclose(file);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize Var
    int Var2 = 7;

    // Create and run threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)Var2) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining thread");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
