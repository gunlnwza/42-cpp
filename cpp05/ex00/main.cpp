#include "Bureaucrat.hpp"

int	main(void)
{
	// Orthodox Canonical Form methods
	// Bureaucrat	default1;
	// Bureaucrat	default2(default1);
	// Bureaucrat	default3;
	// default3 = default1;


	// construct with highest grade
	Bureaucrat	a("Alex", 1); 
	std::cout << a << std::endl;
	
	// construct lowest grade
	Bureaucrat	b("Bob", 150);
	std::cout << b << std::endl;


	// getName() and getGrade()
	std::cout << std::endl
		<< a.getName() << " is a Grade-" << a.getGrade() << " Bureaucrat!!!" << " Very cool!" << std::endl
		<< b.getName() << " is a Grade-" << b.getGrade() << " Bureaucrat!!!" << " Very cool too!" << std::endl
		<< std::endl;

	// decrementGrade()
	std::cout << "DEMOTING " << a.getName() << std::endl;
	a.decrementGrade();  
	std::cout << a << std::endl
		<< a.getName() << " got demoted!" << " Oh no!" << std::endl
		<< std::endl;

	// incrementGrade()
	std::cout << "PROMOTING " << a.getName() << std::endl;
	a.incrementGrade();
	std::cout << a << std::endl
		<< a.getName() << " got back into their original position again!" << " Hooray!" << std::endl
		<< std::endl;


	// construct with too high grade
	std::cout << "Bureaucrat c('Clara', 0);" << std::endl;
	// Bureaucrat	c("Clara", 0);  // will throw Bureaucrat::GradeTooHighException
	try
	{
		Bureaucrat	c("Clara", 0);
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot be a Grade-0 Bureaucrat! That is illegal!" << std::endl;
	}
	std::cout << std::endl;

	// construct with too low grade
	std::cout << "Bureaucrat d('Dolan', 151);" << std::endl;
	// Bureaucrat	d("Dolan", 151);  // will throw Bureaucrat::GradeTooLowException
	try
	{
		Bureaucrat	d("Dolan", 151);
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot be a Grade-151 Bureaucrat! That is illegal!" << std::endl;
	}
	std::cout << std::endl;

	// decrementing lowest grade
	std::cout << "DEMOTING " << b.getName() << std::endl;
	// b.decrementGrade();  // will throw Bureaucrat::GradeTooLowException
	try
	{
		b.decrementGrade();
	}
	catch (std::exception& e)
	{
		std::cout << "NO!!! You cannot go lower than that! That is illegal!" << std::endl;
	}
	std::cout << std::endl;

	// incrementing highest grade
	std::cout << "PROMOTING " << a.getName() << std::endl;
	// a.incrementGrade();  // will throw Bureaucrat::GradeTooHighException
	try
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
