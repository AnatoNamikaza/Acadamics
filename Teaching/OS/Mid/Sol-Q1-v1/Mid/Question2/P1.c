#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function executed by each thread
void *thread_function(void *arg) {
    int Var_numb = (int )arg;
    int random_number = rand() % 100; // Generate random number between 0 and 99

    // Display the result on the screen
    // For Debugging
    printf("Var_numb: %d, Added value: %d\n", Var_numb, random_number);

    // Add random number to Var
    Var_numb += random_number;

    // Display the result on the screen
    printf("Thread ID: %ld, Result value: %d\n", (long)pthread_self(), Var_numb);

    // Return the value of Var
    pthread_exit((void *)Var_numb);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int sum = 0;

    // Initialize Var
    int Var = 5;

    // Create and run threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)Var) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    int thread_results[NUM_THREADS]; // Array to store results from each thread

    // Collect results from threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        void *thread_result;
        if (pthread_join(threads[i], &thread_result) != 0) {
            perror("Error joining thread");
            exit(EXIT_FAILURE);
        }
        thread_results[i] = (int)thread_result; // Store thread result in array
    }

    // Calculate the sum of all thread results
    for (int i = 0; i < NUM_THREADS; ++i) {
        sum += thread_results[i];
    }

    // Display the sum
    printf("Sum of all thread results: %d\n", sum);

    // Store each result in the file "Sum_of_5s.txt"
    FILE *file = fopen("Sum_of_5s.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        fprintf(file, "%d\n", thread_results[i]);
    }
    fclose(file);

    return 0;
}
