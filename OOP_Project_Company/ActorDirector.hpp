#ifndef _INCL_ACTOR_DIRECTOR
#define _INCL_ACTOR_DIRECTOR

#include "Dependencies.hpp"
#include "Director.hpp"
#include "Actor.hpp"

class ActorDirector: public Actor, public Director {
public:
	double get_salary(Movie *);

	/* constructors */
	ActorDirector(uint Id, std::string Name, double Salary, 
				  std::vector< std::pair< std::string, Movie * > >& Movies,
				  uint Bonus, uint MainRole = false, uint PercentageBonus = 0):
	 Personnel(Id, Name, Salary, Movies), Actor(Id, Name, Salary, Movies,
	 MainRole, PercentageBonus), Director(Id, Name, Salary, Movies, Bonus) {}
};

double ActorDirector::get_salary(Movie *) {

	double sum = 0;
	std::vector< std::pair< std::string, Movie * > >::iterator it;

	for (it = MovieDevelopmentList.begin(); it != MovieDevelopmentList.end(); ++it) 
		sum += (it->second->get_profit() * (Salary + 0.1) + Bonus); 

	return sum;
}

#endif