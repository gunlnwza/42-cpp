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


void	RPN::evaluate(std::string expression)
{
	std::stack<int> stack;

	std::string::iterator it = expression.begin();
	std::string::iterator it_end = expression.end();
	for (; it != it_end; ++it)
	{
		char c = *it;
		if (c == ' ')
			continue ;

		if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			int b = stack.top();
			stack.pop();
			// std::cout << "Pop " << b << std::endl;
			int a = stack.top();
			stack.pop();
			// std::cout << "Pop " << a << std::endl;
			int value = 0;

			if (c == '+')
			{
				value = a + b;
			}
			else if (c == '-')
			{
				value = a - b;
			}
			else if (c == '*')
			{
				value = a * b;
			}
			else if (c == '/')
			{
				value = a / b;
			}
			// std::cout << a << " " << c << " " << b << " = " << value << std::endl;
			stack.push(value);
		}
		else if (std::isdigit(c))
		{
			int value = static_cast<int>(c - '0');
			// std::cout << "Push " << value << std::endl;
			stack.push(value);
		}
		else
			throw (std::out_of_range("Unknown char"));
	}

	std::cout << "Result is " << stack.top() << std::endl;
}
