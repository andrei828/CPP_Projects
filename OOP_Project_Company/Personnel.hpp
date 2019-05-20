#ifndef _INCL_PERSONNEL
#define _INCL_PERSONNEL

#include "Dependencies.hpp"

class Movie;

class Personnel {
protected:
	uint Id;
	double Salary;
	std::string Name;
	std::vector< std::pair< std::string, Movie * > > MovieDevelopmentList;
public:
	virtual double get_salary();
	
	/* constructors */
	Personnel(uint Id, std::string Name, double Salary, 
		std::vector< std::pair< std::string, Movie * > >& Movies): 
	 Id(Id), Name(Name), Salary(Salary), MovieDevelopmentList(Movies) {}

	/* getters */
	std::string get_name() { return Name; }
	std::vector< std::pair< std::string, Movie * > > get_movies() 
	{ return MovieDevelopmentList; }
	Movie * get_movie_at_index(int index) { return MovieDevelopmentList[index].second; }
};

double Personnel::get_salary() {

	double sum = 0;
	std::vector< std::pair< std::string, Movie * > >::iterator it;

	for (it = MovieDevelopmentList.begin(); it != MovieDevelopmentList.end(); ++it) 
		sum += (it->second->get_profit() * Salary); 

	return sum;
}

#endif