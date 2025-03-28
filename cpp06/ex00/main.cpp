#include "ScalarConverter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Expected 1 argument" << std::endl
				  << "Usage: ./scalar_converter <literal>" << std::endl;
		return (EXIT_FAILURE);
	}
	ScalarConverter::convert(argv[1]);
	return (EXIT_SUCCESS);
}
