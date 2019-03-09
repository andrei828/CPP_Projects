#include "Graph.h"

template <class T>
Graph<T>::Graph(const std::map< T, std::vector<T> >& graph) {
	this->graph = graph;
}

template <class T>
void Graph<T>::add_edge(const std::pair<T, T>& edge) {
	graph[edge.first].push_back(edge.second);
	visited_nodes.insert(std::pair<T, bool>(edge.first, 0));
	visited_nodes.insert(std::pair<T, bool>(edge.second, 0));
}

template <class T>
void Graph<T>::print_visited_nodes() {
	typename std::map<T, bool>::iterator node;
	for (node = visited_nodes.begin(); node != visited_nodes.end(); ++node)
		std::cout << "(" << node->first << ", " << node->second << "), ";
	std::cout << std::endl;	
}

template <class T>
void Graph<T>::print_graph_incident_list() {
	typename std::map< T, std::vector<T> >::iterator node;
	for (node = graph.begin(); node != graph.end(); ++node) {
		std::cout << node->first << ": ";

		typename std::vector<T>::iterator neighbour;
		for (neighbour = node->second.begin(); neighbour != node->second.end(); ++neighbour)
			std::cout << *neighbour << ' ';
		
		std::cout << std::endl;
	}
}

template <class T>
void Graph<T>::DFS(const T & node) {
	visited_nodes[node] = true;

	typename std::vector<T>::iterator neighbour;
	for (neighbour = graph[node].begin(); neighbour != graph[node].end(); ++neighbour) 
		if (!visited_nodes[*neighbour])
			DFS(*neighbour);
}

template class Graph<int>;