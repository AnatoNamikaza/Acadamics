#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int src, dest, weight;
	Edge(int _src, int _dest, int _weight) { src = _src; dest = _dest; weight = _weight; }
};

class Graph {
public:
	int numVertices;
	vector<vector<pair<int, int>>> adjList;
	// e.g. 0: {1, 12}, {2, 4} -> the weight from vertex 0 to 1 is 12 
	//                        and the weight from vertex 0 to 2 is 4

	Graph(const vector<Edge>& edges, int vertices) {
		numVertices = vertices;

		adjList.resize(vertices);

		for (auto& edge : edges) {
			adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
		}
	}
};

void shortestdist(const Graph& graph, int src, vector<int>& distance, int prev_weight) {
	int i;
	for (i = 0; i < graph.adjList[src].size(); i++) {

		if (distance[graph.adjList[src][i].first] > prev_weight + graph.adjList[src][i].second) {
			distance[graph.adjList[src][i].first] = prev_weight + graph.adjList[src][i].second;
		}
	}

	for (i = 0; i < graph.adjList[src].size(); i++) {
		shortestdist(graph, graph.adjList[src][i].first, distance, prev_weight + graph.adjList[src][i].second);
	}
}

vector<int> dijkstra(const Graph& graph, int src) {

	int size = graph.numVertices;

	vector<int> distance;
	distance.resize(size);
	for (int i = 0; i < size; i++) { distance[i] = INT_MAX; };

	distance[src] = 0;

	shortestdist(graph, src, distance, 0);

	return distance;
}

int main() {

	vector<Edge> egs;
	Edge e1(0, 1, 4);
	egs.push_back(e1);
	Edge e2(1, 2, 1);
	egs.push_back(e2);
	Edge e3(2, 3, 8);
	egs.push_back(e3);
	Edge e4(3, 4, 9);
	egs.push_back(e4);
	Edge e5(3, 5, 5);
	egs.push_back(e5);
	Edge e6(5, 4, 12);
	egs.push_back(e6);
	Edge e7(6, 5, 7);
	egs.push_back(e7);
	Edge e8(0, 6, 10);
	egs.push_back(e8);
	Edge e9(1, 6, 2);
	egs.push_back(e9);
	Edge e10(6, 2, 6);
	egs.push_back(e10);


	for (int i = 0; i < egs.size(); i++) {
		cout << egs[i].src << '\t' << egs[i].dest << '\t' << egs[i].weight << '\n';
	}

	Graph G(egs, 7);


	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	for (int i = 0; i < G.adjList.size(); i++) {
		for (int j = 0; j < G.adjList[i].size(); j++) {
			cout << i << '\t' << G.adjList[i][j].first << '\t' << G.adjList[i][j].second << '\n';
		}
	}

	vector<int> res = dijkstra(G, 0);


	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	for (int i = 0; i < res.size(); i++) {
		cout << i << '\t' << res[i] << '\n';
	}

	return 0;
}