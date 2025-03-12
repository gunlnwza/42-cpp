#include "AForm.hpp"


void AForm::assertValidGrade(int grade)
{
	if (grade < 1)
		throw (AForm::GradeTooHighException());
	if (grade > 150)
		throw (AForm::GradeTooLowException());
}


AForm::AForm(void)
	: name(""), isSigned(false), gradeToSign(150), gradeToExecute(150)
{
}

AForm::AForm(const AForm& other)
	: name(other.name), isSigned(other.isSigned),
	gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& other)
{
	this->isSigned = other.getIsSigned();
	return (*this);
}

AForm::~AForm(void)
{
}


AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false),
	gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	AForm::assertValidGrade(gradeToSign);
	AForm::assertValidGrade(gradeToExecute);
}


std::string	AForm::getName(void) const
{
	return (this->name);
}

bool AForm::getIsSigned(void) const
{
	return (this->isSigned);
}

int	AForm::getGradeToSign(void) const
{
	return (this->gradeToSign);
}

int AForm::getGradeToExecute(void) const
{
	return (this->gradeToExecute);
}


void AForm::beSigned(Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->getGradeToSign())  // if bureaucrat's grade is too low, throw exception
		throw (AForm::GradeTooLowException());
	this->isSigned = true;
}

void AForm::execute(Bureaucrat const & executor) const
{
	if (!this->getIsSigned())
		throw (AForm::FormNotSignedException());
	if (executor.getGrade() > this->getGradeToExecute())
		throw (AForm::AForm::GradeTooLowException());
}


const char* AForm::GradeTooHighException::what() const throw()
{
	return ("(form): grade is too high");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return ("(form): grade is too low");
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return ("(form): the form has not been signed");
}

const char* AForm::FormNotExistException::what() const throw()
{
	return ("(form): the form type is not recognized");
}


std::ostream&	operator<<(std::ostream& os, const AForm& f)
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
