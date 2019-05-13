#include <fstream>
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
	ProductionCompany * productionCompany;

public:
	Manager() {
		productionCompany = new ProductionCompany();
	}

	void input_movies();
	void print_movies();
	void input_personnel();
	void print_personnel();
};

void Manager::print_movies() {
	std::vector< std::pair< uint, Movie *> > Movies = productionCompany->get_movies();

	for (auto movie: Movies) {
		std::cout << movie.first << std::endl;
	}
}

void Manager::input_personnel() {
	std::ifstream fin(INPUT_PERSONNEL_FILE, std::ifstream::in);


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