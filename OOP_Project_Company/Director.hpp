#ifndef _INCL_DIRECTOR
#define _INCL_DIRECTOR

#include "Dependencies.hpp"
#include "Personnel.hpp"

class Director: virtual public Personnel {
protected:
	uint Bonus;

public:
	virtual uint get_salary(const Movie&);

	/* constructors */
	Director(uint Id, std::string Name, uint Salary, uint Bonus):
	 Personnel(Id, Name, Salary), Bonus(Bonus) {}
};

uint Director::get_salary(const Movie&) {

	return 10;
}

#endif