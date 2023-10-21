#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <list>

struct Edge { int src, dest, weight; };

struct GraphNode {

    int ID, weight; std::string location; std::vector<Edge> connections;

    GraphNode() { ID = 0, weight = 10000; }

    void Copy(GraphNode const &obj) { ID = obj.ID, weight = obj.weight, location = obj.location, connections = obj.connections; }

};

class Graph {

    int totalVertex;
    std::vector<Edge> Gedges;
    std::list<std::list<GraphNode>> AdjList;

public:

    Graph(std::list<GraphNode > const &data, int N) {
        totalVertex = N;
        AdjList.resize(totalVertex);
        for (auto SN = AdjList.begin(); SN != AdjList.end(); ++SN) { SN->resize(totalVertex); }
        std::_List_const_iterator<GraphNode> DN;
        for (auto SN = AdjList.begin(), DN = data.begin(); DN != data.end() && SN != AdjList.end(); ++SN, ++DN) {
            SN->begin()->Copy(*DN);
        }

        //std::vector<Edge>::iterator SE;
        //for (SE = edges.begin(); SE != edges.end(); ++SE) { adjList[SE->src][SE->dest] = SE->weight; }
        //Gedges = edges;
    }

//	bool EdgeExist(int sr, int de) { return 	adjList[sr][de] == 1 ? true : false; }
//
//	void DisplayCycle(bool visited[], int start, int ns, int ind, bool &found, vector<Edge> cycle) {
//		visited[ind] = true;
//		cycle.push_back(Gedges[ind]);
//		for (int i = 0; i < Gedges.size(); i++) {
//			if (Gedges[i].src == ns && Gedges[i].dest == start) {
//				cycle.push_back(Gedges[i]);
//				cout << "Cycle is: \n";
//				int k;
//				for (k = 0; k < cycle.size(); k++)
//					if (k + 1 < cycle.size() && cycle[k].src == cycle[k + 1].src) { cout << cycle[k].src << "->"; k++; }
//					else { cout << cycle[k].src << "->"; }
//				cout << cycle[k - 1].dest << "\n";
//				found = true;
//			}
//			else if (Gedges[i].src == ns && visited[i] == false) {
//				DisplayCycle(visited, start, Gedges[i].dest, i, found, cycle);
//			}
//		}
//	}
//
//
//
//	bool printCycle() {
//		bool* visited = new bool[Gedges.size()]{ false };
//		bool found = false;
//		vector<Edge> cycle;
//		for (int i = 0; i < Gedges.size(); i++)
//			DisplayCycle(visited, Gedges[i].src, Gedges[i].dest, i, found, cycle);
//		delete[] visited; visited = nullptr;
//		return found;
//	}
//
//
//	void isBipartite() {
//		int* colorArr = new int[totalVertex];
//		for (int c = 0; c < totalVertex + 1; c++) { colorArr[c] = -1; }
//		colorArr[0] = 1;
//		if (Bipartite(1, colorArr, 1)) {
//			std::cout << "Set X = { ";
//			for (int v = 0; v < totalVertex + 1; v++)
//				if (colorArr[v] == 0)  std::cout << v + 1 << " ";
//			std::cout << "} \nSet Y = { ";
//			for (int v = 0; v < totalVertex + 1; v++)
//				if (colorArr[v] == 1)  std::cout << v + 1 << " ";
//			std::cout << "} \n ";
//		}
//		else {
//			std::cout << "Graph is not Bipartite.\n";
//		}
//	}
//
//	bool Bipartite(int color, int *&colorArr, int index) {
//		if (index < totalVertex) {
//			for (int i = 0; i < Gedges.size(); i++) {
//				if (Gedges[i].src == index && colorArr[Gedges[i].dest - 1] == -1) {
//					colorArr[Gedges[i].dest - 1] = ((colorArr[Gedges[i].src - 1] + 1) % 2);
//				}
//				else if (Gedges[i].src == index && colorArr[Gedges[i].dest - 1] == colorArr[Gedges[i].src - 1]) {
//					return false;
//				}
//			}
//			return Bipartite(((color + 1) % 2), colorArr, index + 1);
//		}
//		return true;
//	}
//
//	bool EulerPath() {
//		bool* visited = new bool[Gedges.size()]{ false };
//		bool found = false;
//		vector<Edge> Euler;
//		for (int i = 0; i < Gedges.size(); i++) {
//			if (findEuler(visited, Gedges[i].src, Gedges[i].dest, i, Euler, found) || found == true) {
//				delete[] visited; visited = nullptr;
//				return true;
//			}
//		}
//		delete[] visited; visited = nullptr;
//		return found;
//	}
//
//	bool findEuler(bool visited[], int start, int ns, int ind, vector<Edge> Euler, bool &found) {
//		visited[ind] = true;
//		Euler.push_back(Gedges[ind]);
//		for (int i = 0; i < Gedges.size(); i++) {
//			if (Gedges[i].src == ns && Gedges[i].dest == start) {
//				if (!findEuler(visited, start, Gedges[i].dest, i, Euler, found)) {
//					Euler.push_back(Gedges[i]);
//					cout << "Euler Path's Edges are: \n";
//					int k;
//					for (k = 0; k < Euler.size(); k++)
//						cout << Euler[k].src << "->" << Euler[k].dest << "\n";
//					cout << "Euler Circuit is: \n";
//					for (k = 0; k < Euler.size(); k++)
//						cout << Euler[k].src << "->";
//					cout << Euler[k - 1].dest << "\n";
//					return found = true;
//				}
//			}
//			else if (Gedges[i].src == ns && visited[i] == false) {
//				return findEuler(visited, start, Gedges[i].dest, i, Euler, found);
//			}
//		}
//		return false;
//	}
//
//	bool spamming(bool visitedNode[]) {
//		for (int i = 0; i <= totalVertex; i++)
//			if (visitedNode[i] == false) { return false; }
//		return true;
//	}
//
//	bool shortestPath() {
//		bool* visitedNode = new bool[totalVertex] { false };
//		bool* visitedEdge = new bool[Gedges.size()]{ false };
//		vector<Edge> Path;
//		int lowest = 100000, edgeIndex, testsum = 0, vertexcount = 0;
//		for (int i = 0; i < Gedges.size(); i++)
//			if (Gedges[i].src == 1 && Gedges[i].weight < lowest)
//				lowest = Gedges[i].weight, edgeIndex = i;
//		shortPathFinder(edgeIndex, testsum, visitedNode, visitedEdge, Path, vertexcount);
//		if (spamming(visitedNode)) {
//			cout << "\nShortest Path: ";
//			int k;
//			for (k = 0; k < Path.size(); k++)
//				if (k + 1 < Path.size() && Path[k].src == Path[k + 1].src) {
//					cout << Path[k].src << "->"; k++;
//				}
//				else { cout << Path[k].src << "->"; }
//			cout << Path[k - 1].dest << "\nTotal Weight: " << testsum << "\n";
//			delete[] visitedNode; visitedNode = nullptr;
//			delete[] visitedEdge; visitedEdge = nullptr;
//			return true;
//		}
//		else {
//			delete[] visitedNode; visitedNode = nullptr;
//			delete[] visitedEdge; visitedEdge = nullptr;
//			return false;
//		}
//	}
//
//	void shortPathFinder(int index, int &testsum, bool *&visitedNode, bool visitedEdge[], vector<Edge> &path, int vertexcount) {
//		if (vertexcount <= totalVertex - 1) {
//			vertexcount++;
//			visitedEdge[index] = true;
//			testsum += Gedges[index].weight;
//			visitedNode[Gedges[index].src - 1] = true;
//			path.push_back(Gedges[index]);
//			int lowest = 100000, edgeIndex;
//			for (int i = 0; i < Gedges.size(); i++)
//				if (Gedges[i].src == Gedges[index].dest && Gedges[i].weight < lowest)
//					lowest = Gedges[i].weight, edgeIndex = i;
//			if (lowest != 100000)
//				shortPathFinder(edgeIndex, testsum, visitedNode, visitedEdge, path, vertexcount);
//			else {
//				visitedNode[Gedges[index].dest - 1] = true;
//			}
//		}
//	}
//
};

