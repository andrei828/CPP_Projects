#include <iostream>
#include <typeinfo>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

template <class T>
class Graph;

template <class T>
std::istream& operator >> (std::istream&, Graph<T>&);

template <class T>
std::ostream& operator << (std::ostream&, Graph<T>&);

template <class T>
Graph<T> operator + (Graph<T>, Graph<T>&);

template <class T>
class Graph {

	std::string name;
	std::map< T, bool > visited_nodes;
	std::map< T, std::vector<T> > graph;
	std::map< std::pair<T, T>, bool> connected_nodes;
	std::vector< std::vector<T> > strongly_connected_components;

	void clear_visited_nodes();
	void init_strongly_conn_comp();
	void init_connected_nodes_matrix();
	bool is_graph_strongly_connected();
	bool DFS_utils(const T & , const T &);
	void DFS_fill_stack(const T &, std::stack<T>&);
	std::vector<T> DFS(T, std::map< T, std::vector<T> >&);
	
public:
	
	Graph() {};
	Graph(std::string name) : name(name) {};
	Graph(const std::map< T, std::vector<T> >&);
	
	friend Graph<T> operator + <>(Graph<T>, Graph<T>&);
	friend std::istream& operator >> <>(std::istream&, Graph<T>&);
	friend std::ostream& operator << <>(std::ostream&, Graph<T>&);

	void DFS(T);
	void BFS(T);

	std::string get_name();
	std::string get_type();
	void print_visited_nodes();
	void print_graph_incident_list();
	void print_connected_nodes_matrix();
	void print_strongly_connected_components();
	
	void add_node(const T&);
	void add_edge(const std::pair<T, T>&);
};

