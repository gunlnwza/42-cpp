#include "Form.hpp"


void Form::assertValidGrade(int grade)
{
	if (grade < 1)
		throw (Form::GradeTooHighException());
	if (grade > 150)
		throw (Form::GradeTooLowException());
}


Form::Form(void)
	: name(""), isSigned(false), gradeToSign(150), gradeToExecute(150)
{
}

Form::Form(const Form& other)
	: name(other.getName()), isSigned(other.getIsSigned()),
	gradeToSign(other.getGradeToSign()),
	gradeToExecute(other.getGradeToExecute())
{
}

Form& Form::operator=(const Form& other)
{
	this->isSigned = other.getIsSigned();
	return (*this);
}

Form::~Form(void)
{
}


Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: name(name), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	Form::assertValidGrade(gradeToSign);
	Form::assertValidGrade(gradeToExecute);
}


std::string	Form::getName(void) const
{
	return (this->name);
}

bool Form::getIsSigned(void) const
{
	return (this->isSigned);
}

int	Form::getGradeToSign(void) const
{
	return (this->gradeToSign);
}

int Form::getGradeToExecute(void) const
{
	return (this->gradeToExecute);
}


void Form::beSigned(Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->getGradeToSign())
		throw (Form::GradeTooLowException());
	this->isSigned = true;
}


const char* Form::GradeTooHighException::what() const throw()
{
	return ("(form): grade is too high");
}

const char* Form::GradeTooLowException::what() const throw()
{
	return ("(form): grade is too low");
}


std::ostream&	operator<<(std::ostream& os, const Form& f)
{
	os << f.getName() << ", form";

	if (f.getIsSigned())
		os << " (signed)";
	else
		os << " (not signed)";
	
	os << "require grade " << f.getGradeToSign() << " to sign, "
		<< "require grade " << f.getGradeToExecute() << " to execute";

	return (os);
}
