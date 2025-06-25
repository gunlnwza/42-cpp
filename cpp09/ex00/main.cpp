#include "BitcoinExchange.hpp"

// Containers used: std::map, std::pair

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Wrong argument format" << std::endl;
		std::cout << "Usage: ./btc <query_file_name>" << std::endl;
		return (EXIT_FAILURE);
	}

	std::string database_file_name = "database/data_head.csv";
	BitcoinExchange	calculator(database_file_name);
	calculator.evaluate_query(argv[1]);

	return (EXIT_SUCCESS);
}
