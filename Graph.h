#include <iostream>
#include <vector>
#include <fstream>

namespace fs = std::experimental::filesystem;

struct Edge {
	int src, dest;
};

class Graph
{
public:
	std::vector<std::vector<int>> adjList;

    void AddNode(const int src, const int dest)
    {
        if(adjList.size() == src)
            adjList.push_back({});
        adjList[src].push_back(dest);
    }

    void ReadGraph()
    {
        fs::create_directories(".lit/graph.txt");
        std::ifstream is(".lit/graph.txt");
        std::string str;
        int row = 0;
        while(std::getline(is,str)) {
            std::istringstream ss(str);
            adjList.push_back({});
            int node;
            while(ss >> node) adjList[row++].push_back(node);
        }
    }

};


void printGraph(Graph const& graph, int N)
{
	for (int i = 0; i < N; i++)
	{
		// print current vertex number
		std::cout << i << " --> ";

		// print all neighboring vertices of vertex i
		for (int v : graph.adjList[i])
			std::cout << v << " ";
		std::cout << std::endl;
	}
}
/*
// Graph Implementation using STL
int main()
{
	// vector of graph edges as per above diagram.
	// Please note that initialization vector in below format will
	// work fine in C++11, C++14, C++17 but will fail in C++98.
	vector<Edge> edges =
	{
		{ 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
		{ 3, 2 }, { 4, 5 }, { 5, 4 }
	};

	// Number of nodes in the graph
	int N = 6;

	// construct graph
	Graph graph(edges, N);

	// print adjacency list representation of graph
	printGraph(graph, N);

	return 0;
}*/