#include "../RPN.hpp"

bool	is_operator(const std::string& str)
{
	return (str == "+" || str == "-" || str == "*" || str == "/");
}

bool	is_operator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}
