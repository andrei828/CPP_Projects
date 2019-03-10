#include <iostream>
#include "Graph.h"

template <class T>
std::istream& operator >> (std::istream& is, Graph<T> & tmp) {
	
	std::cout << "Number of edges: ";
	T edges; is >> edges;

	std::pair<T, T> edge;
	for (int i = 0; i < edges; i++) {
		is >> edge.first >> edge.second;
		tmp.add_edge(edge);
	}

	return is;}

template <class T>
std::ostream& operator << (std::ostream& os, Graph<T> & tmp) {
	os << "\n******************************\n";
	os << "Incident list of graph:\n";
	tmp.print_graph_incident_list();
	return os << "******************************\n\n";}

template <class T>
Graph<T> operator + (Graph<T> first_term, Graph<T>& second_term) {
	typename std::vector<T>::iterator neigh;
	typename std::map< T, std::vector<T> >::iterator node;
	for (node = second_term.graph.begin(); node != second_term.graph.end(); ++node) {

		if (first_term.graph.find(node->first) != first_term.graph.end()) {
			
			for (neigh = node->second.begin(); neigh != node->second.end(); ++neigh) 
				if (find(first_term.graph[node->first].begin(), first_term.graph[node->first].end(), *neigh) 
					== first_term.graph[node->first].end()) 
					first_term.graph[node->first].push_back(*neigh);
		
		} else {
			first_term.graph.insert(*node);
		}
	}
	return first_term;}

int main() {
	Graph<int> * a = new Graph<int>;
	std::cin >> *a;
	Graph<int> * b = new Graph<int>;
	std::cin >> *b;
	Graph<int> * c = new Graph<int>;
	*c = *a + *b;

	std::cout << *a << std::endl;
	std::cout << *b << std::endl;
	std::cout << *c << std::endl;

	delete a;
	delete b;
	delete c;
}