int main() {
    std::ifstream fin("Graph Info.txt");
    if (!fin.is_open()) { std::cout << "File could not be accessed.\n"; }
    else {
        std::list<GraphNode> Data;
        std::vector<Edge> dataedges;
        Edge tempEdge;
        GraphNode tempNode;
        int TotalNodes = 0, TotalEdges = 0;
        fin >> TotalNodes;
        for (int i = 0; i < TotalNodes; i++) {
            fin >> tempNode.ID;
            fin.ignore(2, ', ');
            std::getline(fin, tempNode.location, '\n');
            Data.push_back(tempNode);
        }
        fin >> TotalEdges;
        for (int i = 0; i < TotalEdges; i++) {
            fin >> tempEdge.src;
            fin.ignore(1, ',');
            fin >> tempEdge.dest >> tempEdge.weight;
            dataedges.push_back(tempEdge);
        }

        //if (s == d) {
        //	N = s;
        //	while (true) {
        //		fin >> s >> d >> w;
        //		if (N < 0) { break; }
        //		if (s != d) {
        //			CurrentEdge.src = s, CurrentEdge.dest = d, CurrentEdge.weight = w;
        //			edges.push_back(CurrentEdge);
        //		}
        //		else if (s == d) {
        //			Graph graph(edges, N);
        //			graphList.push_back(graph);
        //			edges.clear();
        //			N = s;
        //		}
        //	}
        //	N = 0;
        //	std::list<Graph>::iterator SG;
        //	for (SG = graphList.begin(); SG != graphList.end(); SG++) {
        //		std::cout << "Graph#" << N + 1 << "\n", N++;
        //		std::cout << "\nCycles in graph:\n";
        //		if (!SG->printCycle()) { std::cout << "Cycles not found.\n"; }
        //		std::cout << "\n";
        //		SG->isBipartite();
        //		std::cout << "\n";
        //		if (!SG->EulerPath()) { std::cout << "Euler Path doesn't exist.\n"; }
        //		if (!SG->shortestPath()) { std::cout << "Shortest Path doesn't exist.\n"; }
        //		std::cout << "\n-------------------------------------------------------\n";
        //	}
        //}
        //else { std::cout << "Graph could not be created.\n"; }
    }
    return 0;
}