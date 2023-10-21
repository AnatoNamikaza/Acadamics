#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//============================================================================================= Edge Class =================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Edge {

	int src, dest, weight;

	Edge() { src = 0, dest = 0, weight = 0; }

	Edge(Edge const &obj) { src = obj.src, dest = obj.dest, weight = obj.weight; }

	Edge& operator =(Edge const &obj) { src = obj.src, dest = obj.dest, weight = obj.weight; return *this; }

	void Copy(Edge const &obj) { src = obj.src, dest = obj.dest, weight = obj.weight; }

	bool operator == (const Edge &obj) const { return src == obj.src && dest == obj.dest && weight == obj.weight ? true : false; }

	bool operator > (const Edge &obj) const { return src == obj.src &&  weight > obj.weight ? true : false; }

	bool operator < (const Edge &obj) const { return src == obj.src  && weight < obj.weight ? true : false; }

	friend std::ostream& operator << (std::ostream &out, const Edge &obj) { out << obj.src << "->" << obj.dest << " w:" << obj.weight << '\n'; return out; }

	friend std::ofstream& operator << (std::ofstream &fout, const Edge &obj) { fout << obj.src << ',' << obj.dest << ' ' << obj.weight << '\n';	return fout; }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//=========================================================================================== GraphNode Class ==============================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct GraphNode {

	int ID, weight; std::string location; std::vector<Edge> connections;

	GraphNode() { ID = 0, weight = INT_MAX; }

	GraphNode(GraphNode const &obj) { ID = obj.ID, weight = obj.weight, location = obj.location, connections = obj.connections; }

	void Copy(GraphNode const &obj) { ID = obj.ID, weight = obj.weight, location = obj.location, connections = obj.connections; }

	friend std::ostream& operator << (std::ostream &out, const GraphNode &obj) { out << "ID: " << obj.ID << " Location: " << obj.location << " Node_Weight: " << obj.weight << '\n'; return out; }

	friend std::ofstream& operator << (std::ofstream &fout, const GraphNode &obj) { fout << obj.ID << ", " << obj.location << '\n';	return fout; }

};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//============================================================================================ Heap Functions ==============================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct MinHeap {

	std::vector<GraphNode> Heap; int HeapSize;

	MinHeap() { HeapSize = 0; }

	MinHeap(std::vector<GraphNode>& obj) { Heap = obj; HeapSize = obj.size(); Heap[0].weight = 0; }

	void Hswap(int index1, int index2) { GraphNode temp = Heap[index1];	Heap[index1] = Heap[index2]; Heap[index2] = temp; }

	void BuildHeap() { for (int i = ((HeapSize / 2) - 1); i >= 0; i--) { BHeapify(i, HeapSize - 1); } }

	void BHeapify(int index, int size) {
		int LNode = ((index * 2) + 1), RNode = ((index * 2) + 2), Minimum = 0;
		if (LNode <= size) {
			if (LNode == size) { Minimum = LNode; }
			else { if (Heap[LNode].weight <= Heap[RNode].weight) { Minimum = LNode; } else { Minimum = RNode; } }
			if (Heap[index].weight > Heap[Minimum].weight) { Hswap(index, Minimum);	BHeapify(Minimum, size); }
		}
	}

	void decreaseKey(int i) {
		for (int k = 0; k < Heap[i].connections.size(); k++) { for (int v = 0; v < Heap.size(); v++) { if (Heap[v].ID == Heap[i].connections[k].dest) { Heap[v].weight = Heap[i].connections[k].weight; } } }
		for (int v = 0; v < Heap.size(); v++) { for (int k = 0; k < Heap[v].connections.size(); k++) { if (Heap[i].ID == Heap[v].connections[k].dest) { Heap[v].weight = Heap[v].connections[k].weight; } } }
	}

	GraphNode extractMin() { GraphNode temp = Heap[0];	decreaseKey(0);	Heap[0] = Heap[HeapSize - 1]; Heap.pop_back(); HeapSize--; BuildHeap(); return temp; }

	~MinHeap() { HeapSize = 0; }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//=========================================================================================== Extre Functions ==============================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool spanning(bool visitedNode[], int size) { for (int i = 0; i <= size; i++) { if (visitedNode[i] == false) { return false; } };	return true; }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//============================================================================================ Graph Class =================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Graph {

	int totalVertex; std::vector<Edge> Alledges; std::vector<GraphNode>Vertx; std::vector<Edge> SPathEdges; std::list<std::list<GraphNode>> AdjList;

