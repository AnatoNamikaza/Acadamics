// Name:		Abdul-Rehman
// Roll no:		19L-1135
// Section:		CS-4A

//========================================================== Imported Libraries ============================================================

#include"Essentials.h"

//=============================================================== Main Code ================================================================
int temp;
void SIGCHLDSignal(int arg) {
     int processID = waitpid(-1, &temp, WNOHANG); // take Id of the process 
     if(processID > 0) {
		char str[200];
		for(int i=0; i < lastJobIndex; i++) {
			if(jobs[i].pid == processID) {
        		jobs[i].endJob(i);
        		cout<<endl;
				PrintPrompt();
				deleteJob(i);
				break;
			}
		}
		fflush(stdout);
	}
	return;
}


int main() {
	system("clear");
	signal(SIGCHLD,&SIGCHLDSignal);

	parsePath(AllPaths);
	PrintPrompt();
	readCommand(Command_To_Execute);

	while (Command_To_Execute != "exit") {
		J_Data* cmdJob;
		if (Command_To_Execute != "" && Command_To_Execute != "\n") {
			cmdJob = new J_Data;
			cmdJob->set(Command_To_Execute);
			executeJob(cmdJob);
		}
		Command_To_Execute = "";
		cout<<endl;
		PrintPrompt();
		readCommand(Command_To_Execute);
	}
	killallProcess();
	std::cout << "19L-1135_Shell exited. \n";
	return 0;
}

//============================================================== End of Code ===============================================================
