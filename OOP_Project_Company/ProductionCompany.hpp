#include "Dependencies.hpp"
#include <typeinfo>

template <class T>
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

template <class T>
void ProductionCompany<T>::add_movie(std::pair<uint, Movie *> tmp) {
	Movies.push_back(tmp);
}

template <class T>
void ProductionCompany<T>::add_personnel(Personnel * tmp) {
	Employees.push_back(tmp);
}

template <>
class ProductionCompany<unsigned> {
private:
	uint current_year;
	uint num_of_actors;
	std::vector< Personnel * > Employees; 
	std::vector< std::pair< uint, Movie * > > Movies;
public:
	ProductionCompany() {}
	unsigned main_role_actors() {
		unsigned total_actors = 0;
		for (auto employee: Employees) 
			//if (typeid(employee) == typeid(Actor*))
				total_actors++;
		return total_actors;
	}

	/* setters */
	void add_personnel(Personnel *);
	void add_movie(std::pair<uint, Movie *>);

	/* getters */
	std::vector< Personnel * >& get_personnel() { return Employees; }
	std::vector< std::pair< uint, Movie *> >& get_movies() { return Movies; }
};

void ProductionCompany<unsigned>::add_movie(std::pair<uint, Movie *> tmp) {
	Movies.push_back(tmp);
}

void ProductionCompany<unsigned>::add_personnel(Personnel * tmp) {
	Employees.push_back(tmp);
}