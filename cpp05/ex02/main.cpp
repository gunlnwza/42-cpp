#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

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

	Bureaucrat	boss("Boss", 1);
	Bureaucrat	senior_diplomat("Senior Galactic Diplomat", 5);
	Bureaucrat	junior_diplomat("Junior Galactic Diplomat", 25);
	Bureaucrat	senior_soldier("Senior Soldier", 45);
	Bureaucrat	junior_soldier("Junior Soldier", 72);
	Bureaucrat	senior_gardener("Senior Gardener", 137);
	Bureaucrat	junior_gardener("Junior Gardener", 145);
	Bureaucrat	crook("Crook", 150);

	std::cout << "[ The Prestigious Members of the cpp05/ex02 Council ]" << std::endl
		<< "- " << boss << std::endl
		<< "- " << senior_diplomat << std::endl
		<< "- " << junior_diplomat << std::endl
		<< "- " << senior_soldier << std::endl
		<< "- " << junior_soldier << std::endl
		<< "- " << senior_gardener << std::endl
		<< "- " << junior_gardener << std::endl
		<< "- " << crook << std::endl
		<< std::endl;
	
	ShrubberyCreationForm	shrubbery_form("42Bangkok");
	RobotomyRequestForm		robotomy_form("Bender");
	PresidentialPardonForm	pardon_form("Gun");


	std::cout << "[ The Different Types of Form at the cpp05/ex02 Council ]" << std::endl
		<< "- " << shrubbery_form << std::endl
		<< "- " << robotomy_form << std::endl
		<< "- " << pardon_form << std::endl
		<< std::endl;


	std::cout << "[ ShrubberyCreationForm ]" << std::endl;
	junior_gardener.signForm(shrubbery_form);
	senior_gardener.executeForm(shrubbery_form);

	std::cout << std::endl;

	std::cout << "[ RobotomyRequestForm ]" << std::endl;
	junior_soldier.signForm(robotomy_form);
	senior_soldier.executeForm(robotomy_form);

	std::cout << std::endl;

	std::cout << "[ PresidentialPardonForm ]" << std::endl;
	junior_diplomat.signForm(pardon_form);
	senior_diplomat.executeForm(pardon_form);

	std::cout << std::endl;


	std::cout << "[ Invalid Execution ]" << std::endl;
	ShrubberyCreationForm	other_shrubbery_form("Home");
	crook.executeForm(other_shrubbery_form);  // grade too low to execute unsigned form

	boss.signForm(other_shrubbery_form);
	crook.executeForm(other_shrubbery_form);  // grade too low to execute signed form


	// AForm abstract_form;  // AForm's objects cannot be instantiated

	return (0);
}
