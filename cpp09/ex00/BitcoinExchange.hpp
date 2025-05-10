#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <sstream>

# include <map>

# include "Date.hpp"

class BitcoinExchange
{
    private:
        std::map<Date, double> date_to_exchange_rate;

        BitcoinExchange();

    public:
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange(const std::string& database_filename);

        void readDatabase(const std::string& database_filename);
        void evaluateQuery(const std::string& query_filename);
};

#endif
