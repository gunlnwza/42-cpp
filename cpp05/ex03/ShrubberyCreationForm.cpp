#include "ShrubberyCreationForm.hpp"

#define REQUIRED_GRADE_SIGN 145
#define REQUIRED_GRADE_EXEC 137

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: AForm(target + "_shrubbery", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target(target)
{
	// std::cout << "ShrubberyCreationForm's Construtor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(void)
	: AForm("_shrubbery", REQUIRED_GRADE_SIGN, REQUIRED_GRADE_EXEC), target("")
{
	// std::cout << "ShrubberyCreationForm's Default Construtor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& form)
	: AForm(form), target(form.target)
{
	// std::cout << "ShrubberyCreationForm's Copy Construtor called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& form)
{
	// std::cout << "ShrubberyCreationForm's Copy Assignment Operator called" << std::endl;

	this->target = form.target;
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	// std::cout << "ShrubberyCreationForm's Destrutor called" << std::endl;
}

AForm* ShrubberyCreationForm::create(std::string target)
{
	return (new ShrubberyCreationForm(target));
}


void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);

	// plant some trees
	std::ifstream	infile("shrubbery_plan");
	std::ofstream	outfile((this->target + "_shrubbery").c_str());

	std::string		line;
	while (std::getline(infile, line))
		outfile << line << std::endl;

	infile.close();
	outfile.close();
}

std::string	ShrubberyCreationForm::getTarget(void) const
{
	return (this->target);
}
