#include<string>
#include<stdio.h>
#include<fcntl.h>
#include<iostream>
#include <unistd.h>
#include<sys/wait.h>

using namespace std;

void Reverse_Casing(string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			str[i] += 32;
		}
		else if (str[i] > 96 && str[i] < 123)
		{
			str[i] -= 32;
		}
	}
}

int main()
{
	string message1 = "Hi There";
	cout << "string: " << message1 << "\n\n";
	message1 += '\0';
	int pipe1[2], pipe2[2];
	pipe(pipe1), pipe(pipe2);

	pid_t forkId = fork();
	if (forkId == -1)
	{
		cout << "Child not created.\n";
		return -1;
	}

	if (forkId == 0)
	{
		//cout << "Child process.\n";
		string Str;
		close(pipe2[1]);
		char temp = ' ';
		for (int i = 0; temp != '\0'; i++)
		{
			read(pipe2[0], &temp, 1);
			Str += temp;
		}
		close(pipe2[0]);

		Reverse_Casing(Str);

		write(pipe1[1], Str.c_str(), Str.size());
		close(pipe1[1]);
		close(pipe1[0]);
	}
	else if (forkId > 0)
	{
		//cout << "Parent process.\n";
		close(pipe2[0]);

		write(pipe2[1], message1.c_str(), message1.size());
		close(pipe2[1]);
		wait(NULL);
		string Str;
		close(pipe1[1]);
		char temp = ' ';
		for (int i = 0; temp != '\0'; i++)
		{
			read(pipe1[0], &temp, 1);
			Str += temp;
		}
		close(pipe1[0]);

		cout << "Converted string: " << Str << "\n\n";
	}

	return 0;
}
