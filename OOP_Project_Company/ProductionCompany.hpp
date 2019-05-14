#include "Dependencies.hpp"

class ProductionCompany {
private:
	uint current_year;
	uint num_of_actors;
	std::vector< Personnel * > Employees; 
	std::vector< std::pair< uint, Movie * > > Movies;
public:
	ProductionCompany() {}

	/* setters */
	void add_personnel(Personnel *);
	void add_movie(std::pair<uint, Movie *>);

	/* getters */
	std::vector< Personnel * >& get_personnel() { return Employees; }
	std::vector< std::pair< uint, Movie *> >& get_movies() { return Movies; }
};

void ProductionCompany::add_movie(std::pair<uint, Movie *> tmp) {
	Movies.push_back(tmp);
}

void ProductionCompany::add_personnel(Personnel * tmp) {
	Employees.push_back(tmp);
}