#ifndef _INCL_DIRECTOR
#define _INCL_DIRECTOR

#include "Dependencies.hpp"
#include "Personnel.hpp"

class Director: virtual public Personnel {
protected:
	double Bonus;

public:
	virtual double get_salary(Movie *);

	/* constructors */
	Director(uint Id, std::string Name, double Salary,
		std::vector< std::pair< std::string, Movie * > >& Movies, double Bonus):
	 Personnel(Id, Name, Salary, Movies), Bonus(Bonus) {}
};

double Director::get_salary(Movie *) {
	double sum = 0;
	std::vector< std::pair< std::string, Movie * > >::iterator it;

	for (it = MovieDevelopmentList.begin(); it != MovieDevelopmentList.end(); ++it) 
		sum += (it->second->get_profit() * Salary + Bonus); 

	return sum;
}

#endif