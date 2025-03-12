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
	: name(other.name), isSigned(other.isSigned),
	gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
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
	: name(name), isSigned(false),
	gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
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
	if (bureaucrat.getGrade() > this->getGradeToSign())  // if bureaucrat's grade is too low, throw exception
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
	os << f.getName() << ", form (";
	if (f.getIsSigned())
		os << "SIGNED";
	else
		os << "NOT SIGNED";
	os << ", lowest can sign: " << f.getGradeToSign()
		<< ", lowest can execute: " << f.getGradeToExecute() << ")";
	return (os);
}
