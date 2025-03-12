#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include "AForm.hpp"
# include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		std::string target;

	public:
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(const ShrubberyCreationForm& form);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& form);
		~ShrubberyCreationForm(void);

		ShrubberyCreationForm(std::string target);

		virtual void	execute(Bureaucrat const & executor) const;

		std::string	getTarget(void) const;
};

#endif
