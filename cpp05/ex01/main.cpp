#include "Bureaucrat.hpp"

void	ex00_test(void)
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
}

int	main(void)
{
	// ex00_test();

	Bureaucrat	ben("Ben", 10);
	Form		form_42("The 42 Form", 42, 42);
	Form		form_1("The Number One Form", 1, 10);

	std::cout << ben << std::endl
		<< std::endl
		<< form_42 << std::endl
		<< form_1 << std::endl
		<< std::endl;

	ben.signForm(form_42);  // can sign
	ben.signForm(form_1);  // cannot sign
	std::cout << std::endl;

	std::cout << form_42 << std::endl
		<< form_1 << std::endl
		<< std::endl;

	std::cout << "Trying to create invalid forms" << std::endl;
	try {
		Form	a("Too High Form", 0, 42);
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Form	b("Too High Form", 42, 0);
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Form	c("Too Low Form", 151, 42);
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Form	d("Too Low Form", 42, 151);
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	return (0);
}
