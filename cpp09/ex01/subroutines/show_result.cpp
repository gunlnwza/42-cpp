#include "../RPN.hpp"

std::string	get_stack_string(std::stack<ll> stack)
{
	std::stack<ll>		temp;
	std::stringstream	ss;

	while (!stack.empty())
	{
		temp.push(stack.top());
		stack.pop();
	}
	ss << "[";
	while (!temp.empty())
	{
		ss << temp.top();
		temp.pop();
		if (!temp.empty())
			ss << ",";
	}
	return (ss.str());
}

void	show_result(std::stack<ll>& stack)
{
	std::string	stack_string;
	ll			value;

	stack_string = get_stack_string(stack);
	value = stack.top();
	stack.pop();
	if (!stack.empty())
		throw (std::runtime_error("Error: calculation is unfinished ( stack = " + stack_string + " )"));
	std::cout << "Result is " << value << std::endl;
}
