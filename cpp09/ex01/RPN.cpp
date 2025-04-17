#include "RPN.hpp"

RPN::RPN(void)
{}

RPN::RPN(const RPN& other)
{
	(void) other;
}

RPN& RPN::operator=(const RPN& other)
{
	(void) other;
	return (*this);
}

RPN::~RPN(void)
{}


std::string	get_token(const std::string& expression, size_t i);
void		process_token(const std::string& token, std::stack<ll>& stack);
void		show_result(std::stack<ll>& stack);

void	RPN::evaluate(const std::string& expression) const
{
	std::stack<ll>	stack;
	std::string		token;
	size_t			i;

	if (expression.length() == 0)
	{
		std::cout << "Input is empty" << std::endl;
		return ;
	}
	i = 0;
	while (i < expression.length())
	{
		if (std::isspace(expression[i]))
		{
			i++;
			continue ;
		}
		token = get_token(expression, i);
		process_token(token, stack);
		i += token.length();
	}
	show_result(stack);
}
