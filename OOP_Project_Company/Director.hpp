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
	Director(uint Id, std::string Name, double Salary, double Bonus):
	 Personnel(Id, Name, Salary), Bonus(Bonus) {}
};

double Director::get_salary(Movie *) {

	return 10;
}

#endif