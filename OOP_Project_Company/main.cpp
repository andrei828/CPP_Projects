#include "ManageData.hpp"

int main() {
	//operator>>(std::cin, manager);
	//operator<<(std::cout, manager);
	/*Movie * tmp = new Movie();
	Personnel * x = new ActorDirector(1, "Actor", 5, 10, false, 300);
	std::cout << x->get_salary(*tmp) << std::endl;
	delete tmp;*/

	Manager * manager = new Manager();

	manager->input_movies();
	manager->input_personnel();
	
	manager->print_movies();
	manager->print_personnel();
}