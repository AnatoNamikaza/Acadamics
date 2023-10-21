	// Name:		Abdul-Rehman
	// Roll no:		19L-1135
	// Section:		CS-4A

	//========================================================== Imported Libraries ============================================================

	#include<string>
	#include<string.h>
	#include<unistd.h>
	#include<stdlib.h>
	#include<iostream>
	#include<sys/wait.h>

	//============================================================ Global Variables ============================================================

	#define MAX_ARGS 64
	#define MAX_PATHS 64
	std::string Command_To_Execute;

	//============================================================ Global Functions ============================================================

	std::string remove(std::string& str, char a) {
		std::string rmdstr; int i = 0;
		while (i < str.length()) { if (str[i] != a) rmdstr += str[i];	i++; };
		return rmdstr;
	}

	void PrintPrompt() {
		std::cout << getenv("USER") << '@' << getenv("USER")
			<< "-VirtualBox: " << get_current_dir_name() << "$ ";
	}

	void readCommand(std::string& Command_To_Execute) {
		getline(std::cin, Command_To_Execute);
	}

	void parsePath(std::string* AllPaths) {
		std::string Path = getenv("PATH");
		int i = 0, j = 0;
	Label_1:
		do { AllPaths[j] += Path[i], i++; } while (Path[i] != '\0' && Path[i] != ':');
		AllPaths[j] += '\0';
		if (Path[i] != '\0') {
			i++, j++; goto Label_1;
		}
	}

	void parseCommand(std::string* Argv, std::string Command_To_Execute) {
		int i = 0, j = 0;
	Label_2:
		do { Argv[j] += Command_To_Execute[i], i++; } while (Command_To_Execute[i] != '\0' && Command_To_Execute[i] != ' ');
		Argv[j] += '\0';
		if (Command_To_Execute[i] != '\0') {
			i++, j++; goto Label_2;
		}
	}

	bool search(std::string str, char c) {
		for (int i = 0; str[i] != '\0'; i++)
			if (str[i] == c)return true;
		return false;
	}

	std::string lookupPath(std::string* AllPaths, std::string* Argv) {
		if (search(Command_To_Execute, '/'))
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
				filename[filename.size() - 1] = '/';
				filename += Argv[0];
				if (access(filename.c_str(), F_OK) != -1) return filename;
			}
		return "errorCode(-781)";
	}

	//=============================================================== Main Code ================================================================

	int main() {
		system("clear");

		std::string AllPaths[MAX_PATHS];
		std::string exeCommand;
		parsePath(AllPaths);

		while (Command_To_Execute != "exit") {
			Command_To_Execute = "";
			std::string rgv[MAX_ARGS];

			PrintPrompt();
			readCommand(Command_To_Execute);
			parseCommand(rgv, Command_To_Execute);
			int srgv = 0;
			for (; rgv[srgv] != ""; srgv++);

			char** Argv = new char* [srgv];

			for (int i = 0; i < srgv; i++) {
				Argv[i] = new char[rgv[i].size()];
				for (int j = 0; j < rgv[i].size(); j++)	Argv[i][j] = rgv[i][j];
			}

			std::string result = lookupPath(AllPaths, rgv);
			if (result != "errorCode(-781)") {
				pid_t id = fork();
				if (id == -1)
					std::cout << "error";
				if (id == 0)
					execv(result.c_str(), Argv);
				else
					wait(NULL);
			}
		}

		std::cout << "19L-1135_Shell exited. \n";
		return 0;
	}

	//============================================================== End of Code ===============================================================
