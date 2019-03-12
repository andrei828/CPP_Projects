#include "Graph.h"
#define MAX_NUM_OF_GRAPHS 10
#define CLEAR system("clear")

std::vector< std::string > graph_name;
std::vector< std::pair< void *, std::string > > graph_list;

void testing();
void print_main_menu();
void reset_everything();
void print_add_graph_menu();
void choose_graph_for_info();
void choose_graph_for_deletion();
template <class T> void print_graph_data(Graph<T> * tmp);
void print_graph_name_from_list(std::vector<std::pair< void *, std::string > >::iterator & graph);

void print_main_menu() {
	int option;
	RETRY_CHOICE:
	CLEAR;
	std::cout << "\nCurrent graphs:\n { ";

	if (!graph_list.empty()) {
		std::vector<std::string>::iterator name = graph_name.begin();
		std::cout << *name; ++name;
		for (; name != graph_name.end(); ++name)
			std::cout << ", " << *name;
	}
	else 
		std::cout << '~';

	std::cout << " }" << std::endl << std::endl;
	std::cout << "1) Add new graph\n\n";
	std::cout << "2) Show/Edit graph data\n\n";
	std::cout << "3) Delete graph\n\n";
	std::cout << "4) Add two graphs\n\n";
	std::cout << "5) Reset\n\n >";

	std::cin >> option;

	if (option == 1)
		print_add_graph_menu();
	else if (option == 2)
		choose_graph_for_info();
	else if (option == 3)
		choose_graph_for_deletion();
	else if (option == 4)
		reset_everything();
	else if (option == 5) 
		reset_everything();
			
	goto RETRY_CHOICE;
}

void print_add_graph_menu() {
	RETRY_ADD:
	CLEAR;
	std::string name;
	std::string type;
	
	std::cout << "\nGraph name: ";
	std::cin >> name;

	std::cout << "\nGraph data type: ";
	std::cin >> type;
	
	if (!type.compare("int")) {
		Graph<int> * a = new Graph<int>(name); std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else if (!type.compare("char")) {
		Graph<char> * a = new Graph<char>(name); std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else if (!type.compare("short")) {
		Graph<short> * a = new Graph<short>(name); std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else if (!type.compare("float")) {
		Graph<float> * a = new Graph<float>(name); std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else if (!type.compare("double")) {
		Graph<double> * a = new Graph<double>(name); std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else if (!type.compare("string")) {
		Graph<std::string> * a = new Graph<std::string>(name); 
		std::cin >> *a;
		graph_list.push_back(std::pair< void *, std::string >(a, a->get_type()));
		graph_name.push_back(name);
	}
	else 
		goto RETRY_ADD;
}

void choose_graph_for_info() {
	RETRY_GRAPH:
	CLEAR;
	if (!graph_list.empty()) {
		std::cout << "Choose graph: \n { ";
		std::vector<std::string>::iterator name = graph_name.begin();
		std::cout << *name; ++name;
		for (; name != graph_name.end(); ++name) {
			std::cout << ", " << *name;
		}
		std::cout << " }\n\n >";
	}
	else return;

	std::string choice;
	std::cin >> choice;

	std::vector<std::string>::iterator it = std::find(graph_name.begin(), graph_name.end(), choice);

	if (it != graph_name.end()) {
		int index = distance(graph_name.begin(), it);
		std::cout << "INDEX = " << index << std::endl;

		if (!graph_list[index].second.compare("i")){
			print_graph_data((Graph<int> *)graph_list[index].first);
		} else if (!graph_list[index].second.compare("c")) {
			print_graph_data((Graph<char> *)graph_list[index].first);
		} else if (!graph_list[index].second.compare("s")) {
			print_graph_data((Graph<short> *)graph_list[index].first);
		} else if (!graph_list[index].second.compare("f")) {
			print_graph_data((Graph<float> *)graph_list[index].first);
		} else if (!graph_list[index].second.compare("d")) {
			print_graph_data((Graph<double> *)graph_list[index].first);
		} else {
			print_graph_data((Graph<std::string> *)graph_list[index].first);
		}
	} else goto RETRY_GRAPH;
}

void choose_graph_for_deletion() {
	RETRY_DELETE:
	CLEAR;
	if (!graph_list.empty()) {
		std::cout << "Choose graph: \n { ";
		std::vector<std::string>::iterator name = graph_name.begin();
		std::cout << *name; ++name;
		for (; name != graph_name.end(); ++name) {
			std::cout << ", " << *name;
		}
		std::cout << " }\n\n >";
	}
	else return;

	std::string choice;
	std::cin >> choice;

	std::vector<std::string>::iterator it = std::find(graph_name.begin(), graph_name.end(), choice);

	if (it != graph_name.end()) {
		int index = distance(graph_name.begin(), it);
		std::cout << "INDEX = " << index << std::endl;
		delete graph_list[index].first;
		graph_list.erase(graph_list.begin() + index);
		graph_name.erase(graph_name.begin() + index);
	} else goto RETRY_DELETE;
}

template <class T>
void print_graph_data(Graph<T> * tmp) {
	CLEAR;
	RETRY:
	std::cout << "Graph: " << tmp->get_name() << std::endl << std::endl;
	std::cout << "1) Print graph\n";
	std::cout << "2) Print connected nodes matrix\n";
	std::cout << "3) Print strongly connected components\n";
	std::cout << "4) DFS\n";
	std::cout << "5) BFS\n";
	std::cout << "6) Add new edge\n";
	std::cout << "7) Go back\n >";

	T starting_node, edge_left, edge_right;
	int option; std::cin >> option;

	if (option == 1) {
		CLEAR;
		tmp->print_graph_incident_list();
		goto RETRY;
	} else if (option == 2) {
		CLEAR;
		tmp->print_connected_nodes_matrix();
		goto RETRY;
	} else if (option == 3) {
		CLEAR;
		tmp->print_strongly_connected_components();
		goto RETRY;
	} else if (option == 4) {
		std::cout << "Choose starting node for BFS:";
		tmp->print_visited_nodes();
		std::cout << " >";
		std::cin >> starting_node;
		CLEAR;
		tmp->DFS(starting_node);
		goto RETRY;
	} else if (option == 5) {
		std::cout << "Choose starting node for BFS:";
		tmp->print_visited_nodes();
		std::cout << " >";
		std::cin >> starting_node;
		CLEAR;
		tmp->BFS(starting_node);
		goto RETRY;
	} else if (option == 6) {
		std::cout << "Input new edge: ";
		std::cin >> edge_left >> edge_right;
		tmp->add_edge(std::pair<T, T>(edge_left, edge_right));
		CLEAR;
		goto RETRY;
	} else if (option == 7) {
		return;
	} 
}

void reset_everything() {
	std::vector< std::pair< void *, std::string > >::iterator it;
	for (it = graph_list.begin(); it != graph_list.end(); ++it) 
		delete it->first;
	graph_list.clear();
	graph_name.clear();
}
