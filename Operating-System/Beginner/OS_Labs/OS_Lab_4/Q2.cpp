#include<string>
#include<fcntl.h>
#include<fstream>
#include<iostream>
#include <unistd.h>
#include<sys/wait.h>

using namespace std;

int main(int arg, char* argv[])
{
	int
		pipe1[2];

	string
		inputFile = argv[1],
		outputFile = argv[2],
		input;

	pipe(pipe1);

	ifstream fin(inputFile);
	if (!fin.is_open())
	{
		cout << "Input file didnot open.\n";
		return -1;
	}

	string c;
	getline(fin, c, '\n');
	while (!fin.eof())
	{
		input += c + '\n';
		getline(fin, c, '\n');
	}
	fin.close();
	input += c + '\0';

	int forkId = fork();
	if (forkId == -1)
	{
		return 4;
	}

	if (forkId == 0)
	{
		//cout << "Child Process.\n";
		string Str;
		close(pipe1[1]);
		char temp = ' ';
		for (int i = 0; temp != '\0'; i++)
		{
			read(pipe1[0], &temp, 1);
			Str += temp;
		}
		close(pipe1[0]);


		ofstream fout(outputFile);
		if (!fout.is_open())
		{
			cout << "Output file didnot open.\n";
			return -1;
		}
		fout << Str;

		fout.close();
	}
	else if (forkId > 0)
	{
		//cout << "Parent Process.\n";
		close(pipe1[0]);
		write(pipe1[1], input.c_str(), input.size());
		close(pipe1[1]);

		wait(NULL);
		cout << "File copied.\n";
	}
	return 0;
}
