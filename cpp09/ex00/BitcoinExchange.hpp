#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double> data;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange(void);

		void	readDatabase(const std::string& data_filename);
		void	evaluate(const std::string& input_filename);
};

#endif
