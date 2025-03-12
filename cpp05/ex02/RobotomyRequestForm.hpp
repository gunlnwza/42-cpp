#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include "AForm.hpp"
# include <ctime>
# include <cstdlib>

class RobotomyRequestForm : public AForm
{
	private:
		std::string target;

	public:
		RobotomyRequestForm(void);
		RobotomyRequestForm(const RobotomyRequestForm& form);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& form);
		~RobotomyRequestForm(void);

		RobotomyRequestForm(std::string target);

		virtual void	execute(Bureaucrat const & executor) const;

		std::string	getTarget(void) const;
};

#endif
