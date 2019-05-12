#include <fstream>
#include "Movie.hpp"
#include "Dependencies.hpp"
#include "ProductionCompany.hpp"

#include "Actor.hpp"
#include "Director.hpp"
#include "Personnel.hpp"
#include "ActorDirector.hpp"

#define INPUT_MOVIES_FILE "mock_Movies.txt"

class Manager {
private:
	ProductionCompany * productionCompany;

public:
	Manager() {
		productionCompany = new ProductionCompany();
	}

	void input_movies();
	void print_movies();
};

void Manager::print_movies() {
	std::vector< std::pair< uint, Movie > > Movies = productionCompany->get_movies();

	for (auto& movie: Movies) {
		std::cout << movie.first << std::endl;
	}
}

void Manager::input_movies() {
	std::ifstream fin(INPUT_MOVIES_FILE, std::ifstream::in);

	uint year, duration, number_of_movies;
	std::string name, category;
	fin >> number_of_movies; fin.ignore();

	for (int i = 0; i < number_of_movies; i++) {
		std::getline(fin, name);
		fin >> year; fin.ignore();

		std::getline(fin, category);
		fin >> duration; fin.ignore();

		productionCompany->add_movie(std::make_pair(year, 
			Movie(name, category, duration)));
	}

}