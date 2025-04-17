#include "../RPN.hpp"

bool	is_operator(const std::string& str);

void	process_operator(std::string op, std::stack<ll>& stack)
{
	ll	num_a;
	ll	num_b;
	ll	value;

	if (stack.empty())
		throw (std::runtime_error("Error: no number for operator '" + op + "'"));
	num_b = stack.top();
	stack.pop();
	if (stack.empty())
		throw (std::runtime_error("Error: not enough number for operator '" + op + "'"));
	num_a = stack.top();
	stack.pop();
	if (op == "+")
		value = num_a + num_b;
	else if (op == "-")
		value = num_a - num_b;
	else if (op == "*")
		value = num_a * num_b;
	else if (op == "/")
		value = num_a / num_b;
	stack.push(value);
}

void	process_number(const std::string& token, std::stack<ll>& stack)
{
	char	*ptr;
	ll		value;

	errno = 0;
	value = std::strtoll(token.c_str(), &ptr, 10);
	if (errno == ERANGE)
	{
		if (value < 0)
			throw (std::runtime_error("Error: string to number conversion underflowed"));
		else
			throw (std::runtime_error("Error: string to number conversion overflowed"));
	}
	stack.push(value);
}

void	process_token(const std::string& token, std::stack<ll>& stack)
{
	if (is_operator(token))
		process_operator(token, stack);
	else
		process_number(token, stack);
}
