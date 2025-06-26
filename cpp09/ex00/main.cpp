#include <cstdlib>

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

	const std::string database_file_name = "database/data_head.csv";
	try {
		BitcoinExchange	calculator(database_file_name);
		calculator.evaluate_query(argv[1]);
	} catch (const std::runtime_error& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
