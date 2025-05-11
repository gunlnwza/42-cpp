#include <iostream>

#include "RPN.hpp"

// Containers used: std::stack, std::queue

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong argument format" << std::endl
				  << "Usage: ./RPN <expression>" << std::endl
				  << "(Don't forget to put quotes around the expression!)" << std::endl;
		return (EXIT_FAILURE);
	}

	RPN	calculator;
	try {
		calculator.evaluate(argv[1]);
		return (EXIT_SUCCESS);
	}
	catch (std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
}