public:

	Graph() { totalVertex = 0; }

	Graph(std::vector<GraphNode> &data, int N, std::vector<Edge> &Edata, int eN) { SetGraphData(data, N, Edata, eN); }

	void SetGraphData(std::vector<GraphNode> &data, int N, std::vector<Edge> &Edata, int eN) {
		totalVertex = N; Vertx = data; Alledges = Edata;
		for (int i = 0; i < totalVertex; i++)for (int j = 0; j < eN; j++)if (i + 1 == Edata[j].src) { Vertx[i].connections.push_back(Edata[j]); }
		AdjList.resize(totalVertex);
		std::list<GraphNode> ::iterator DE; std::list<std::list<GraphNode>>::iterator SE;
		for (SE = AdjList.begin(); SE != AdjList.end(); ++SE) { SE->resize(totalVertex); }
		for (int i = 0; i < eN; i++) {
			SE = AdjList.begin(); int j;
			for (j = 0; j < Edata[i].src - 1 && SE != AdjList.end(); j++) { ++SE; }
			if (j < totalVertex) { DE = SE->begin(); for (j = 0; j < Edata[i].dest - 1 && DE != SE->end(); j++) { ++DE; }if (j < totalVertex) { DE->Copy(Vertx[j]); } }
			//----------------------------------------------------------------------------------------------------------------------------------------------------------
			SE = AdjList.begin();
			for (j = 0; j < Edata[i].dest - 1 && SE != AdjList.end(); j++) { ++SE; }
			if (j < totalVertex) { DE = SE->begin(); for (j = 0; j < Edata[i].src - 1 && DE != SE->end(); j++) { ++DE; }if (j < totalVertex) { DE->Copy(Vertx[j]); } }
		}
		SE = AdjList.begin();
		for (int i = 0; i < N; i++) { DE = SE->begin();	DE->Copy(Vertx[i]); ++SE; }
		if (!ShortestPathGenerator()) { std::cout << "\nNot Shortest Path Exist that cover all nodes.\n"; }
	}

	bool ShortestPathGenerator() {
		MinHeap temp(Vertx); std::vector<GraphNode> sPathNodes;
		for (int i = 0; i < Vertx.size(); i++) { sPathNodes.push_back(temp.extractMin()); }
		bool* visited = new bool[Vertx.size()]{ false }, found;
		for (int k = 0; k < sPathNodes.size(); k++) { visited[sPathNodes[k].ID - 1] = true; }
		if (spanning(visited, Vertx.size())) {
			for (int Xd = 0; Xd < Alledges.size(); Xd++)
				for (int n = 0; n < sPathNodes.size(); n++)
					if (Alledges[Xd].weight == sPathNodes[n].weight&& sPathNodes[n].ID == Alledges[Xd].src || sPathNodes[n].ID == Alledges[Xd].dest && Alledges[Xd].weight == sPathNodes[n].weight)
						SPathEdges.push_back(Alledges[Xd]);
			Edge temp;
			for (int Ck = 0; Ck < SPathEdges.size(); Ck++) {
				temp = SPathEdges[Ck];
				for (int ek = 0; ek < SPathEdges.size(); ek++)
					if (temp == SPathEdges[ek] && Ck != ek) { temp = SPathEdges[SPathEdges.size() - 1], SPathEdges[ek] = temp, SPathEdges.pop_back(); }
			}
			delete[] visited; visited = nullptr; return true;
		}
		delete[] visited; visited = nullptr; return false;
	}

	bool AddEdge() {
		Edge temp;	std::cout << "Enter StartNode of the Edge: "; std::cin >> temp.src;
		if (findVertxIndex(temp.src)) {
			std::cout << "\nEnter EndNode of the Edge: "; std::cin >> temp.dest;
			if (findVertxIndex(temp.dest)) { std::cout << "\nEnter Weight of the Edge: "; std::cin >> temp.weight; Alledges.push_back(temp); SetGraphData(Vertx, Vertx.size(), Alledges, Alledges.size()); return true; }
			else { std::cout << "\nThe Node is not found in the graph.\n"; }
		}
		else { std::cout << "\nThe Node is not found in the graph.\n"; }
		return false;
	}

	void AddVertex() {
		GraphNode tempVx; std::cout << "Enter ID of the Vertx: "; std::cin >> tempVx.ID; std::cout << "\nEnter Location of the Vertx: ";
		std::cin >> tempVx.location; Vertx.push_back(tempVx); std::cout << '\n'; if (!AddEdge()) { SetGraphData(Vertx, Vertx.size(), Alledges, Alledges.size()); }
	}

	bool findVertxIndex(int inx) { for (int i = 0; i < Vertx.size(); i++) { if (inx == Vertx[i].ID) { return true; } }	return false; }

	void InputData(std::string const& filename) {
		std::ifstream fin(filename);
		if (!fin.is_open()) { std::cout << "File could not be accessed.\n"; }
		else {
			std::vector<GraphNode> Data; std::vector<Edge> dataedges; Edge tempEdge; GraphNode tempNode; int TotalNodes = 0, TotalEdges = 0;
			fin >> TotalNodes;
			for (int i = 0; i < TotalNodes; i++) { fin >> tempNode.ID; fin.ignore(2, ', '); std::getline(fin, tempNode.location, '\n'); Data.push_back(tempNode); }
			fin >> TotalEdges;
			for (int i = 0; i < TotalEdges; i++) { fin >> tempEdge.src; fin.ignore(1, ','); fin >> tempEdge.dest >> tempEdge.weight; dataedges.push_back(tempEdge); }
			SetGraphData(Data, TotalNodes, dataedges, TotalEdges);
		}
	}

	void SaveData(std::string const& filename) {
		std::ofstream fout(filename);
		if (!fout.is_open()) { std::cout << "File could not be accessed.\n"; }
		else {
			fout << Vertx.size() << '\n';	for (int i = 0; i < Vertx.size(); i++) { fout << Vertx[i].ID << ", " << Vertx[i].location << '\n'; }
			fout << Alledges.size() << '\n'; for (int i = 0; i < Alledges.size(); i++) { fout << Alledges[i].src << ',' << Alledges[i].dest << ' ' << Alledges[i].weight << '\n'; }
		}
	}

	void PrintAllEdges() { for (int i = 0; i < Alledges.size(); i++) { std::cout << Alledges[i]; } }

	void PrintShortestEdges() { for (int i = 0; i < SPathEdges.size(); i++) { std::cout << SPathEdges[i]; } }

	~Graph() { totalVertex = 0; }

};

//==========================================================================================================================================================================================================