#include "BitcoinExchange.hpp"

// Containers used: std::map, std::pair

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Wrong argument format" << std::endl;
		std::cout << "Usage: ./btc <query_filename>" << std::endl;
		return (EXIT_FAILURE);
	}

	BitcoinExchange	calculator("database/data.csv");
	calculator.evaluate_query(argv[1]);
	return (EXIT_SUCCESS);
}
