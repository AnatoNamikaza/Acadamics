#include <time.h> 
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>
#include <string.h>

#define BILLION  1000000000L;

time_t t1;
FILE* fptr1, * fptr2, * fptr3, * fptr4;

// Create 2 files: file1.txt and file2.txt, both with one million rows of random numbers.
void generate()
{
    fptr1 = fopen("file1.txt", "w");
    fptr2 = fopen("file2.txt", "w");

    if (fptr1 == NULL || fptr2 == NULL)
    {
        printf("Error!");
        exit(1);
    }


    srand((unsigned)time(&t1));
    int i;
    for (i = 0; i < 1000000; i++)
    {
        fprintf(fptr1, "%d\n", (rand() % 100000));
        fprintf(fptr2, "%d\n", (rand() % 100000));
    }

    fclose(fptr1);
    fclose(fptr2);
}

// Read the entire contents of files into memory, then process each row
void fun1()
{
    printf("Method#1 called\n");

    //Accessing files
    fptr1 = fopen("file1.txt", "r");
    fptr2 = fopen("file2.txt", "r");
    fptr3 = fopen("newfile1.txt", "w");
    fptr4 = fopen("newfile2.txt", "w");

    char delim[] = "\n";

    //reading file_1 and processing each row 
    fseek(fptr1, 0, SEEK_END);
    long fsize1 = ftell(fptr1);
    fseek(fptr1, 0, SEEK_SET);
    char* string1 = malloc(fsize1 + 1);
    fread(string1, fsize1, 1, fptr1);
    fclose(fptr1);
    char* ptr1 = strtok(string1, delim);
    while (ptr1 != NULL)
    {
        fprintf(fptr3, "%d\n", atoi(ptr1) * 2);
        ptr1 = strtok(NULL, delim);
    }
    fclose(fptr3);

    //reading file_2 and processing each row 
    fseek(fptr2, 0, SEEK_END);
    long fsize2 = ftell(fptr2);
    fseek(fptr2, 0, SEEK_SET);
    char* string2 = malloc(fsize2 + 1);
    fread(string2, fsize2, 1, fptr2);
    fclose(fptr2);
    char* ptr2 = strtok(string2, delim);
    while (ptr2 != NULL)
    {
        fprintf(fptr4, "%d\n", atoi(ptr2) * 2);
        ptr2 = strtok(NULL, delim);
    }
    fclose(fptr4);
}


// Read one row of file at a time and process it
void fun2()
{
    printf("Method#2 called\n");

    //Accessing files
    fptr1 = fopen("file1.txt", "r");
    fptr2 = fopen("file2.txt", "r");
    fptr3 = fopen("newfile1.txt", "w");
    fptr4 = fopen("newfile2.txt", "w");

    //Reading rows from files and processing them
    int num1 = 0, num2 = 0;
    while (fscanf(fptr1, "%d", &num1) == 1 && fscanf(fptr2, "%d", &num2) == 1)
    {
        fprintf(fptr3, "%d\n", num1 * 2);
        fprintf(fptr4, "%d\n", num2 * 2);
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);
}


// Split file1.txt into 2 parts and read each part into memory separately
void fun3()
{
    printf("Method#3 called\n");

    //Accessing files
    fptr1 = fopen("file1.txt", "r");
    fptr2 = fopen("file2.txt", "r");
    fptr3 = fopen("newfile1.txt", "w");
    fptr4 = fopen("newfile2.txt", "w");
    char delim[] = "\n";

    //Reading 1st half of file_1
    fseek(fptr1, 0, SEEK_END);
    long fsize1 = ftell(fptr1);
    fseek(fptr1, 0, SEEK_SET);
    char* string1 = malloc(((fsize1 / 2) + 1));
    fread(string1, ((fsize1 / 2) + 1), 1, fptr1);
    char* ptr1 = strtok(string1, delim);
    while (ptr1 != NULL)
    {
        fprintf(fptr3, "%d\n", atoi(ptr1) * 2);
        ptr1 = strtok(NULL, delim);
    }
    //Reading 2nd half of file_1
    fseek(fptr1, (fsize1) / 2, SEEK_SET);
    fread(string1, ((fsize1 + 1) / 2), 1, fptr1);
    ptr1 = strtok(string1, delim);
    while (ptr1 != NULL)
    {
        fprintf(fptr3, "%d\n", atoi(ptr1) * 2);
        ptr1 = strtok(NULL, delim);
    }
    fclose(fptr1);
    fclose(fptr3);


    //Reading 1st half of file_2
    fseek(fptr2, 0, SEEK_END);
    long fsize2 = ftell(fptr2);
    fseek(fptr2, 0, SEEK_SET);
    char* string2 = malloc(((fsize2 / 2) + 1));
    fread(string2, ((fsize2 / 2) + 1), 1, fptr2);
    char* ptr2 = strtok(string2, delim);
    while (ptr2 != NULL)
    {
        fprintf(fptr4, "%d\n", atoi(ptr2) * 2);
        ptr2 = strtok(NULL, delim);
    }
    //Reading 2nd half of file_2
    fseek(fptr2, (fsize2) / 2, SEEK_SET);
    fread(string2, ((fsize2 + 1) / 2), 1, fptr2);
    ptr2 = strtok(string2, delim);
    while (ptr2 != NULL)
    {
        fprintf(fptr4, "%d\n", atoi(ptr2) * 2);
        ptr2 = strtok(NULL, delim);
    }
    fclose(fptr2);
    fclose(fptr4);
}

//Main body code
int main()
{
    struct timespec start, stop;
    double accum;

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    generate();


    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    accum = (stop.tv_sec - start.tv_sec)
        + (double)(stop.tv_nsec - start.tv_nsec)
        / (double)BILLION;
    printf("Generation time: %lf seconds \n", accum);

    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    fun1(); //Method#1

    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    accum = (stop.tv_sec - start.tv_sec)
        + (double)(stop.tv_nsec - start.tv_nsec)
        / (double)BILLION;
    printf("Doubling time method#1: %lf seconds \n", accum);

    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    fun2(); //Method#2

    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    accum = (stop.tv_sec - start.tv_sec)
        + (double)(stop.tv_nsec - start.tv_nsec)
        / (double)BILLION;
    printf("Doubling time method#2: %lf seconds \n", accum);

    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------

    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    fun3(); //Method#3

    if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
        perror("clock gettime");
        return EXIT_FAILURE;
    }

    accum = (stop.tv_sec - start.tv_sec)
        + (double)(stop.tv_nsec - start.tv_nsec)
        / (double)BILLION;
    printf("Doubling time method#3: %lf seconds \n", accum);

    return EXIT_SUCCESS;
}
