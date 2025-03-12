#include "PresidentialPardonForm.hpp"

#define REQUIRED_GRADE_SIGN 25
#define REQUIRED_GRADE_EXEC 5

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: AForm(target + "_pardon", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target(target)
{
	// std::cout << "PresidentialPardonForm's Construtor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(void)
	: AForm("_pardon", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target("")
{
	// std::cout << "PresidentialPardonForm's Default Construtor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& form)
	: AForm(form), target(form.target)
{
	// std::cout << "PresidentialPardonForm's Copy Construtor called" << std::endl;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& form)
{
	// std::cout << "PresidentialPardonForm's Copy Assignment Operator called" << std::endl;

	this->target = form.target;
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	// std::cout << "PresidentialPardonForm's Destrutor called" << std::endl;
}

AForm* PresidentialPardonForm::create(std::string target)
{
	return (new PresidentialPardonForm(target));
}


void	PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);

	// pardoned by Zaphod Beeblebrox
	std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox" << std::endl;

}

std::string	PresidentialPardonForm::getTarget(void) const
{
	return (this->target);
}
