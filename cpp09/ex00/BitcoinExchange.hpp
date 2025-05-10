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

        void read_database_header(const std::string& line);
        void read_database_line(const std::string& line);

    public:
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange(const std::string& database_filename);

        void read_database(const std::string& database_filename);

        void evaluate_query(const std::string& query_filename);
};

#endif
