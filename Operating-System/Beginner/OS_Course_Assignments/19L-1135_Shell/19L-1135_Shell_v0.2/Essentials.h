#include"Jobs.h"
#include<string>
#include<string.h>
#include<iostream>

using namespace std;

J_ID jobs[100]; // our shell can handel 100 jobs at a time
int lastJobIndex = 0;


void PrintPrompt();
void readCommand(std::string& Command_To_Execute);
void parseCommand(std::string* Argv, std::string Command_To_Execute);
void parsePath(std::string* AllPaths);
std::string lookupPath(std::string* AllPaths, std::string* Argv);
bool is_shell_command(std::string cmd);
void executeJob(J_Data* cmdJob,std::string command, P_Data* temp);
void parse(J_Data* cmdJob);
int isPipe(std::string ptr);
void executeJob(J_Data* cmdJob);

void PrintPrompt()
{
	std::cout << getenv("USER") << '@' << getenv("USER")
		<< "-VirtualBox: " << get_current_dir_name() << "_ᕕ( ᐛ )ᕗ ";
}

void readCommand(std::string& Command_To_Execute)
{
	getline(std::cin, Command_To_Execute);
	//add_history(Command_To_Execute);
}

void parseCommand(std::string* Argv, std::string Command_To_Execute)
{
	int i = 0, j = 0;
Label_2:
	do { Argv[j] += Command_To_Execute[i], i++; } while (Command_To_Execute[i] != '\0' && Command_To_Execute[i] != ' ');
	Argv[j] += '\0';
	if (Command_To_Execute[i] != '\0') {
		i++, j++; goto Label_2;
	}
}

void parsePath(std::string* AllPaths)
{
	std::istringstream Paths(getenv("PATH"));
	int i = 0;
	while (getline(Paths, AllPaths[i], ':')) i++;
}

std::string lookupPath(std::string* AllPaths, std::string* Argv)
{
	if (occur('/', Command_To_Execute.c_str()) > 0)
		if (Command_To_Execute[0] == '/')
			if (access(Command_To_Execute.c_str(), F_OK) != -1)
				return Command_To_Execute;
			else return "errorCode(-781)";
		else {
			if (Command_To_Execute[0] == '.')
				Command_To_Execute = remove(Command_To_Execute, '.');
			std::string filename = get_current_dir_name() + Command_To_Execute;
			if (access(filename.c_str(), F_OK) != -1)
				return filename;
			else return "errorCode(-781)";
		}
	else
		for (int i = 0; !AllPaths[i].empty(); i++) {
			std::string filename = AllPaths[i];
			filename += "/";
			filename += Argv[0];
			if (access(filename.c_str(), F_OK) != -1) return filename;
		}
	return "errorCode(-781)";
}

bool is_shell_command(std::string cmd)
{
	std::string shell_commands[] = { "ping", "cd", "chmod", "ls", "find", "kill", "help", "grep", "rm", "rmdir", "mkdir", "mv", "cp" };
	for (int i = 0; i < sizeof(shell_commands) / sizeof(std::string); i++)
		if (cmd == shell_commands[i]) return true;
	return false;
}

int CHILD_ID;
int pgId = 0;
std::string rgv[MAX_ARGS]; // assign memory one by one
void freeRgv() {
	for (int i = 0; i < MAX_ARGS; i++) 
	{
		rgv[i] = "";
	}
}

