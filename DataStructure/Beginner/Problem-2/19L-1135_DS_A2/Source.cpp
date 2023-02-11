#include <iostream>
#include"Mind_Thrashing_Game.h"
using namespace std;

int main() {
	string file = "Week2 Stages.txt";
	MTG Game(file);
	int v = 0;

	while (v!=2) {
		cout << "All Stages:\n";
		Game.PrintAllStages();
		cout << "\n...................................................................\n";
		cout << "1. Iterative		2.Recursive\n\nEnter Choice: ";
		cin >> v;
		if (v==1) {
			Game.PlayableStages_I();
			v = 0;
		}
		else if (v==2) {
			Game.PlayableStages_R();
			v = 0;
		}
		else {
			cout << "Choice isn't Available.";
			v = 0;
		}
		cout << "\n_____________________\n";
		cout << "1. Repeat		2.Exit\n\nEnter Choice: ";
		cin >> v;
		system("cls");
	}
	return 0;
 }