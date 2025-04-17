#include <iostream>

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong argument format" << std::endl
				  << "Usage: ./RPN <expression>" << std::endl
				  << "(Don't forget to put quotes around the expression!)" << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		RPN	calculator;
		calculator.evaluate(argv[1]);
		return (EXIT_SUCCESS);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
}
