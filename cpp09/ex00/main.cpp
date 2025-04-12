#include "BitcoinExchange.hpp"

// std::ifstream	*open_infile(const char* str)
// {
// 	errno = 0;
// 	std::string		filename = str;
// 	std::ifstream	infile(filename);
	
// 	if (!infile)
// 	{
// 		std::cerr << "Error: cannot read '" << filename << "' (" << std::strerror(errno) << ")" << std::endl;
// 		return (NULL);
// 	}
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong argument format" << std::endl
				  << "Usage: ./btc input_filename" << std::endl;
		return (1);
	}

	BitcoinExchange	calculator;

	calculator.readDatabase("data.csv");
	calculator.evaluate(argv[1]);

	return (0);
}
