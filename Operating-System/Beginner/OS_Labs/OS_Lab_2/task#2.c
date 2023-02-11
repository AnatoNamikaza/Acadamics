#include<stdio.h>
#include<stdlib.h>

int main(int arg, char* argv[])
{

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
        printf("\nSorted Array: \n");
        for (int i = 0; i < arg - 1; i++)
            for (int j = 0; j < arg - i - 2; j++)
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1],
                    arr[j + 1] = temp;
                }
        for (int i = 0; i < arg - 1; i++)
            printf("%d ", arr[i]);
        printf("\n");
    
        free(arr);
    }

    return 0;
}