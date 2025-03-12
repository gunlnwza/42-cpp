#include "Intern.hpp"

Intern::Intern(void) {}

Intern::Intern(Intern const & other)
{
	(void) other;
}

Intern& Intern::operator=(Intern const & other)
{
	(void) other;
	return (*this);
}

Intern::~Intern(void) {}


std::string ft_strtrim(std::string str, std::string set)
{
    size_t start = str.find_first_not_of(set);
    if (start == std::string::npos)
        return ("");
    size_t end = str.find_last_not_of(set);
    return (str.substr(start, end - start + 1));
}

std::string	ft_strlower(std::string str)
{
	std::string new_str;
	int			i;

	i = 0;
	while (str[i])
	{
		new_str += std::tolower(str[i]);
		i++;
	}
	return (new_str);
}

AForm*	Intern::makeForm(std::string name, std::string target)
{
	int	len = 3;
	std::string	form_names[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm*	(*form_creates[])(std::string) = {
		&ShrubberyCreationForm::create,
		&RobotomyRequestForm::create,
		&PresidentialPardonForm::create
	};

	name = ft_strlower(ft_strtrim(name, " "));
	for (int i = 0; i < len; i++)
	{
		if (name == form_names[i])
			return (form_creates[i](target));
	}

	throw (AForm::FormNotExistException());
}
