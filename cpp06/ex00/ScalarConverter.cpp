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
	else if (*ptr == 'f' && *(ptr + 1) == '\0')
		return (TYPE_FLOAT);
	
	(void) i;
	return (TYPE_INVALID);
}

void	ScalarConverter::convert(const std::string& input)
{
	char	c;
	int		i;
	float	f;
	double	d;

	switch (identify_type(input))
	{
		case TYPE_CHAR:
			c = input[0];
			i = static_cast<int>(c);
			f = static_cast<float>(c);
			d = static_cast<double>(c);
			break ;
		case TYPE_INT:
			i = std::atoi(input.c_str());
			c = static_cast<char>(i);
			f = static_cast<float>(i);
			d = static_cast<double>(i);
			break ;
		case TYPE_FLOAT:
			f = std::atof(input.c_str());
			c = static_cast<char>(f);
			i = static_cast<int>(f);
			d = static_cast<double>(f);
			break ;
		case TYPE_DOUBLE:
			d = std::atof(input.c_str());
			c = static_cast<char>(d);
			i = static_cast<int>(d);
			f = static_cast<float>(d);
			break ;
		case TYPE_INVALID:
			std::cout << "Error: Scalar's type not recognized" << std::endl;
			return;
	}

	std::cout	<< "char: " << c << std::endl
				<< "int: " << i << std::endl
				<< "float: " << f << std::endl
				<< "double: " << d << std::endl;
}
