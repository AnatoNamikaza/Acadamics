#include<fcntl.h>
#include<fstream>
#include<sstream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    std::string File_Text,
        line,
        File_Name = "lab.txt";

    std::ifstream fin(File_Name);

    if (fin.is_open())
    {
        while (getline(fin, line))
            File_Text += line + '\n';

        fin.close();
    }
    else std::cout << "Unable to open file";

    int fd = shm_open("shm3", O_CREAT | O_EXCL | O_RDWR, 0600),
        size = File_Text.size();

    //std::cout << "File text:\n\n" << File_Text << "\n\nTotal_Size: " << size << "\n\n";

    if (fd < 0)
    {
	std::cout << "Error!! fd not working (-_-)\n";
        return EXIT_FAILURE;
    }

    ftruncate(fd, size);
    int* data = (int*)mmap(0, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    std::cout << "sender mapped address: " << data << '\n';

    for (int i = 0; i < size; i++)
        data[i] = File_Text[i];

    int p_id = fork();

    if (p_id == 0)
    {
        //std::cout << "\n------------ Child Process ------------\n";

        std::stringstream s(File_Text); // Used for breaking words
        std::string word; // to store individual words

        int count = 0;
        while (s >> word)
            count++;

        std::ofstream out(File_Name, std::ios::app);
        out << std::endl << std::endl << "Total_Words: " << count << std::endl;
        out.close();
    }

    else
    {
        wait(NULL);
        //std::cout << "\n----------- Parent Process ------------\n";

        int lines = 0;
        for (int i = 0; i < size; i++)
            if (data[i] == '.')
                lines++;

        std::ofstream out(File_Name, std::ios::app);
        out << "Total_Lines: " << lines << std::endl;
        out.close();
    }

    //std::cout << "Process Successful (^_^)\n";

    munmap(data, size * sizeof(int));
    close(fd);
    shm_unlink("shm3");
    return EXIT_SUCCESS;
}