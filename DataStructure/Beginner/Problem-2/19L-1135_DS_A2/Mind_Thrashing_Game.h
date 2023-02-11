#pragma once
#include <fstream>
#include <cmath>
#include"MT_Data.h"
#include"MT_Stack.h"

class MTG {
private:
	int totalStages;
	MT_Data* Stages;
public:
	//Default Constructor
	MTG() {
		Stages = new MT_Data;
		totalStages = 0;
	}

	//Parameterized Constructor
	MTG(string& file) {
		Stages = nullptr;
		totalStages = 0;
		string name, px, tm;

		ifstream fin;
		fin.open(file);
		if (fin.is_open() != true) {
			std::cout << "File didnot open. \n";
		}

		getline(fin, name, ' ');
		if (name != "") {
			getline(fin, px, ' ');
			getline(fin, tm, '\n');
			totalStages++;
			Stages = new MT_Data(name, stoi(px), stoi(tm), totalStages);
			getline(fin, name, ' ');
			MT_Data* Stemp = Stages;
			while (name != "") {
				getline(fin, px, ' ');
				getline(fin, tm, '\n');
				totalStages++;
				Stemp->Next = new MT_Data(name, stoi(px), stoi(tm), totalStages);
				Stemp = Stemp->Next;
				getline(fin, name, ' ');
			}
			Stemp = nullptr;
		}
	}
	
	//Print all stages listed for the game.
	void PrintAllStages() {
		Stages->PrintA();
	}

	//Prints the Best playable stages for earning max points by finding best combination through iterative function.
	void PlayableStages_I() {
		int AvailableTime = 50;
		cout << "...................................................................\n";
		cout << "Please Enter the total time you can spare to play the game:\n";
		cin >> AvailableTime;
//		cout << "...................................................................\n";
//		cout << "\nAll Possibilities:\n";
//		cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";

		MT_Stack<MT_Data> StageStack; MT_Data* remp = nullptr, * tmp;
		int subsets = pow(2, totalStages) - 1, checked = 0;

		while (subsets > 0) {
			checked = subsets;
			tmp = Stages;
			while (checked > 0) {
				if (checked % 2 == 1) {
					remp = new MT_Data(tmp->StageName, tmp->StagePoints, tmp->StageCompletionTime, tmp->StageNo, remp);
				}
				checked = checked / 2;
				tmp = tmp->Next;
			}
			if (AvailableTime >= remp->CalculateTotalTime()) {
				StageStack.push(remp);
			}
			DeleteA(remp);
			delete remp; remp = nullptr;
			subsets--;
		}
//		StageStack.print();
//		cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		StageStack.Best();
	}

	//Prints the Best playable stages for earning max points by finding best combination through recursive function.
	//Rapper recursive function.
	void PlayableStages_R() {
		int AvailableTime = 50;
		cout << "...................................................................\n";
		cout << "Please Enter the total time you can spare to play the game:\n";
		cin >> AvailableTime;
//		cout << "...................................................................\n";
//		cout << "\nAll Possibilities:\n";
//		cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";


		MT_Stack<MT_Data> StageStack; MT_Data* remp=nullptr;
		APStages_R(remp, totalStages, Stages,AvailableTime, StageStack);
//		StageStack.print();
//		cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		StageStack.Best();
	}

	//Recursive function.
	void APStages_R(MT_Data* tmp, int i, MT_Data* tmp2, int val, MT_Stack<MT_Data>& Stack) {
		if (i == 0) {
			if (tmp != nullptr && val >= tmp->CalculateTotalTime()) {
				Stack.push(tmp);
			}
			return;
		}
		APStages_R(tmp, i - 1, tmp2->Next, val, Stack);
		tmp = new MT_Data(tmp2->StageName, tmp2->StagePoints, tmp2->StageCompletionTime, tmp2->StageNo, tmp);
		APStages_R(tmp, i - 1, tmp2->Next, val, Stack);
		delete tmp, tmp = nullptr;
	}

	//Deletes all the data in the next pointer of a data element.
	void DeleteA(MT_Data* &tmp) {
		if (tmp != nullptr) {
			while (tmp != nullptr && tmp->StageName != "" && tmp->Next != nullptr) {
				MT_Data* del = tmp->Next;
				tmp->Next = tmp->Next->Next;
				delete del; del = nullptr;
			}
		}
	}

	~MTG() {
		totalStages = 0;
		MT_Data* tmp= Stages;
		Stages = nullptr;
		DeleteA(tmp);
		delete tmp; tmp = nullptr;
	}
};