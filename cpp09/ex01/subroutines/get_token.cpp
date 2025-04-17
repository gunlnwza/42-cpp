#include "../RPN.hpp"

bool	is_operator(char c);

std::string	get_token(const std::string& expression, size_t i)
{
	std::stringstream	ss;

	if (is_operator(expression[i]))
		ss << expression[i];
	else
	{
		while (i < expression.length())
		{
			if (std::isspace(expression[i]) || is_operator(expression[i]))
				break ;
			if (!std::isdigit(expression[i]))
				throw (std::runtime_error("Error: not-a-number is presented in the input"));
			ss << expression[i];
			i++;
		}
	}
	return (ss.str());
}
