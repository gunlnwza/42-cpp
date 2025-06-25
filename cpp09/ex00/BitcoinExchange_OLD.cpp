#include "BitcoinExchange.hpp"

#define MAX_AMOUNT 1000


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
    this->read_database(database_filename);
}


std::ifstream open_infile(const std::string& filename)
{
    std::ifstream infile(filename);
    if (!infile)
        throw (std::runtime_error("Cannot open '" + filename + "'"));
    return (infile);
}

std::string get_error_message(size_t line_nb, const std::string& line, const std::string& reason)
{
    std::stringstream ss;
    ss << line_nb;
    return ("Invalid line " + ss.str() + ": '" + line + "' (" + reason + ")");
}

std::pair<std::string, std::string> split_two(const std::string& line, const std::string& delimiter)
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

double parse_double(const std::string& s)
{
    char    *ptr;
    double  value;

    value = std::strtod(s.c_str(), &ptr);
    if (*ptr != '\0')
        throw (std::runtime_error("not a number"));
    return (value);
}

// use only 2 decimal digits, cut out trailing 0
static std::string format_price(double price)
{
    std::ostringstream  oss;
    std::string         result;

    oss << std::fixed << std::setprecision(2) << price;
    result = oss.str();
    result.erase(result.find_last_not_of('0') + 1);
    if (result.back() == '.')
        result.pop_back();
    return (result);
}


void BitcoinExchange::read_database_header(const std::string& line)
{
    std::pair<std::string, std::string> tokens;

    tokens = split_two(line, ",");
    if (tokens.first != "date" || tokens.second != "exchange_rate")
        throw (std::runtime_error("invalid header name(s)"));
}

void BitcoinExchange::read_database_line(const std::string& line)
{
    std::pair<std::string, std::string> tokens;
    Date                                date;
    double                              exchange_rate;

    tokens = split_two(line, ",");
    date.parse_date(tokens.first);
    exchange_rate = parse_double(tokens.second);
    if (exchange_rate < 0)
        throw (std::runtime_error("negative exchange rate"));
    this->date_to_exchange_rate[date] = exchange_rate;
}

void BitcoinExchange::read_database(const std::string& database_filename)
{
    std::ifstream                       database;
    size_t                              line_nb;
    std::string                         line;
    std::pair<std::string, std::string> tokens;

    database = open_infile(database_filename);
    line_nb = 1;
    while (std::getline(database, line))
    {
        try {
            if (line_nb == 1)
                this->read_database_header(line);
            else
                this->read_database_line(line);
        } catch (const std::runtime_error& e) {
            throw (std::runtime_error(get_error_message(line_nb, line, e.what())));
        }
        line_nb++;
    }
}


void BitcoinExchange::evaluate_query_header(const std::string& line) const
{
    std::pair<std::string, std::string> tokens;

    tokens = split_two(line, " | ");
    if (tokens.first != "date" || tokens.second != "value")
        throw (std::runtime_error("invalid header name(s)"));
}

double BitcoinExchange::get_exchange_rate(const Date& date) const
{
    std::map<Date, double>::const_iterator it;
    
    it = this->date_to_exchange_rate.lower_bound(date);
    if (it == this->date_to_exchange_rate.end())
        --it;
    else if (it->first != date)
    {
        if (it != this->date_to_exchange_rate.begin())
            --it;
    }
    return (it->second);
}

void BitcoinExchange::evaluate_query_line(const std::string& line) const
{
    std::pair<std::string, std::string> tokens;
    Date                                date;
    double                              amount;
    double                              price;

    if (line == "")
        return ;
    tokens = split_two(line, " | ");
    date.parse_date(tokens.first);
    amount = parse_double(tokens.second);
    if (amount < 0)
        throw (std::runtime_error("invalid amount: not a positive number"));
    if (amount > MAX_AMOUNT)
        throw (std::runtime_error("invalid amount: too large a number"));
    price = this->get_exchange_rate(date);
    std::cout << date << " => " << amount << " = " << format_price(amount * price) << std::endl;
}

void BitcoinExchange::evaluate_query(const std::string& query_filename) const
{
    std::ifstream                       query;
    size_t                              line_nb;
    std::string                         line;
    std::pair<std::string, std::string> tokens;

    query = open_infile(query_filename);
    line_nb = 1;
    while (std::getline(query, line))
    {
        try {
            if (line_nb == 1)
                this->evaluate_query_header(line);
            else
                this->evaluate_query_line(line);
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << " ('" << line << "')" << std::endl;
        }
        line_nb++;
    }
}
