#include "Graph.h"

Graph::Graph(const std::map< int, std::vector<int> >& graph) {
	this->graph = graph;
}

void Graph::add_edge(const std::pair<int, int>& edge) {
	graph[edge.first].push_back(edge.second);
	visited_nodes.insert(std::pair<int, bool>(edge.first, 0));
	visited_nodes.insert(std::pair<int, bool>(edge.second, 0));
}

void Graph::print_visited_nodes() {
	std::map< int, bool>::iterator node;
	for (node = visited_nodes.begin(); node != visited_nodes.end(); ++node)
		std::cout << "(" << node->first << ", " << node->second << "), ";
	std::cout << std::endl;	
}

void Graph::print_graph_incident_list() {
	std::map< int, std::vector<int> >::iterator node;
	for (node = graph.begin(); node != graph.end(); ++node) {
		std::cout << node->first << ": ";

		std::vector<int>::iterator neighbour;
		for (neighbour = node->second.begin(); neighbour != node->second.end(); ++neighbour)
			std::cout << *neighbour << ' ';
		
		std::cout << std::endl;
	}
}

void Graph::DFS(const int & node) {
	visited_nodes[node] = true;

	std::vector<int>::iterator neighbour;
	for (neighbour = graph[node].begin(); neighbour != graph[node].end(); ++neighbour) 
		if (!visited_nodes[*neighbour])
			DFS(*neighbour);
}
