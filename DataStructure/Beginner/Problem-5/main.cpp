#include "Graph.h"

int main() {
	Graph G;

	int val;
	std::string filename;

	while (true) {
		std::cout << "1.File options | 2.Input Options | 3.Print Options | 4.Exit \n";
		std::cout << "Enter choice: \n";
		std::cin >> val;
		system("cls");
		if (val == 1) {
			val = 0;
			std::cout << "1.Input Graph Data from file | 2.Save Graph Data in File | 3.clear Data From file\n";
			std::cout << "Enter choice: \n";
			std::cin >> val;
			system("cls");
			if (val == 1) {
				std::cin.ignore(1);
				//std::cout << "Enter filename: \n";
				//std::cin >> filename;
				filename = "Graph Info.txt";
				G.InputData(filename);
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
				if (val == 2) {
					return 0;
				}
				else if (val == 1) {}
				system("cls");
				val = 0;
			}
			else if (val == 2) {
				//std::cout << "Enter filename: \n";
				//std::cin >> filename;
				filename = "SGraph.txt";
				std::ofstream fout(filename);
				if (!fout.is_open()) { std::cout << "File could not be accessed.\n"; }
				else { G.SaveData(filename); }
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
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
				//std::cout << "Enter filename: \n";
				//std::cin >> filename;
				filename = "SGraph.txt";
				std::ofstream fout(filename);
				if (!fout.is_open()) { std::cout << "File could not be accessed.\n"; }
				else { fout << "\0"; }
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
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
			std::cin.ignore(1);
			val = 0;
			std::cout << "1.Add New Vertex | 2.Add New Edge | 3.Back to main\n";
			std::cout << "Enter choice: \n";
			std::cin >> val;
			system("cls");
			if (val == 1) {
				G.AddVertex();
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
				if (val == 2) {
					return 0;
				}
				else if (val == 1) {
					system("cls");
					val = 0;
				}
			}
			else if (val == 2) {
				G.AddEdge();
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
				if (val == 2) {
					return 0;
				}
				else if (val == 1) {
					system("cls");
					val = 0;
				}
			}
			system("cls");
			val = 0;
		}
		else if (val == 3) {
			std::cin.ignore(1);
			val = 0;
			std::cout << "1.Print All Paths | 2.Print Shortest Path | 3.Back to main\n";
			std::cout << "Enter choice: \n";
			std::cin >> val;
			system("cls");
			if (val == 1) {
				G.PrintAllEdges();
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
				if (val == 2) {
					return 0;
				}
				else if (val == 1) {
					system("cls");
					val = 0;
				}
			}
			else if (val == 2) {
				G.PrintShortestEdges();
				val = 0;
				std::cout << "1.Back to main menu 2.Exit\n";
				std::cout << "Enter choice: \n";
				std::cin >> val;
				if (val == 2) {
					return 0;
				}
				else if (val == 1) {
					system("cls");
					val = 0;
				}
			}
			system("cls");
			val = 0;
		}
		else if (val == 4) { return 0; }
	}

	return 0;
}