void executeJob(J_Data* cmdJob, std::string command, P_Data* temp)
{
	if (isPipe(command)) {
		parse(cmdJob);
		return;
	}
	else {
		parseCommand(rgv, temp->command);
		int srgv = 0;
		for (; rgv[srgv] != ""; srgv++);
		char** Argv = new char* [srgv];
		for (int i = 0; i < srgv; i++) {
			Argv[i] = new char[rgv[i].size()];
			for (int j = 0; j < rgv[i].size(); j++)
				Argv[i][j] = rgv[i][j];
		}
		std::string result = lookupPath(AllPaths, rgv);
		if (result != "errorCode(-781)") {
			int fID = fork();
			if (fID == -1) {
				cout << "\nFork Error";
				return;
			}

			else if (fID == 0) {
				setpgid(pgId, pgId);
				if (execv(result.c_str(), Argv) == -1) {
					cout << "\nNo such file or directory";
					exit(EXIT_FAILURE);
				}
			}
			else {
				if (!cmdJob->BG_Job) {
					int status = 0;
					CHILD_ID = fID;
					signal(SIGTTIN, SIG_IGN);
					signal(SIGTTIN, SIG_IGN);
					tcsetpgrp(STDIN_FILENO, fID);
					waitpid(fID, &status, WUNTRACED);
					tcsetpgrp(STDIN_FILENO, getpgrp());
					signal(SIGTTIN, SIG_DFL);
					signal(SIGTTOU, SIG_DFL);

					if (WIFSTOPPED(status)) { //Given status from a call to waitpid, return true if the child process was stopped
						cout << jobs[lastJobIndex].pName << " with PID " << fID << " suspended\n";
						int i = 0;
						jobs[lastJobIndex].pName += command;
						jobs[lastJobIndex].pid = CHILD_ID;
						lastJobIndex++;
					}
				}
				else {
					for (int i = 0; rgv[i] != ""; i++) {
						jobs[lastJobIndex].pName += rgv[i];
						jobs[lastJobIndex].pName += " ";
					}
					jobs[lastJobIndex].pid = fID;
					jobs[lastJobIndex].startJob(lastJobIndex);
					lastJobIndex++;
				}
			}
		}
		else {
			cout << "\nCommand not support by this shell";
			return;
		}
	}
	freeRgv();
}

void parse(J_Data* cmdJob) {

	int pipes[2], fd = 0;
	int fId;
	for (P_Data* pTemp = cmdJob->procs; pTemp != NULL; pTemp = pTemp->next_proc)
	{
		pipe(pipes);
		fId = fork();

		if (fId < 0) {
			std::cout << "fork error";
		}
		else if (fId == 0) {
			dup2(fd, 0);

			if (pTemp->next_proc != NULL) {
				dup2(pipes[1], 1);
			}

			close(pipes[0]);
			executeJob(cmdJob, pTemp->command, pTemp);
			exit(2);
		}

		else if (fId > 0) {
			wait(NULL);
			close(pipes[1]);
			fd = pipes[0];
		}
	}
}

int isPipe(std::string ptr) {
	for (int i = 0; ptr[i] != '\0'; i++) {
		if (ptr[i] == '|') {
			return 1;
		}
	}
	return 0;
}

void executeJob(J_Data* cmdJob) {
	string file;
	int action = 0, file_desc, success = 0, back_up = 0;

	if (cmdJob->input_file != "")
	{
		file = cmdJob->input_file;
		action = 1;
	}
	else if (cmdJob->output_file != "")
	{
		file = cmdJob->output_file;
		action = 2;
	}

	if (file != "")
		file_desc = open(file.c_str(), O_WRONLY | O_APPEND | O_CREAT);

	if (action == 1)
	{
		back_up = dup(0);
		success = dup2(file_desc, 0);
		close(file_desc);
		executeJob(cmdJob, cmdJob->Line, cmdJob->procs);
		close(0);
		dup2(back_up, 0);
		close(back_up);
	}
	else if (action == 2)
	{
		back_up = dup(1);
		success = dup2(file_desc, 1);
		close(file_desc);
		executeJob(cmdJob, cmdJob->Line, cmdJob->procs);
		close(1);
		dup2(back_up, 1);
		close(back_up);
	}
	else
	{
		executeJob(cmdJob, cmdJob->Line, cmdJob->procs);
	}
}

void killallProcess() {
	for (int i = 0; i < lastJobIndex; i++) {
		kill(jobs[i].pid, 9); // 9 nummber is use to kill any process
	}
}

void deleteJob(int i) { // delete a perticular job record from the job list
	for (int j = i; j <= lastJobIndex; j++) {
		jobs[i].pName = jobs[i + 1].pName;
		jobs[i].pid = jobs[i + 1].pid;
	}
	lastJobIndex--;
}