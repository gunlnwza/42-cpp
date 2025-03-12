#include "RobotomyRequestForm.hpp"

#define REQUIRED_GRADE_SIGN 72
#define REQUIRED_GRADE_EXEC 45

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: AForm(target + "_robotomy", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target(target)
{
	// std::cout << "RobotomyRequestForm's Construtor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(void)
	: AForm("_robotomy", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target("")
{
	// std::cout << "RobotomyRequestForm's Default Construtor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& form)
	: AForm(form), target(form.target)
{
	// std::cout << "RobotomyRequestForm's Copy Construtor called" << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& form)
{
	// std::cout << "RobotomyRequestForm's Copy Assignment Operator called" << std::endl;

	this->target = form.target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	// std::cout << "RobotomyRequestForm's Destrutor called" << std::endl;
}

AForm* RobotomyRequestForm::create(std::string target)
{
	return (new RobotomyRequestForm(target));
}


void	RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);

	// tatakae, tatakae!!!
	std::srand(std::time(NULL));
	int	random_num = std::rand() % 2;
	if (random_num == 0)
	{
		std::cout << "\033[30mWHIRRR...  \033[33mSCREEEKKK!  \033[31;1mBOOM!!!\033[0m" << std::endl;
		std::cout << this->getTarget() << " has been robotomized" << std::endl;
	}
	else
	{
		std::cerr << "Robotomy failed. " << this->getTarget() << " got away..." << std::endl;
	}
}

std::string	RobotomyRequestForm::getTarget(void) const
{
	return (this->target);
}
