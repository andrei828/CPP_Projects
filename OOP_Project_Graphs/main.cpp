#include <iostream>
#include "Graph.h"

#include <vector>
#include <map>

std::istream& operator >>(std::istream& is, Graph & tmp) {
	
	std::cout << "Number of edges: ";
	int edges; is >> edges;

	std::pair<int, int> edge;
	for (int i = 0; i < edges; i++) {
		is >> edge.first >> edge.second;

		tmp.add_edge(edge);
	}

	return is;
}

std::ostream& operator <<(std::ostream& is, Graph & tmp) {
	is << "\n******************************\n" << "Incident list of graph:\n";
	tmp.print_graph_incident_list();
	is << "******************************\n\n";
	return is;
}

int main() {
	
	std::map< int, std::vector<int> > test;
	std::pair<int, std::vector<int> > tmp;

	for (int i = 1; i <= 5; i++) {
		tmp.first = i;

		for (int j = 0; j <= i; j++)
			tmp.second.push_back(j);

		test.insert(tmp);
		tmp.second.clear();
	}

	//Graph * g = new Graph(test);
	//g->print_graph_incident_list();
	Graph g;
	std::cin >> g;
	std::cout << g;
	g.DFS(1);
	g.print_visited_nodes();
}
