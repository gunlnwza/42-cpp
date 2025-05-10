#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this == &other)
        return (*this);
    this->date_to_exchange_rate = other.date_to_exchange_rate;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}


BitcoinExchange::BitcoinExchange(const std::string& database_filename)
{
    this->readDatabase(database_filename);
}


/*
You have to create a program which outputs the value of a certain amount of bitcoin
on a certain date.

This program must use a database in csv format which will represent bitcoin price
over time. This database is provided with this subject.

The program will take as input a second database, storing the different prices/dates
to evaluate.

Your program must respect these rules:
• The program name is btc.
• Your program must take a file as an argument.
• Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer, between 0 and 1000.
*/

static std::ifstream open_infile(const std::string& filename)
{
    std::ifstream infile(filename);
    if (!infile)
        throw (std::runtime_error("Cannot open '" + filename + "'"));
    return (infile);
}

static std::string get_error_message(size_t line_nb, const std::string& line, const std::string& reason)
{
    std::stringstream ss;
    ss << line_nb;
    return ("Invalid line " + ss.str() + ": '" + line + "' (" + reason + ")");
}

static std::runtime_error get_error(size_t line_nb, const std::string& line, const std::string &reason)
{
    return (std::runtime_error(get_error_message(line_nb, line, reason)));
}

static std::pair<std::string, std::string> split_two(const std::string& line, const std::string& delimiter)
{
    std::string                         s(line);
    std::pair<std::string, std::string> pair;
    size_t                              pos;

    for (size_t i = 0; i < 2; i++)
    {
        pos = s.find(delimiter);
        switch (i)
        {
            case 0: pair.first = s.substr(0, pos); break ;
            case 1: pair.second = s.substr(0, pos); break ;
        }
        s.erase(0, pos + delimiter.length());
    }
    if (pos != std::string::npos)
        throw (std::runtime_error("more than 2 tokens"));
    return (pair);
}

void BitcoinExchange::readDatabase(const std::string& database_filename)
{
    std::ifstream                       database = open_infile(database_filename);
    size_t                              line_nb = 1;
    std::string                         line;
    std::pair<std::string, std::string> tokens;

    std::cout << "Database" << std::endl;

    while (std::getline(database, line))
    {
        try {
            tokens = split_two(line, ",");
        } catch (const std::runtime_error& e) {
            throw (get_error(line_nb, line, e.what()));
        }

        if (line_nb == 1)
        {
            if (tokens.first != "date" || tokens.second != "exchange_rate")
                throw (get_error(line_nb, line, "invalid header name(s)"));
        }
        else
        {
            Date date;
            try {
                date.parse_date(tokens.first);
            } catch (const std::runtime_error& e) {
                throw (get_error(line_nb, line, e.what()));
            }

            char *ptr;
            double exchange_rate = std::strtod(tokens.second.c_str(), &ptr);
            if (*ptr != '\0')
                throw (get_error(line_nb, line, "not a number"));
            if (exchange_rate < 0)
                throw (get_error(line_nb, line, "negative exchange_rate"));
        
            this->date_to_exchange_rate[date] = exchange_rate;
        }
        line_nb++;
    }

    for (std::map<Date, double>::const_iterator it = this->date_to_exchange_rate.begin(); it != this->date_to_exchange_rate.end(); ++it) {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

void BitcoinExchange::evaluateQuery(const std::string& query_filename)
{
    std::ifstream                       query = open_infile(query_filename);
    size_t                              line_nb = 1;
    std::string                         line;
    std::pair<std::string, std::string> tokens;

    std::cout << "Query" << std::endl;

    while (std::getline(query, line))
    {
        try {
            tokens = split_two(line, " | ");
        } catch (const std::runtime_error& e) {
            throw (get_error(line_nb, line, e.what()));
        }

        if (line_nb == 1)
        {
            if (tokens.first != "date" || tokens.second != "value")
                throw (get_error(line_nb, line, "invalid header name(s)"));
        }
        else
        {
            Date date;
            try {
                date.parse_date(tokens.first);
            } catch (const std::runtime_error& e) {
                // throw (get_error(line_nb, line, e.what()));
                std::cout << "Error: bad input => " << tokens.first << std::endl;
                continue ;
            }

            char *ptr;
            double amount = std::strtod(tokens.second.c_str(), &ptr);
            if (*ptr != '\0') {
                std::cout << "Error: not a number" << std::endl;
                continue ;
            }
            if (amount < 0) {
                std::cout << "Error: not a positive number" << std::endl;
                continue ;
            }
            if (amount > 1000) {
                std::cout << "Error: too large a number" << std::endl;
                continue ;
            }

            std::cout << date << " => " << amount << " = " << amount << std::endl;
        }
        line_nb++;
    }
}
