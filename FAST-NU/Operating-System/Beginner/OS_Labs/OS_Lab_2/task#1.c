#include<stdio.h>
#include<stdlib.h>

int main(int arg, char* filename[])
{

    FILE* file_ptr;
    char ch;

    printf("Filename: %s \n", filename[1]);
    file_ptr = fopen(filename[1], "r");
    if (file_ptr == NULL)
        printf("Unable to access file.\n");
    else
    {
        printf("File has been accessed and the contents are displayed on console:\n\n");
        do ch = fgetc(file_ptr), putchar(ch);
        while (ch != EOF);

        fclose(file_ptr);
    }

    return 0;
}