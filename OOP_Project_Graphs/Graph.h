#include <iostream>
#include <vector>
#include <map>
#include <set>

class Graph {

	std::map< int, bool > visited_nodes;
	std::map< int, std::vector<int> > graph;

public:

	Graph() {}
	Graph(const std::map< int, std::vector<int> >&);
	
	friend std::istream& operator >>(std::istream& is, Graph & tmp);
	friend std::istream& operator <<(std::istream& is, const Graph & tmp);

	void add_edge(const std::pair<int, int>&);
	
	void print_visited_nodes();
	void print_graph_incident_list();

	void DFS(const int & node);
};