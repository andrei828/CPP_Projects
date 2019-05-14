#include "ManageData.hpp"

int main() {
	/*Movie * tmp = new Movie();
	Personnel * x = new ActorDirector(1, "Actor", 5, 10, false, 300);
	std::cout << x->get_salary(*tmp) << std::endl;
	delete tmp;*/

	Manager * manager = new Manager();

	operator>>(std::cin, manager);
	operator<<(std::cout, manager);
	// manage->input_movies();
	//manage->print_movies();
}