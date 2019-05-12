#ifndef _INCL_ACTOR_DIRECTOR
#define _INCL_ACTOR_DIRECTOR

#include "Dependencies.hpp"
#include "Director.hpp"
#include "Actor.hpp"

class ActorDirector: public Actor, public Director {
public:
	uint get_salary(const Movie&);

	/* constructors */
	ActorDirector(uint Id, std::string Name, uint Salary, 
				  uint PercentageBonus, uint MainRole, uint Bonus):
	 Personnel(Id, Name, Salary), Actor(Id, Name, Salary,
	 MainRole, PercentageBonus), Director(Id, Name, Salary, Bonus) {}
};

uint ActorDirector::get_salary(const Movie&) {

	return 20;
}

#endif