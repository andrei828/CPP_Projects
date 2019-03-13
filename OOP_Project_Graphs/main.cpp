#include "menu_impl.h"

template <class T>
std::istream& operator >> (std::istream& is, Graph<T> & tmp) {
	
	std::cout << "Number of edges: ";
	int edges; is >> edges;

	std::cout << "Input edges:\n";
	std::pair<T, T> edge;
	for (int i = 0; i < edges; i++) {
		is >> edge.first >> edge.second;
		tmp.add_edge(edge);
	}

	return is;
}

template <class T>
std::ostream& operator << (std::ostream& os, Graph<T> & tmp) {
	tmp.print_graph_incident_list();
	return os;
}

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
	return first_term;
}

int main() {
	print_main_menu();

	// main menu
	//////////////////////////////////////////////////
	// Current graphs:								
	// { nume1, nume2, nume3 }						
	//												
	// 1) Add new Graph 							
	//												
	// 2) Show/Edit graph data						
	//												
	// 3) Delete graph 							
	//												
	// 4) Add two graphs							
	//												
	// 5) Reset										
	//  > 											
	//////////////////////////////////////////////////

	
	// add new graph menu
	//////////////////////////////////////////////////
	// Graph name: Network							
	// Graph data type: string						
	// Number of edges: 4							
	// Input edges:									
	// x y											
	// z y										 	
	// t b 										  	
	// s o 										  	
	// Graph created! Press any key to go back... 	
 	//////////////////////////////////////////////////	


	// show/edit graph data menu
	//////////////////////////////////////////////////
	// Graph: nume2									
	//												
	// 1) Print graph 								
	// 2) Print connected nodes matrix              
	// 3) Print strongly connected components		
	// 4) DFS										
	// 5) BFS										
	// 6) Add new edge 								
	// 7) Go back 									
	//  > 											
	//////////////////////////////////////////////////
}



