#include <iostream>
#include "Search_Engine.h" 

using namespace std;

int main() {

	string file = "Docs Records.txt";
	int val = 0;

	Search_Engine v1;
	v1.IndexGenerator(file);

	while (true) {
		cout << "1.File options | 2.Search | 3.Print All Data | 3.Exit \n";
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
			cout << "1.Back to main menu 2.Exit\n";
			cout << "Enter choice: \n";
			cin >> val;
			if (val == 2) {
				return 0;
			}
			else if (val == 1) {
				system("cls");
				val = 0;
			}
			system("cls");
			val = 0;
		}
		else if (val == 3) {
			system("cls");
			v1.IndexPrint();
			val = 0;
			cout << "1.Back to main menu 2.Exit\n";
			cout << "Enter choice: \n";
			cin >> val;
			if (val == 2) {
				return 0;
			}
			else if (val == 1) {
				system("cls");
				val = 0;
			}
			system("cls");
			val = 0;
		}
		else if (val == 4) {
			system("cls");
			val = 0;
            break;
		}
	}
    return 0;
}