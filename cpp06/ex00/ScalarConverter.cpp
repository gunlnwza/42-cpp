#include <iostream>
#include <cerrno>
#include <cfloat>

#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter(void) {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	*this = other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void) other;
	return (*this);
}

ScalarConverter::~ScalarConverter(void) {}


t_scalar_type	identify_type(const std::string& input)
{
	char	*ptr;
	int		i;

	if (input == "inff" || input == "+inff" || input == "-inff" || input == "nanf")
		return (TYPE_FLOAT);
	else if (input == "inf" || input == "+inf" || input == "-inf" || input == "nan")
		return (TYPE_DOUBLE);

	i = std::strtol(input.c_str(), &ptr, 10);
	if (*ptr == '\0')
		return (TYPE_INT);
	if (input.length() == 1)
		return (TYPE_CHAR);

	if (*ptr != '.' || !std::isdigit(ptr[1]))
		return (TYPE_INVALID);
	ptr++;

	i = std::strtol(ptr, &ptr, 10);
	if (*ptr == '\0')
		return (TYPE_DOUBLE);
	else if (*ptr == 'f' && ptr[1] == '\0')
		return (TYPE_FLOAT);
	
	(void) i;
	return (TYPE_INVALID);
}

void	convert_char(const std::string &input)
{
	char	c = input[0];
	int		i = static_cast<int>(c);
	float	f = static_cast<float>(c);
	double	d = static_cast<double>(c);

	std::cout << "char: ";
	if (std::isprint(c))
		std::cout << "'" << c << "'";
	else
		std::cout << "Non displayable";
	std::cout << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

void	convert_int(const std::string &input)
{
	errno = 0;
	char	*ptr;
	long	value = std::strtol(input.c_str(), &ptr, 10);

	if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
	{
		std::cout << "char: Value dependent on int" << std::endl;
		std::cout << "int: ";
		if (value < 0)
			std::cout << "Underflow";
		else
			std::cout << "Overflow";
		std::cout << std::endl;
		std::cout << "float: Value dependent on int" << std::endl;
		std::cout << "double: Value dependent on int" << std::endl;
		return ;
	}

	int		i = static_cast<int>(value);
	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);

	std::cout << "char: ";
	if (value < CHAR_MIN)
		std::cout << "Underflow";
	else if (value > CHAR_MAX)
		std::cout << "Overflow";
	else if (std::isprint(c))
		std::cout << "'" << c << "'";
	else if (0 <= c && c <= CHAR_MAX)
		std::cout << "Non displayable";
	else
		std::cout << "Undefined";
	std::cout << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << std::endl;
	std::cout << "double: " << d << std::endl;
}

void	convert_float(const std::string &input)
{
	errno = 0;
	char	*ptr;
	double	value = std::strtod(input.c_str(), &ptr);

	if (errno == ERANGE || value < -FLT_MAX || value > FLT_MAX)
	{
		std::cout << "char: Value dependent on float" << std::endl;
		std::cout << "int: Value dependent on float" << std::endl;
		std::cout << "float: ";
		if (value < 0)
			std::cout << "Underflow";
		else
			std::cout << "Overflow";
		std::cout << std::endl;
		std::cout << "double: Value dependent on float" << std::endl;
		return ;
	}

	float	f = static_cast<float>(value);
	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);

	if (input == "nanf")
	{
		std::cout << "char: Impossible" << std::endl;
		std::cout << "int: Impossible" << std::endl;
		std::cout << "float: " << f << std::endl;
		std::cout << "double: " << d << std::endl;
		return ;
	}

	std::cout << "char: ";
	if (value < CHAR_MIN)
		std::cout << "Underflow";
	else if (value > CHAR_MAX)
		std::cout << "Overflow";
	else if (std::isprint(c))
		std::cout << "'" << c << "'";
	else if (0 <= c && c <= CHAR_MAX)
		std::cout << "Non displayable";
	else
		std::cout << "Undefined";
	std::cout << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << std::endl;
	std::cout << "double: " << d << std::endl;
}

void	convert_double(const std::string &input)
{
	char	*ptr;
	double	value = std::strtod(input.c_str(), &ptr);

	double	d = value;
	char	c = static_cast<char>(d);
	int		i = static_cast<int>(d);
	float	f = static_cast<float>(d);

	std::cout << "TODO" << std::endl;

	std::cout << "char: ";
	if (value < CHAR_MIN)
		std::cout << "Underflow";
	else if (CHAR_MAX < value)
		std::cout << "Overflow";
	else if (std::isprint(c))
		std::cout << "'" << c << "'";
	else if (0 <= c && c <= CHAR_MAX)
		std::cout << "Non displayable";
	else
		std::cout << "Impossible";
	std::cout << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << std::endl;
	std::cout << "double: " << d << std::endl;
}


void	ScalarConverter::convert(const std::string& input)
{
	switch (identify_type(input))
	{
		case TYPE_CHAR:
			convert_char(input);
			break ;
		case TYPE_INT:
			convert_int(input);
			break ;
		case TYPE_FLOAT:
			convert_float(input);
			break ;
		case TYPE_DOUBLE:
			convert_double(input);
			break ;
		default:
			std::cout << "Error: Scalar's type not recognized" << std::endl;
			return;
	}
}
