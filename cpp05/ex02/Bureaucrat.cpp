#include "Bureaucrat.hpp"


void	Bureaucrat::assertValidGrade(int grade)
{
	if (grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	if (grade > 150)
		throw (Bureaucrat::GradeTooLowException());
}


Bureaucrat::Bureaucrat(void)
	: name(""), grade(150)
{
	// std::cout << "Bureaucrat's Default Constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: name(other.name), grade(other.grade)
{
	// std::cout << "Bureaucrat's Copy Constructor called" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &other)
{
	// std::cout << "Bureaucrat's Copy Assignment Operator called" << std::endl;

	// this->name is immutable, so it is kept as-is
	this->grade = other.grade;
	return (*this);
}

Bureaucrat::~Bureaucrat(void)
{
	// std::cout << "Bureaucrat's Destructor called" << std::endl;
}


Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: name(name), grade(grade)
{
	assertValidGrade(grade);
}


std::string	Bureaucrat::getName(void) const
{
	return (this->name);
}

int	Bureaucrat::getGrade(void) const
{
	return (this->grade);
}


void	Bureaucrat::incrementGrade(void)
{
	int	new_grade;

	new_grade = this->grade - 1;
	assertValidGrade(new_grade);
	grade = new_grade;
}

void	Bureaucrat::decrementGrade(void)
{
	int	new_grade;

	new_grade = this->grade + 1;
	assertValidGrade(new_grade);
	grade = new_grade;
}


void	Bureaucrat::signForm(AForm& form)
{
	try
	{
		form.beSigned(*this);

		std::cout << this->getName() << " signed " << form.getName() << std::endl;
	}
	catch (AForm::GradeTooLowException& e)
	{
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because their grade is too low" << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm const & form)
{
	try
	{
		form.execute(*this);
		
		std::cout << this->getName() << " executed " << form.getName() << std::endl;
	}
	catch (AForm::FormNotSignedException & e)
	{
		std::cout << this->getName() << " couldn't executed " << form.getName() << " because the form is not signed" << std::endl;
	}
	catch (AForm::GradeTooLowException & e)
	{
		std::cout << this->getName() << " couldn't executed " << form.getName() << " because their grade is too low" << std::endl;
	}
}


const char*	Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("bureaucrat's grade is too high");
}

const char*	Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("bureaucrat's grade is too low");
}


std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade();
	return (os);
}
