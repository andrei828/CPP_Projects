#ifndef _INCL_PERSONNEL
#define _INCL_PERSONNEL

#include "Dependencies.hpp"
#include "Movie.hpp"

class Movie;

class Personnel {
protected:
	uint Id;
	double Salary;
	std::string Name;
	std::vector< std::pair< std::string, Movie * > > MovieDevelopmentList;
public:
	virtual double get_salary(Movie *);
	
	/* constructors */
	Personnel(uint Id, std::string Name, double Salary): 
	 Id(Id), Name(Name), Salary(Salary) {}

};

double Personnel::get_salary(Movie *) {

	return 15;
}
#endif