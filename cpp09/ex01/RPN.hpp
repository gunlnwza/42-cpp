#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <istream>
# include <string>
# include <stack>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN(void);

		void	evaluate(std::string expression);
};

#endif
