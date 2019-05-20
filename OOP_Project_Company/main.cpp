#include "ManageData.hpp"

#define Google_URL "open /Applications/Safari.app/ \"http://www.google.com/search?q="

Manager * manager;

void load_data();
void main_menu();
void movie_menu(Movie * movie);
void personnel_menu(Personnel * personnel);

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

void personnel_menu(Personnel * personnel) {
	std::system("clear");
	std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	std::cout << personnel->get_name() << std::endl;
	std::cout << '$' << (double) personnel->get_salary() << std::endl;
	std::vector< std::pair< std::string, Movie * > > Movies = personnel->get_movies();
	std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

	int i = 1;
	for (auto movie: Movies) {
		std::cout << i++ << ") "<< movie.first << std::endl;
	}
	int choice;
	std::cin >> choice;
	if (choice == 0) main_menu();

	movie_menu(personnel->get_movie_at_index(choice - 1));
}

void movie_menu(Movie * movie) {
	uint choice;
	std::system("clear");
	std::cout << "*********************************\n";
	std::cout << movie->get_name() << std::endl;
	std::cout << movie->get_category() << ", " << movie->get_duration() << " min" << std::endl;
	std::cout << "Profit: $" << movie->get_profit() <<  std::endl;
	std::cout << "*********************************\n";
	std::cout << "1) Employers list\n" << "2) See trailer\n";
	std::cin >> choice;
	
	if (choice == 0) main_menu();
	else if (choice == 1) {
		std::vector< Personnel * >& employees = movie->get_employees();
		std::system("clear");
		int i = 1;
		if (employees.size() == 0) std::cout << "No personnel here :(\n";
		for (auto employee: employees) {
			std::cout << i++ << ") " << employee->get_name() << std::endl;
		}

		int choice2;
		std::cin >> choice2;
		if (choice2 == 0) main_menu();
		personnel_menu(employees[choice2 - 1]);

	}
	else if (choice == 2){
		std::cout << "Open url in Safari\n";
		char * command = new char[200];
		strcpy(command, Google_URL);
		strcat(command, movie->get_name().c_str());
		command = strcat(command, " trailer\"");
		std::system(command);
		main_menu();
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