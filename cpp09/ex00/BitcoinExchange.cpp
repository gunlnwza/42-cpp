#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this == &other)
        return (*this);
    this->date_to_price = other.date_to_price;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}


static bool have_two_tokens(const std::string& row, const std::string& delim)
{
    size_t idx;

    idx = row.find(delim);
    if (idx == std::string::npos)
        return (false);
    idx = row.find(delim, idx + delim.length());
    return (idx == std::string::npos);
}

static void split_two(const std::string& row, const std::string& delim, std::string& left, std::string& right)
{
    size_t idx = row.find(delim);
    left = row.substr(0, idx);
    right = row.substr(idx + delim.length());
}

double parse_double(const std::string& d_str)
{
    char   *ptr;
    double val;

    errno = 0;
    val = std::strtod(d_str.c_str(), &ptr);
    if (*ptr != '\0')
        throw (std::runtime_error("not a double string '" + d_str + "'"));
    if (errno == ERANGE || val < -DBL_MAX || val > DBL_MAX)
        throw (std::runtime_error("double string out-of-range '" + d_str + "'"));
    return (val);
}

// load database_file into its map container
void BitcoinExchange::read_database(const std::string& database_file_name)
{
    std::ifstream file(database_file_name.c_str());
    if (!file)
        throw (std::runtime_error("Cannot open '" + database_file_name + "'"));
    
    const std::string delim = ",";
    std::string row, left, right;
    Date date;
    double price;

    std::getline(file, row);
    if (!have_two_tokens(row, delim))
        throw ("wrong database header '" + row + "'");
    split_two(row, delim, left, right);
    if (left != "date" || right != "exchange_rate")
        throw ("wrong database header '" + row + "'");

    while (std::getline(file, row))
    {
        if (!have_two_tokens(row, delim))
            throw ("wrong database row '" + row + "'");
        split_two(row, delim, left, right);

        date.parse_date(left);
        price = parse_double(right);
        this->date_to_price[date] = price;
    }
}

BitcoinExchange::BitcoinExchange(const std::string& database_file_name) { this->read_database(database_file_name); }


double BitcoinExchange::get_price(const Date& date) const
{
    std::map<Date, double>::const_iterator it;

    it = this->date_to_price.lower_bound(date);
    if (it == this->date_to_price.end())
        --it;
    else if (it->first != date && it != this->date_to_price.begin())
        --it;
    return (it->second);
}

// compute each query's money, log error message on wrong query
void BitcoinExchange::evaluate_query(const std::string& query_file_name) const
{
    std::ifstream file(query_file_name.c_str());
    if (!file)
        throw (std::runtime_error("Cannot open '" + query_file_name + "'"));

    const std::string delim = " | ";
    std::string row, left, right;
    Date date;
    double amount, price, money;

    std::getline(file, row);
    if (!have_two_tokens(row, delim))
        throw ("wrong query header '" + row + "'");
    split_two(row, delim, left, right);
    if (left != "date" || right != "value")
        throw ("wrong query header '" + row + "'");

    while (std::getline(file, row))
    {
        if (!have_two_tokens(row, delim))  // TODO: add more ERROR HANDLING
        {
            std::cout << "Error: bad input => " << row << std::endl;
            continue ;
        }
        split_two(row, delim, left, right);

        date.parse_date(left);  // TODO: parse better, refactor Date
        amount = parse_double(right);
        price = this->get_price(date);
        money = amount * price;

        std::cout << date << " => " << amount << " = " << std::fixed << std::setprecision(2) << money << std::endl;
    }
}
