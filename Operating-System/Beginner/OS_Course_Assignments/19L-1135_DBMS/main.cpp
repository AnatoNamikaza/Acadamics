#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

using namespace std;

struct book
{
    int id;
    char    title[100],
        authors[5][100],
        date_of_publication[100],
        publisher[100];

    book() {}

    void read()
    {
        cout << "Please enter the id of the book: ";
        cin >> id;
        cin.ignore();
        cout << "Please enter the title of the book: ";
        cin.getline(title, 100);
        cout << "How many authors are there: ";
        int number;
        cin >> number;
        cin.ignore();
        for (int i = 0; i < number; i++)
        {
            cout << "Please enter the author no " << i + 1 << " of the book: ";
            cin.getline(authors[i], 100);
        }
        cout << "Please enter the date of publication: ";
        cin.getline(date_of_publication, 100);
        cout << "Please enter the publisher of the book: ";
        cin.getline(publisher, 100);
    }

    book(int id, char* t, char** a, char* d, char* p)
    {
        this->id = id;
        strcpy(title, t);
        for (int i = 0; i < 5; i++)
        {
            strcpy(authors[i], a[i]);
        }
        strcpy(date_of_publication, d);
        strcpy(publisher, p);
    }

    void printDetails()
    {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Authors:\n";
        for (int i = 0; i < 5; i++)
        {
            cout << authors[i] << endl;
        }
        cout << "Date of publication: " << date_of_publication << endl;
        cout << "Publisher: " << publisher << endl;
    }
};

int main()
{
    string option;
    cout << "Write one of following options to proceed:\n";
    cout << "------------------------------------------\n";
    cout << "1-Write (exit) to exit from the system.\n";
    cout << "2-Write (update) to update the record from system.\n";
    cout << "3-Write (add) to add record to the system.\n";
    cout << "4-Write (search) to search from the system.\n";
    cout << "5-Write (print) to show the details of the book in system\n";
    cout << "----------------------------\n";
    cout << "Write your instruction here: ";
    int fd0 = open("record.dat", O_RDWR, ios::binary | ios::out);
    lseek(fd0, 100 * sizeof(book), SEEK_SET);
    close(fd0);
    getline(cin, option);
    while (option != "exit")
    {
        if (option == "add")
        {
            int fd = open("record.dat", O_RDWR, ios::binary | ios::out);
            book* b = new book();
            b->read();
            lseek(fd, (b->id) * sizeof(book), SEEK_SET);
            write(fd, (char*)b, sizeof(book));
            close(fd);
        }
        else if (option == "search")
        {
            int fd = open("record.dat", O_RDWR, ios::binary | ios::in);
            int id;
            cout << "Please enter the id: ";
            cin >> id;
            book* b = new book;
            lseek(fd, (id) * sizeof(book), SEEK_SET);
            read(fd, (char*)b, sizeof(book));
            if (b->id == 0)
            {
                cout << "this book does not exist\n";
            }
            else
            {
                cout << "this book is present\n";
            }
            cin.ignore();
            close(fd);
        }
        else if (option == "update")
        {
            int fd = open("record.dat", O_RDWR, ios::binary | ios::in);
            int id;
            cout << "Please enter the id for which you want to update: ";
            cin >> id;
            book* b = new book;
            lseek(fd, (id) * sizeof(book), SEEK_SET);
            read(fd, (char*)b, sizeof(book));
            bool flag = true;
            if (b->id == 0)
            {
                flag = false;
            }
            else
            {
                flag = true;
            }

            if (flag == true)
            {
                int fd2 = open("record.dat", O_RDWR, ios::binary | ios::in | ios::out);
                book* c = new book;
                lseek(fd2, id * sizeof(book), SEEK_SET);
                read(fd2, (char*)c, sizeof(book));
                c->read();
                close(fd2);
                int fd3 = open("record.dat", O_RDWR, ios::binary | ios::in);
                book* data = (book*)mmap(0, 100 * sizeof(book), PROT_READ | PROT_WRITE, MAP_SHARED, fd3, 0);
                data[id] = (*c);
                close(fd3);
                cout << "Record updated\n";
            }
            else
            {
                cout << "Record not found\n";
            }
        }
        else if (option == "print")
        {
            int fd = open("record.dat", O_RDWR, ios::binary | ios::in);
            int id;
            cout << "Please enter the id: ";
            cin >> id;
            book* b = new book;
            lseek(fd, (id) * sizeof(book), SEEK_SET);
            read(fd, (char*)b, sizeof(book));
            if (b->id != 0)
            {
                b->printDetails();
            }
            else
            {
                cout << "this book is not present\n";
            }
            cin.ignore();
            close(fd);
        }
        cout << "----------------------------\n";
        cout << "Write your instruction here: ";
        getline(cin, option);
    }
}
