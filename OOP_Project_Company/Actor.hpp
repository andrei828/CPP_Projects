#ifndef _INCL_ACTOR
#define _INCL_ACTOR

#include "Dependencies.hpp"
#include "Personnel.hpp"

class Actor: virtual public Personnel {
protected:
	bool MainRole;
	uint PercentageBonus;

public:
	virtual uint get_salary(const Movie&);

	/* constructors */
	Actor(uint Id, std::string Name, uint Salary, bool MainRole, uint PercentageBonus = 0):
	 Personnel(Id, Name, Salary), MainRole(MainRole), PercentageBonus(PercentageBonus) {}
};

uint Actor::get_salary(const Movie&) {
	return 5;
}

#endif