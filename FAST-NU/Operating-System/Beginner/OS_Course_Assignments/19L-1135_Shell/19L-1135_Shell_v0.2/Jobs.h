#include<time.h>
#include<string>
#include<sstream>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<sys/wait.h>
//#include<readline/history.h>
//#include<readline/readline.h>

using namespace std;

//====================== Global Variables ======================

#define MAX_ARGS 64
#define MAX_PATHS 64
std::string Command_To_Execute;
std::string AllPaths[MAX_PATHS];

//====================== Global Functions ======================

int occur(char ch, const char* str)
{
	if (str[0] == '\0')
		return 0;
	else if (ch == str[0])
		return 1 + occur(ch, &str[1]);
	else
		return occur(ch, &str[1]);
};

std::string remove(std::string& str, char a)
{
	std::string rmdstr;
	int i = 0;
	while (i < str.length())
	{
		if (str[i] != a)
			rmdstr += str[i];	i++;
	}
	return rmdstr;
}

void remove_Front(std::string& str, char a)
{
	while (str[0] == a)
		for (int j = 0; j < str.length(); j++)
			str[j] = str[j + 1];
}

void replace(std::string& str, char a, char ra)
{
	int i = 0;
	while (i < str.length())
	{
		if (str[i] == a)
			str[i] = ra;
		i++;
	}
}


void remove_Last(std::string& str, char a) {
	for (int j = str.length() - 1; j >= 0; j--)
		if (str[j] == a) {
			str[j] = '\0';

		}
		else if (str[j] != a) {
			break;
		}
}

//========================== Classes ===========================

struct P_Data {

	std::string  command, argv[MAX_ARGS];
	int argc = 0;
	P_Data* next_proc = NULL;

	void set(std::string& cmd)
	{
		command = cmd;
		std::istringstream cgv(command);
		int i = 0;
		while (cgv >> argv[i])i++;
		argc = i;
	}

	void P_print()
	{
		std::cout << "\nCommand: " << command << "\nArgs: \n";
		for (int i = 0; i < argc; i++)
		{
			std::cout << argv[i] << '\n';
		}
	}
};

struct J_Data {
	std::string Line, input_file = "",
		output_file = "",
		argv[MAX_ARGS];
	bool BG_Job = false;
	int no_of_proc = 0;
	P_Data* procs;

	void setDirection(std::string& cmd) {
		std::string temp = "";
		for (int i = 0; cmd[i] != '\0'; i++) {
			temp += cmd[i];
			if (cmd[i] == '>') {
				cmd[i] = (char)0;
				for (int j = i + 1; cmd[j] != '\0'; j++) {
					output_file += cmd[j];
				}
				remove_Front(output_file, ' ');
				remove_Last(output_file, ' ');
				break;
			}

			else if (cmd[i] == '<') {
				cmd[i] = (char)0;
				for (int j = i + 1; cmd[j] != '\0'; j++) {
					input_file += cmd[j];
				}
				remove_Front(input_file, ' ');
				remove_Last(input_file, ' ');
				break;
			}
		}
	}

	void set(std::string& line)
	{
		this->Line = line;
		if (occur('&', line.c_str()) > 0)
		{
			BG_Job = true;
			replace(Line, '&', '\0');
		}

		setDirection(line);
		std::istringstream cgv(line);
		int i = 0;
		while (cgv >> argv[i])i++;

		P_Data* temp_proc = nullptr;

		std::string Prc;

		i = 0;
		while (argv[i] != "" && argv[i][0] != '\0')
		{
			if (argv[i] == "|")
			{
				no_of_proc++;
				if (no_of_proc == 1)
				{
					procs = new P_Data;
					remove_Front(Prc, ' ');
					procs->set(Prc);
					temp_proc = procs;
					Prc = "";
				}
				else
				{
					temp_proc->next_proc = new P_Data;
					remove_Front(Prc, ' ');
					temp_proc->next_proc->set(Prc);
					temp_proc = temp_proc->next_proc;
					Prc = "";
				}
			}
			else
				Prc += ' ' + argv[i];
			i++;
		}
		if (no_of_proc == 0)
		{
			procs = new P_Data;
			remove_Front(Prc, ' ');
			procs->set(Prc);
			no_of_proc++;
		}
		else
		{
			temp_proc->next_proc = new P_Data;
			remove_Front(Prc, ' ');
			temp_proc->next_proc->set(Prc);
			no_of_proc++;
		}
	}

	void release()
	{
		P_Data* temp = procs;
		procs = nullptr;
		while (temp != nullptr)
		{
			P_Data* temp2 = temp;
			temp = temp->next_proc;
			delete temp2;
			temp2 = nullptr;
		}
	}

	void Jprint()
	{
		std::cout << "Job: " << Line << '\n';

		int i = 0;
		P_Data* temp = procs;
		while (temp != nullptr)
		{
			std::cout << "Process#" << i + 1 << ": \n";
			temp->P_print();
			std::cout << '\n';
			temp = temp->next_proc;
			i++;
		}
		std::cout << "Job printed. \n";
	}
};

struct J_ID {
	int pid; // process Id
	std::string pName; // process name

	void startJob(int i) {
		std::cout << "[" << i << "]" << "\t" << pid;
	}

	void endJob(int i) {
		std::cout << "[" << i << "]" << "\t" << pid << "   " << pName;
	}
};

//======================= Code End =============================