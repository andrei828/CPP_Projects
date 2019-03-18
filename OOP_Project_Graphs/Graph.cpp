#define STARS "******************************\n"
#include "Graph.h"

template <class T>
Graph<T>::Graph(const std::map< T, std::vector<T> >& graph) {
	this->graph = graph;
}

// Graph services

template <class T>
void Graph<T>::add_node(const T& node) {
	graph[node] = std::vector<T>();
	visited_nodes.insert(std::pair<T, bool>(node, false));
}

template <class T>
void Graph<T>::add_edge(const std::pair<T, T>& edge) {
	if (visited_nodes.find(edge.first)  != visited_nodes.end() && 
		visited_nodes.find(edge.second) != visited_nodes.end()) {
		
		connected_nodes[edge] = true;
		graph[edge.first].push_back(edge.second);
		connected_nodes[std::pair<T,T>(edge.first, edge.first)] = true;
		connected_nodes[std::pair<T,T>(edge.second, edge.second)] = true;
	}
}

template <class T>
std::string Graph<T>::get_name() { return name; }

template <class T>
std::string Graph<T>::get_type() { return typeid(T).name(); }

template <class T>
void Graph<T>::clear_visited_nodes() {
	typename std::map < T, bool >::iterator node;
	for (node = visited_nodes.begin(); node != visited_nodes.end(); ++node)
		node->second = false;
}

template <class T>
void Graph<T>::init_connected_nodes_matrix() {
	typename std::map<T, bool>::iterator row;
	typename std::map<T, bool>::iterator col;

	for (row = visited_nodes.begin(); row != visited_nodes.end(); ++row) 
		for (col = visited_nodes.begin(); col != visited_nodes.end(); ++col) 
			if (connected_nodes.find(std::pair<T, T>(row->first, col->first)) == connected_nodes.end()) {
				clear_visited_nodes();
				if (DFS_utils(row->first, col->first))
					connected_nodes[std::pair<T, T>(row->first, col->first)] = true;
				else
					connected_nodes[std::pair<T, T>(row->first, col->first)] = false;
			}
}

template <class T>
void Graph<T>::init_strongly_conn_comp() {
	// 1) Mark all the vertices as not visited (for first DFS)	
	// 2) Fill vertices in stack according to their finishing times
	// 3) Create a reversed graph
	// 4) Mark all the vertices as not visited (for second DFS)
	// 5) Process all vertices in order defined by stack

	std::stack<T> Stack;
	std::vector< std::vector<T> > result;
	std::map< T, std::vector<T> > reversed_graph;
	strongly_connected_components.clear();
	
	clear_visited_nodes();

	typename std::map< T, bool >::iterator node;
	for (node = visited_nodes.begin(); node != visited_nodes.end(); ++node) 
		if (!visited_nodes[node->first])
			DFS_fill_stack(node->first, Stack);

	
	typename std::vector<T>::iterator list_node;
	typename std::map< T, std::vector<T> >::iterator graph_node;
	for (graph_node = graph.begin(); graph_node != graph.end(); ++graph_node) 
		for (list_node = graph_node->second.begin(); list_node != graph_node->second.end(); ++list_node)
			reversed_graph[*list_node].push_back(graph_node->first);

	clear_visited_nodes();

	while (!Stack.empty()) {
		T top = Stack.top();
		Stack.pop();

		if (!visited_nodes[top]) 
			strongly_connected_components.push_back(DFS(top, reversed_graph));
	}
}

template <class T>
bool Graph<T>::is_graph_strongly_connected() {
	init_strongly_conn_comp();
	if (strongly_connected_components.size() == 1) return true;
	return false;
}

// Graph printing 

template <class T>
void Graph<T>::print_visited_nodes() {
	if (!visited_nodes.empty()) {
		std::cout << "\n{ ";
		typename std::map<T, bool>::iterator node = visited_nodes.begin();
		std::cout << node->first; ++node; 
		for (; node != visited_nodes.end(); ++node) {
			std::cout << ", " << node->first;
		}
		std::cout << "}"<< std::endl;	
	} else 
		std::cout << "{ }";
}

template <class T>
void Graph<T>::print_graph_incident_list() {
	typename std::vector<T>::iterator neighbour;
	typename std::map< T, std::vector<T> >::iterator node;

	std::cout << '\n' << STARS << "Incident list of graph:\n";
	for (node = graph.begin(); node != graph.end(); ++node) {
		std::cout << node->first << ": ";

		for (neighbour = node->second.begin(); neighbour != node->second.end(); ++neighbour)
			std::cout << *neighbour << ' ';
		
		std::cout << std::endl;
	}
	std::cout << STARS << '\n';
}

