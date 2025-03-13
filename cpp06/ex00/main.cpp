#include "ScalarConverter.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Expect 1 argument" << std::endl;
		std::cout << "Usage: ./scalar_converter <arg>" << std::endl;
		return (1);
	}

	ScalarConverter::convert(argv[1]);
	
	return (0);
}
