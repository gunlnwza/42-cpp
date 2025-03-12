#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string target;

	public:
		PresidentialPardonForm(void);
		PresidentialPardonForm(const PresidentialPardonForm& form);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& form);
		~PresidentialPardonForm(void);

		PresidentialPardonForm(std::string target);

		static AForm* create(std::string target);

		virtual void	execute(Bureaucrat const & executor) const;

		std::string	getTarget(void) const;
};

#endif
