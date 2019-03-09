#include <iostream>
#include "Graph.h"
#include <vector>
#include <map>

template <class T>
std::istream& operator >> (std::istream& is, Graph<T> & tmp) {
	
	std::cout << "Number of edges: ";
	T edges; is >> edges;

	std::pair<T, T> edge;
	for (int i = 0; i < edges; i++) {
		is >> edge.first >> edge.second;

		tmp.add_edge(edge);
	}

	return is;
}

template <class T>
std::ostream& operator << (std::ostream& os, Graph<T> & tmp) {
	os << "\n******************************\n";
	os << "Incident list of graph:\n";
	tmp.print_graph_incident_list();
	return os << "******************************\n\n";
}

int main() {
	Graph<int> g;
	std::cin >> g;
	std::cout << g;
	g.DFS(1);
}
