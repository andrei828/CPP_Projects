#ifndef _INCL_ACTOR
#define _INCL_ACTOR

#include "Dependencies.hpp"
#include "Personnel.hpp"

class Actor: virtual public Personnel {
protected:
	bool MainRole;
	double PercentageBonus;

public:
	virtual double get_salary(Movie *);

	/* constructors */
	Actor(uint Id, std::string Name, double Salary, std::vector< std::pair< std::string, Movie * > >& Movies,
		bool MainRole = false, double PercentageBonus = 0):
	 Personnel(Id, Name, Salary, Movies), MainRole(MainRole), PercentageBonus(PercentageBonus) {}
};

double Actor::get_salary(Movie *) {
	double sum = 0;
	std::vector< std::pair< std::string, Movie * > >::iterator it;

	for (it = MovieDevelopmentList.begin(); it != MovieDevelopmentList.end(); ++it) 
		sum += (it->second->get_profit() * (Salary + 0.1)); 

	return sum;
}

#endif