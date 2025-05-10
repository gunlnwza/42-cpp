#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	// if (argc != 2)
	// {
	// 	std::cout << "Error: Wrong argument format" << std::endl;
	// 	std::cout << "Usage: ./btc <query_filename>" << std::endl;
	// 	return (EXIT_FAILURE);
	// }

	BitcoinExchange	calculator("database/data_small.csv");

	// calculator.evaluateQuery(argv[1]);
	calculator.evaluateQuery("query/input.txt");

	return (EXIT_SUCCESS);
}