template <class T>
void Graph<T>::print_connected_nodes_matrix() {

	init_connected_nodes_matrix();
	typename std::map<T, bool>::iterator row;
	typename std::map<T, bool>::iterator col;

	std::cout << STARS << "Connected nodes matrix:\n\t";
	for (row = visited_nodes.begin(); row != visited_nodes.end(); ++row)
		std::cout << row->first << '\t';
	std::cout << std::endl;

	for (row = visited_nodes.begin(); row != visited_nodes.end(); ++row) {
		std::cout << row->first << ":\t";
		for (col = visited_nodes.begin(); col != visited_nodes.end(); ++col) 
			std::cout << connected_nodes[std::pair<T, T>(row->first, col->first)] << '\t';
		std::cout << std::endl;
	}
	std::cout << STARS << std::endl;
}

template <class T>
void Graph<T>::print_strongly_connected_components() {
	std::cout << STARS;
	std::cout << "List of strongly connex components:\n";
	init_strongly_conn_comp();
	typename std::vector<T>::iterator node;
	typename std::vector< std::vector<T> >::iterator list_of_lists;
	for (list_of_lists = strongly_connected_components.begin(); 
		list_of_lists != strongly_connected_components.end(); ++list_of_lists) {

		std::cout << "{ ";
		for (node = list_of_lists->begin(); node != list_of_lists->end(); ++node) {
			std::cout << *node << " ";
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "The graph is ";
	if (strongly_connected_components.size() != 1) std::cout << "not ";
	std::cout << "strongly connex\n" << STARS << std::endl;
}

// Graph iterations:

template <class T>
void Graph<T>::DFS(T node) {
	std::stack<T> graph_stack;
	std::cout << STARS << "DFS: ";
	
	clear_visited_nodes();
	graph_stack.push(node);

	while(!graph_stack.empty()) {
		node = graph_stack.top();
		graph_stack.pop();

		if (!visited_nodes[node]) {
			std::cout << node << ' ';
			visited_nodes[node] = true;
		}

		typename std::vector<T>::iterator neighbour;
		for (neighbour = graph[node].begin(); neighbour != graph[node].end(); ++neighbour)  
			if (!visited_nodes[*neighbour]) 
				graph_stack.push(*neighbour);
	}
	std::cout << std::endl << STARS << std::endl;
}

template <class T>
std::vector<T> Graph<T>::DFS(T node, std::map< T, std::vector<T> > & graph) {
	std::vector<T> result;
	std::stack<T> graph_stack;
	graph_stack.push(node);

	while(!graph_stack.empty()) {
		node = graph_stack.top();
		graph_stack.pop();

		if (!visited_nodes[node]) {
			result.push_back(node);
			visited_nodes[node] = true;
		}

		typename std::vector<T>::iterator neighbour;
		for (neighbour = graph[node].begin(); neighbour != graph[node].end(); ++neighbour)  
			if (!visited_nodes[*neighbour]) 
				graph_stack.push(*neighbour);
	}
	return result;
}

template <class T>
void Graph<T>::BFS(T node) {
	std::queue<T> graph_queue;
	std::cout << STARS << "BFS: ";
	clear_visited_nodes();
	graph_queue.push(node);
	visited_nodes[node] = true;

	while(!graph_queue.empty()) {

		T first_elem = graph_queue.front();
		graph_queue.pop();

		std::cout << first_elem << ' ';

		typename std::vector<T>::iterator neighbour;
		for (neighbour = graph[first_elem].begin(); neighbour != graph[first_elem].end(); ++neighbour) { 
			if (!visited_nodes[*neighbour]) {
				graph_queue.push(*neighbour);
				visited_nodes[*neighbour] = true;
			}
		}
	}
	std::cout << std::endl << STARS << std::endl;
}

template <class T>
bool Graph<T>::DFS_utils(const T & start, const T & finish) {
	visited_nodes[start] = true;

	typename std::vector<T>::iterator neighbour;
	for (neighbour = graph[start].begin(); neighbour != graph[start].end(); ++neighbour)
		if (!visited_nodes[*neighbour])
			DFS_utils(*neighbour, finish);
	
	return visited_nodes[finish];
}

template <class T>
void Graph<T>::DFS_fill_stack(const T & node, std::stack<T> & Stack) {
	visited_nodes[node] = true;

	typename std::vector<T>::iterator neighbour;
	for (neighbour = graph[node].begin(); neighbour != graph[node].end(); ++neighbour)
		if (!visited_nodes[*neighbour])
			DFS_fill_stack(*neighbour, Stack);
	Stack.push(node);
}

template class Graph<int>;
template class Graph<char>;
template class Graph<short>;
template class Graph<float>;
template class Graph<double>;
template class Graph<std::string>;

























