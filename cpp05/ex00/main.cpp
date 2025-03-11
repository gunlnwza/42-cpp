#include "Bureaucrat.hpp"

int	main(void)
{
	// Orthodox Canonical Form methods
	// Bureaucrat	default1;
	// Bureaucrat	default2(default1);
	// Bureaucrat	default3;


	Bureaucrat	a("Alex", 1);  // construct with highest grade
	std::cout << a << std::endl;
	
	Bureaucrat	b("Bob", 150);  // construct lowest grade
	std::cout << b << std::endl;

	std::cout << std::endl  // getName() and getGrade()
		<< a.getName() << " is a Grade-" << a.getGrade() << " Bureaucrat!!!" << " Very cool!" << std::endl
		<< b.getName() << " is a Grade-" << b.getGrade() << " Bureaucrat!!!" << " Very cool too!" << std::endl
		<< std::endl;


	std::cout << "DEMOTING " << a.getName() << std::endl;
	a.decrementGrade();  // decrementGrade()
	std::cout << a << std::endl
		<< a.getName() << " got demoted!" << " Oh no!" << std::endl
		<< std::endl;

	std::cout << "PROMOTING " << a.getName() << std::endl;
	a.incrementGrade();  // incrementGrade()
	std::cout << a << std::endl
		<< a.getName() << " got back into their original position again!" << " Hooray!" << std::endl
		<< std::endl;


	std::cout << "Bureaucrat c('Clara', 0);" << std::endl;
	// Bureaucrat	c("Clara", 0);  // will throw Bureaucrat::GradeTooHighException
	try  // must use try-catch instead
	{
		Bureaucrat	c("Clara", 0);
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot be a Grade-0 Bureaucrat! That is illegal!" << std::endl;
	}
	std::cout << std::endl;


	std::cout << "Bureaucrat d('Dolan', 151);" << std::endl;
	// Bureaucrat	d("Dolan", 151);  // will throw Bureaucrat::GradeTooLowException
	try  // must use try-catch instead
	{
		Bureaucrat	d("Dolan", 151);
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot be a Grade-151 Bureaucrat! That is illegal!" << std::endl;
	}
	std::cout << std::endl;


	std::cout << "DEMOTING " << b.getName() << std::endl;
	// b.decrementGrade();  // will throw Bureaucrat::GradeTooLowException
	try  // must use try-catch instead
	{
		b.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot go lower than that! That is illegal!" << std::endl;
	}
	std::cout << std::endl;


	std::cout << "PROMOTING " << a.getName() << std::endl;
	// a.incrementGrade();  // will throw Bureaucrat::GradeTooHighException
	try  // must use try-catch instead
	{
		a.incrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot go higher than that! That is illegal!" << std::endl;
	}
	std::cout << std::endl;


	return (0);
}
