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
				  uint Bonus, uint MainRole = false, uint PercentageBonus = 0):
	 Personnel(Id, Name, Salary), Actor(Id, Name, Salary,
	 MainRole, PercentageBonus), Director(Id, Name, Salary, Bonus) {}
};

double ActorDirector::get_salary(Movie *) {

	return 20;
}

#endif