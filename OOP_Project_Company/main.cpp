#include "ManageData.hpp"

Manager * manager;

void load_data();
void main_menu();
void movie_menu(Movie * movie);

int main() {
	//operator>>(std::cin, manager);
	//operator<<(std::cout, manager);
	/*Movie * tmp = new Movie();
	Personnel * x = new ActorDirector(1, "Actor", 5, 10, false, 300);
	std::cout << x->get_salary(*tmp) << std::endl;
	delete tmp;*/


	load_data();
	main_menu();
	


	//manager->print_personnel();
}

void movie_menu(Movie * movie) {
	uint choice;
	std::system("clear");
	std::cout << movie->get_name() << std::endl;
	std::cout << movie->get_category() << ", " << movie->get_duration() << " min" << std::endl;
	std::cout << "Profit: $" << movie->get_profit() <<  std::endl;
	std::cout << "1) Employers list\n" << "2) See trailer\n";
	std::cin >> choice;

	if (choice == 1) {

	}
}

void main_menu() {
	uint choice;
	std::system("clear");
	manager->print_movies();
	std::cin >> choice;

	if (choice <= manager->get_number_of_movies()) {
		movie_menu(manager->get_movie_at_index(choice - 1));
		return;
	}

	main_menu();
		
}

void load_data() {
	manager = new Manager();

	manager->input_movies();
	manager->input_personnel();
}