#ifndef _INCL_PERSONNEL
#define _INCL_PERSONNEL

#include "Dependencies.hpp"
#include "Movie.hpp"

class Movie;

class Personnel {
protected:
	uint Id;
	uint Salary;
	std::string Name;
	std::vector< std::pair< std::string, Movie > > MovieDevelopmentList;
public:
	virtual uint get_salary(const Movie&);
	
	/* constructors */
	Personnel(uint Id, std::string Name, uint Salary): 
	 Id(Id), Name(Name), Salary(Salary) {}

};

uint Personnel::get_salary(const Movie&) {

	return 15;
}
#endif