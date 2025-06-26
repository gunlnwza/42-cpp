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


static bool have_two_tokens(const std::string& row)
{
    size_t idx;

    idx = row.find(',');
    if (idx == std::string::npos)
        return (false);
    idx = row.find(',', idx);
    return (idx == std::string::npos);
}

static void split_two(const std::string& row, std::string& left, std::string& right)
{
    size_t idx = row.find(',');
    left = row.substr(0, idx);
    right = row.substr(idx + 1);
}

double parse_double(const std::string& d)
{
    char   **ptr;
    double val;

    errno = 0;
    val = std::strtod(d.c_str(), ptr);
    if (*ptr != '\0')
        throw (std::runtime_error("not a double string '" + d + "'"));
    if (errno == ERANGE || val < -DBL_MAX || val > DBL_MAX)
        throw (std::runtime_error("double string out-of-range '" + d + "'"));
    return (val);
}

// load database_file into its map container
void BitcoinExchange::read_database(const std::string& database_file_name)
{
    std::ifstream file(database_file_name.c_str());
    if (!file)
        throw (std::runtime_error("Cannot open '" + database_file_name + "'"));
    
    std::string row, left, right;

    std::getline(file, row);
    if (!have_two_tokens(row))
        throw ("wrong database header '" + row + "'");
    split_two(row, left, right);
    if (left != "data" || right != "exchange_rate")
        throw ("wrong database header '" + row + "'");

    while (std::getline(file, row))
    {
        if (!have_two_tokens(row))
            throw ("wrong database row '" + row + "'");
        split_two(row, left, right);

        Date date(left);  // TODO: parse better, refactor Date
        double price = parse_double(right);
        this->date_to_price[date] = price;
    }
}

BitcoinExchange::BitcoinExchange(const std::string& database_file_name)
{
    this->read_database(database_file_name);
}


// compute each query's money, log error message on wrong query
void BitcoinExchange::evaluate_query(const std::string& query_file_name) const
{
    std::ifstream file(query_file_name.c_str());
    if (!file)
        throw (std::runtime_error("Cannot open '" + query_file_name + "'"));

    std::cout << "[ DATABASE ]" << std::endl;
    std::map<Date, double>::const_iterator it, it_end;
    it = this->date_to_price.begin();
    it_end = this->date_to_price.end();
    for (; it != it_end; ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;


    std::string s;
    std::getline(file, s); // TODO: parse better, validate header
    
    while (std::getline(file, s))
    {
        size_t idx = s.find(" | ");
        if (idx == std::string::npos)
        {
            std::cout << "empty line" << std::endl;  // TODO: throw proper error.
            continue ;
        }

        std::string s_date = s.substr(0, idx);
        std::string s_amount = s.substr(idx + 3);

        // std::cout << "s_date="<<s_date << ", s_amount=" <<s_amount <<std::endl;

        Date date(s_date);  // TODO: parse better, refactor Date
        double amount = std::strtod(s_amount.c_str(), NULL);  // TODO: parse better, validate number


        it = this->date_to_price.lower_bound(date);
        if (it == this->date_to_price.end())
            --it;
        else if (it->first != date && it != this->date_to_price.begin())
            --it;
        double price = it->second;

        // std::cout << "read query line: " << date << ",,," << amount << std::endl;

        // std::cout << "date get from: " << it->first << std::endl;

        double money = amount * price;
        // std::cout << date << " => price=" << price << ", amount=" << amount << ", money="
            // << std::fixed << std::setprecision(2) << money << std::endl;
    
        std::cout << date << " => " << amount << " = "
            << std::fixed << std::setprecision(2) << money << std::endl;

        // std::cout <<"---" << std::endl;
    }
}
