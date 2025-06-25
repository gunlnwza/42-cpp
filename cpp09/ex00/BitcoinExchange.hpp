#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <map>

# include "Date.hpp"

class BitcoinExchange
{
    private:
        std::map<Date, double> date_to_price;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void read_database(const std::string& database_file_name);
        BitcoinExchange(const std::string& database_file_name);

        void evaluate_query(const std::string& query_file_name) const;
};

#endif
