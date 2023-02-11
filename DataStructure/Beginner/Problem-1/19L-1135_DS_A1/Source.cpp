#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Search Engine.h" 

using namespace std;

int initialize() {

	std::string logo = "                                                 \n                               oo                \n                              o   o              \n                             o     o             \n                            o       o            \n                           o         o           \n                          o           o          \n                         o             o         \n                        o               o        \n                       o o o o o o o o o o       \n                      o                   o      \n                     o                     o     \n                    o                       o    \n                   o                         o   \n                  o                           o  \n                                                  \n               ---------------------------------\n";
	while (true) {
		cout << logo;
		int k, l = 0;
		for (int i = 815; i < 850; i++) {
			if (l==2) {
				logo = "\0";
				return 0;
			}
			for (int j = i; j < 850;j++) {
				k = j - 2;
				if (j > 817) {
					logo[j] = '#';
					logo[k] = '-';
					cout << logo;
					system("cls");
				}
			}
			l++;
		}
	}

}

int main() {

	//	string file = "Backup.txt";
	string file = "Docs Records.txt";
	int val = 0;

	Search_Engine v1;

	int v = initialize();
	cout << "1.File options 2.Search 3.Exit \n";
	cout << "Enter choice: \n";
	cin >> val;
	system("cls");
	if (val == 1) {
		val = 0;
		cout << "1.Add new doc topic 2.clear file 3.clear backup\n";
		cout << "Enter choice: \n";
		cin >> val;
		system("cls");
		if (val == 1) {
			cin.ignore(1);
			v1.Add_Doc_to_Index(file);
			val = 0;
			cout << "1.Back to main menu 2.Exit\n";
			cout << "Enter choice: \n";
			cin >> val;
			if (val == 2) {
				return 0;
				system("cls");
				val = 0;
			}
			else if (val == 1) {}
			system("cls");
			val = 0;
		}
		else if (val == 2) {
			v1.clearFile(file);
			val = 0;
			cout << "1.Back to main menu 2.Exit\n";
			cout << "Enter choice: \n";
			cin >> val;
			if (val == 2) {
				return 0;
				system("cls");
				val = 0;
			}
			else if (val == 1) {
				system("cls");
				val = 0;
			}
			system("cls");
			val = 0;
		}
		else if (val == 3) {
			v1.clearBackup();
			val = 0;
			cout << "1.Back to main menu 2.Exit\n";
			cout << "Enter choice: \n";
			cin >> val;
			if (val == 2) {
				return 0;
				system("cls");
				val = 0;
			}
			else if (val == 1) {
				system("cls");
				val = 0;
			}
			system("cls");
			val = 0;
		}
		system("cls");
		val = 0;
	}
	else if (val == 2) {
		cin.ignore(1);
		v1.Search_Documents(file);
		val = 0;
		cout << "Press Enter to Exit\n";	}
	else if (val == 3) {
		system("cls");
		val = 0;
		return 0;
	}

}