#ifndef _INCL_MOVIE
#define _INCL_MOVIE

#include "Dependencies.hpp"
#include "Personnel.hpp"

class Movie {
private:
	std::string Name;
	std::string Category;
	uint Duration; /* in minutes */
	std::vector<Personnel *> Employees;
public:
	/* getters */
	std::string get_name() { return Name; }
	std::string get_category() { return Category; }
	uint get_duration() { return Duration; } /* in minutes */
	std::vector<Personnel *> get_Employees() { return Employees; }

	/* setters */ 
	void set_name(std::string Name) { this->Name = Name; }
	void set_duration(uint Duration) { this->Duration = Duration; }
	void set_category(std::string Category) { this->Category = Category; }
	void add_employee(Personnel * personnel) { Employees.push_back(personnel); }

	/* constructors */
	Movie() {}
	Movie(const Movie &) {} 
	Movie(std::string, std::string, uint, std::vector<Personnel *>&);
	Movie(std::string Name, std::string Category, uint Duration):
	 Name(Name), Category(Category), Duration(Duration) {}
};

#endif