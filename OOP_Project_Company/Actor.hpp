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
	Actor(uint Id, std::string Name, double Salary, bool MainRole = false, double PercentageBonus = 0):
	 Personnel(Id, Name, Salary), MainRole(MainRole), PercentageBonus(PercentageBonus) {}
};

double Actor::get_salary(Movie *) {
	return 5;
}

#endif