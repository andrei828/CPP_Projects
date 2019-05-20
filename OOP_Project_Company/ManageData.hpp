#include <fstream>
#include <cstring>
#include "Movie.hpp"
#include "Dependencies.hpp"
#include "ProductionCompany.hpp"

#include "Actor.hpp"
#include "Director.hpp"
#include "Personnel.hpp"
#include "ActorDirector.hpp"

#define INPUT_MOVIES_FILE "mock_Movies.txt"
#define INPUT_PERSONNEL_FILE "mock_Personnel.txt"

class Manager {
private:
	ProductionCompany<unsigned> * productionCompany;

public:
	Manager() {
		productionCompany = new ProductionCompany<unsigned>();
	}



	void input_movies();
	void print_movies();
	void input_personnel();
	void print_personnel();

	uint get_number_of_movies() { return (uint) productionCompany->get_movies().size(); }
	Movie *& get_movie_at_index(uint index) { return productionCompany->get_movies()[index].second; }
	std::vector<Personnel *>& get_employees() { return productionCompany->get_personnel(); }

	friend std::istream& operator >> (std::istream&  in, Manager * manager);
	friend std::ostream& operator << (std::ostream& out, const Manager * manager);
};

std::istream& operator >> (std::istream& in, Manager * manager) {
	std::ifstream fin(INPUT_MOVIES_FILE, std::ifstream::in);

	std::string name, category;
	uint year, duration, profit, number_of_movies;
	fin >> number_of_movies; fin.ignore();

	for (int i = 0; i < number_of_movies; i++) {
		std::getline(fin, name);
		fin >> year; fin.ignore();

		std::getline(fin, category);
		fin >> duration; fin.ignore();
		fin >> profit; fin.ignore();

		manager->productionCompany->add_movie(std::make_pair(year, 
			(new Movie(name, category, duration, profit))));
	}
	return in;
}

std::ostream& operator << (std::ostream& out, const Manager * manager) {
	std::vector< std::pair<uint, Movie *> > Movies = manager->productionCompany->get_movies();

	for (auto movie: Movies) 
		out << movie.first << std::endl;
	
	return out;
}

void Manager::print_movies() {
	std::vector< std::pair< uint, Movie *> > Movies = productionCompany->get_movies();

	int k = 1;
	for (auto movie: Movies) 
		std::cout << k++ << ") " << movie.second->get_name() << std::endl;
}

void Manager::print_personnel() {
	std::vector< Personnel * > Employees = productionCompany->get_personnel();

	for (auto personnel: Employees)
		std::cout << personnel->get_name() << std::endl;
}

void Manager::input_personnel() {
	double bonus, percentage_bonus;
	bool main_role, _actor, _director;
	std::string name, role, movie_name;
	std::string actor = "Actor", director = "Director";
	uint id, salary, number_of_personnel, number_of_movies;
	
	std::ifstream fin(INPUT_PERSONNEL_FILE, std::ifstream::in);
	std::vector< std::pair< uint, Movie *> >::iterator movie_it;
	std::vector< std::pair< std::string, Movie * > > movie_development_list;
	std::vector< std::pair< uint, Movie *> > Movies = productionCompany->get_movies();
	
	fin >> number_of_personnel; fin.ignore();	
	for (int i = 0; i < number_of_personnel; i++) {
		movie_development_list = std::vector< std::pair< std::string, Movie * > >();
		fin >> id; fin.ignore();
		std::getline(fin, name);

		_actor = _director = false;

		fin >> salary; fin.ignore();
		std::getline(fin, role);

		if (role.find(actor) != std::string::npos) 
		{ fin >> main_role; fin.ignore(); _actor = true; }

		if (role.find(director) != std::string::npos)
		{ fin >> bonus; fin.ignore(); _director = true; }

		fin >> number_of_movies; fin.ignore();

		for (int j = 0; j < number_of_movies; j++) {
			std::getline(fin, movie_name);

			for (movie_it = Movies.begin(); movie_it != Movies.end(); ++movie_it)
				if (!movie_it->second->get_name().compare(movie_name)) 
					movie_development_list.push_back(std::make_pair(
						movie_it->second->get_name(), movie_it->second));
		}

		Personnel * _personnel;
		if (_actor && _director) { 
			_personnel = new ActorDirector(id, name, salary, movie_development_list,
				bonus, main_role, percentage_bonus);

			productionCompany->add_personnel(_personnel);
		}
		else if (_actor) {
			_personnel = new Actor(id, name, salary, movie_development_list, 
				main_role, percentage_bonus);

			productionCompany->add_personnel(_personnel);
		}
		else if (_director){
			_personnel = new Director(id, name, salary, 
				movie_development_list, bonus);

			productionCompany->add_personnel(_personnel);
		}
		
		else {
			_personnel = new Personnel(id, name, salary, 
				movie_development_list);

			productionCompany->add_personnel(_personnel);
		}

		for (auto movie: movie_development_list)
			movie.second->add_employee(_personnel);
	}
}

void Manager::input_movies() {
	std::ifstream fin(INPUT_MOVIES_FILE, std::ifstream::in);

	std::string name, category;
	uint year, duration, profit, number_of_movies;
	fin >> number_of_movies; fin.ignore();

	for (int i = 0; i < number_of_movies; i++) {
		std::getline(fin, name);
		fin >> year; fin.ignore();

		std::getline(fin, category);
		fin >> duration; fin.ignore();
		fin >> profit; fin.ignore();

		productionCompany->add_movie(std::make_pair(year, 
			(new Movie(name, category, duration, profit))));
	}

}