#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


#define NUM_THREADS 2

// Function executed by each thread
void *thread_function(void *arg) {
    char *filename = (char *)arg;
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    int num;
    int r = 1;
    while (fscanf(file, "%d", &num) != EOF) {
        r *= num;
    }

    fclose(file);

    // Display the result on the screen
    // For Debugging
    printf("File results: %d\n", r);

    // Return the value of Var
    pthread_exit((void *)r);
}


int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize Var
    int Var3 = 2;
    
    char *thread_filenames[NUM_THREADS] = {"Sum_of_5s.txt", "Sub_of_3s.txt"};

    // Create and run threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)thread_filenames[i]) != 0) {
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

    // Store each result in the file "Sum_of_5s.txt"
    FILE *file = fopen("Div_of_2s.txt", "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        int res = thread_results[i] / Var3;
        // Display the res
        printf("thread results after division: %d\n", res);
        fprintf(file, "%d\n", res);
    }
    fclose(file);

    return 0;
}
