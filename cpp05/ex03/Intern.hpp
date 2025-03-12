#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class Intern
{
	public:
		Intern(void);
		Intern(Intern const & other);
		Intern& operator=(Intern const & other);
		~Intern(void);

		AForm*	makeForm(std::string name, std::string target);
};

#endif
