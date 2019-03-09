#include <iostream>
#include <vector>
#include <map>
#include <set>

template <class T>
class Graph;

template <class T>
std::istream& operator >> (std::istream&, Graph<T>&);

template <class T>
std::ostream& operator << (std::ostream&, Graph<T>&);

template <class T>
class Graph {

	std::map< T, bool > visited_nodes;
	std::map< T, std::vector<T> > graph;

public:

	Graph() {}
	Graph(const std::map< T, std::vector<T> >&);
	
	friend std::istream& operator >> <>(std::istream&, Graph<T>&);
	friend std::ostream& operator << <>(std::ostream&, Graph<T>&);

	void DFS(const T & node);

	void print_visited_nodes();
	void print_graph_incident_list();

	void add_edge(const std::pair<T, T>&);	
};

