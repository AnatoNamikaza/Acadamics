#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int src, dest;
	Edge(int _src, int _dest) { src = _src; dest = _dest; }
};

class Graph {
public:
	int V;
	vector<vector< int>> adjList;

	Graph(const vector<Edge>& edges, int vertices) {
		V = vertices;

		adjList.resize(vertices);

		for (auto& edge : edges) {
			adjList[edge.src].push_back(edge.dest);
		}
	}
};


vector<string> color(Graph& graph) {

	string clist[] = { "RED","BLUE","GREEN","YELLOW","ORANGE","PURPLE" };

	int size = graph.V;

	vector<string> distance;
	distance.resize(size);
	int* arr = new int[size];

	bool allt;

	int i, j;
	for (i = 0; i < size; i++) { arr[i] = 1; }


	for (int i = 0; i < graph.adjList.size(); i++) {
		for (int j = 0; j < graph.adjList[i].size(); j++) {
			graph.adjList[graph.adjList[i][j]].erase(std::remove(graph.adjList[graph.adjList[i][j]].begin(), graph.adjList[graph.adjList[i][j]].end(), i), graph.adjList[graph.adjList[i][j]].end());
		}
	}

	/*for (int i = 0; i < graph.adjList.size(); i++) {
		for (int j = 0; j < graph.adjList[i].size(); j++) {
			cout << i << '\t' << graph.adjList[i][j] << '\n';
		}
	}*/

	while (1) {
		allt = true;
		for (i = 0; i < size; i++)
			for (j = 0; j < graph.adjList[i].size(); j++) {

				if (arr[graph.adjList[i][j]] == arr[i])
				{
					arr[graph.adjList[i][j]] += 1;
					allt = false;
				}
			}
		if (allt == true) { break; }
	}

	/*for (i = 0; i < size; i++) {
		cout<< arr[i]<<" ";
	}
	cout << endl;*/

	for (i = 0; i < size; i++) {
		distance[i] = (clist[arr[i]-1]);
	}

	return distance;
}

int main() {

	vector<Edge> egs;
	Edge e1(0, 1);
	egs.push_back(e1);
	Edge e2(0, 4);
	egs.push_back(e2);
	Edge e3(0, 5);
	egs.push_back(e3);
	Edge e4(4, 5);
	egs.push_back(e4);
	Edge e5(1, 4);
	egs.push_back(e5);
	Edge e6(1, 3);
	egs.push_back(e6);
	Edge e7(2, 3);
	egs.push_back(e7);
	Edge e8(2, 4);
	egs.push_back(e8);
	Edge e11(1, 0);
	egs.push_back(e11);
	Edge e12(4, 0);
	egs.push_back(e12);
	Edge e13(5, 0);
	egs.push_back(e13);
	Edge e14(5, 4);
	egs.push_back(e14);
	Edge e15(4, 1);
	egs.push_back(e15);
	Edge e16(3, 1);
	egs.push_back(e16);
	Edge e17(3, 2);
	egs.push_back(e17);
	Edge e18(4, 2);
	egs.push_back(e18);


	/*for (int i = 0; i < egs.size(); i++) {
		cout << egs[i].src << '\t' << egs[i].dest << '\n';
	}*/

	Graph G(egs, 6);


	//cout << endl;
	//cout << endl;
	//cout << endl;
	//cout << endl;

	for (int i = 0; i < G.adjList.size(); i++) {
		for (int j = 0; j < G.adjList[i].size(); j++) {
			cout << i << '\t' << G.adjList[i][j] << '\n';
		}
	}

	cout << endl;
	cout << endl;

	vector<string> res = color(G);


	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	for (int i = 0; i < res.size(); i++) {
		cout << i << '\t' << res[i] << '\n';
	}

	return 0;
}