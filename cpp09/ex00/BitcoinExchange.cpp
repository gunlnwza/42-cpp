#include "BitcoinExchange.hpp"

#define MIN_VALUE 0
#define MAX_VALUE 1000


BitcoinExchange::BitcoinExchange(void)
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : data(other.data)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	this->data = other.data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{}


void	trim(std::string& s)
{
	size_t	start;
	size_t	end;

	start = s.find_first_not_of(" \t");
	if (start == std::string::npos)
	{
		s = "";
		return ;
	}
	end = s.find_last_not_of(" \t");
	s = s.substr(start, end - start + 1);
}

void	BitcoinExchange::readDatabase(const std::string& data_filename)
{
	std::string		line;
	std::ifstream	infile(data_filename);

	if (!infile)
	{
		std::cerr << "Error opening database" << std::endl;
		return ;
	}

	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		std::stringstream	ss(line);
		std::string			date, rate_string;

		if (!(std::getline(ss, date, ',') && std::getline(ss, rate_string)))
		{
			std::cerr << "Error reading database line" << std::endl;
			return ;
		}
		trim(date);
		trim(rate_string);

		char *ptr;
		double rate = std::strtod(rate_string.c_str(), &ptr);
		if (*ptr != '\0')
		{
			std::cerr << "Error converting database rate" << std::endl;
			return ;
		}
		this->data[date] = rate;
	}
}

void	BitcoinExchange::evaluate(const std::string& input_filename)
{
	std::string		line;
	std::ifstream	infile(input_filename);

	if (!infile)
	{
		std::cerr << "Error opening input" << std::endl;
		return ;
	}

	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		std::stringstream	ss(line);
		std::string			date, value_string;

		if (!(std::getline(ss, date, '|') && std::getline(ss, value_string)))
		{
			std::cerr << "Error: line is wrong" << std::endl;
			continue ;
		}
		trim(date);
		trim(value_string);

		char *ptr;
		double value = std::strtod(value_string.c_str(), &ptr);
		if (*ptr != '\0')
		{
			std::cerr << "Error: not a number." << std::endl;
			continue ;
		}

		if (value < MIN_VALUE)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > MAX_VALUE)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue ;
		}

		std::map<std::string, double>::iterator it = this->data.lower_bound(date);
		if (it == data.end() || it->first != date) {
			if (it == data.begin()) {
				std::cerr << "Error: no available date.\n";
				continue;
			}
			--it;
		}
		std::cout << date << " => " << value << " = " << value * it->second << '\n';
	}
}
