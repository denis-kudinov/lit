#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Graph {
public:
  std::vector<std::vector<int>> adjList;

  void AddNode(const int src, const int dest) {
    if (adjList.size() == src)
      adjList.push_back({});
    adjList[src].push_back(dest);
    PrintGraph();
  }

  void ReadGraph() {
    std::ifstream in(".lit/graph.txt");
    std::string str;
    int row = 0;
    while (std::getline(in, str)) {
      std::istringstream ss(str);
      adjList.push_back({});
      int node;
      while (ss >> node)
        adjList[row].push_back(node);
      row++;
    }
    in.close();
  }

  void PrintGraph() {
    std::ofstream out(".lit/graph.txt");

    for (auto i : adjList) {
      for (auto j : i)
        out << j << " ";
      out << "\n";
    }
    out.close();
  }
};