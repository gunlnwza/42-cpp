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

void	convert_char(const std::string &input, t_scalar_field &field)
{
	field.c = input[0];
	
	field.i = static_cast<int>(field.c);
	field.f = static_cast<float>(field.c);
	field.d = static_cast<double>(field.c);

	if (std::isprint(field.c))
		std::cout << "char: " << field.c << std::endl;
	else if (field.c < 0)
		std::cout << "char: " << "no character for negative value" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;
	std::cout << "int: " << field.i << std::endl;
	std::cout << "float: " << field.f << std::endl;
	std::cout << "double: " << field.d << std::endl;
}

void	convert_int(const std::string &input, t_scalar_field &field)
{
	long	value;

	errno = 0;
	value = std::strtol(input.c_str(), NULL, 10);
	if (value < std::numeric_limits<int>::lowest())
	{
		std::cout << "char: " << "value dependent on int" << std::endl;
		std::cout << "int: " << "underflow" << std::endl;
		std::cout << "float: " << "value dependent on int" << std::endl;
		std::cout << "double: " << "value dependent on int" << std::endl;
		return ;
	}
	else if (std::numeric_limits<int>::max() < value)
	{
		std::cout << "char: " << "value dependent on int" << std::endl;
		std::cout << "int: " << "overflow" << std::endl;
		std::cout << "float: " << "value dependent on int" << std::endl;
		std::cout << "double: " << "value dependent on int" << std::endl;
		return ;
	}
	field.i = static_cast<int>(value);

	field.c = static_cast<char>(field.i);
	field.f = static_cast<float>(field.i);
	field.d = static_cast<double>(field.i);

	if (field.i < std::numeric_limits<char>::lowest())
		std::cout << "char: " << "underflow" << std::endl;
	else if (std::numeric_limits<char>::max() < field.i)
		std::cout << "char: " << "overflow" << std::endl;
	else if (std::isprint(field.c))
		std::cout << "char: " << field.c << std::endl;
	else if (field.c < 0)
		std::cout << "char: " << "no character for negative value" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;
	std::cout << "int: " << field.i << std::endl;
	std::cout << "float: " << field.f << std::endl;
	std::cout << "double: " << field.d << std::endl;
}

void	convert_float(const std::string &input, t_scalar_field &field)
{
	float	value;

	errno = 0;
	value = std::strtof(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		if (value > std::numeric_limits<float>::max())
		{
			std::cout << "char: " << "value dependent on float" << std::endl;
			std::cout << "int: " << "value dependent on float" << std::endl;
			std::cout << "float: " << "overflow" << std::endl;
			std::cout << "double: " << "value dependent on float" << std::endl;
		}
		else if (value < std::numeric_limits<float>::lowest())
		{
			std::cout << "char: " << "value dependent on float" << std::endl;
			std::cout << "int: " << "value dependent on float" << std::endl;
			std::cout << "float: " << "underflow" << std::endl;
			std::cout << "double: " << "value dependent on float" << std::endl;
		}
		return ;
	}
	field.f = value;

	field.i = static_cast<int>(field.f);
	field.c = static_cast<char>(field.f);
	field.d = static_cast<double>(field.f);

	if (field.f < std::numeric_limits<char>::lowest())
		std::cout << "char: " << "underflow" << std::endl;
	else if (std::numeric_limits<char>::max() < field.f)
		std::cout << "char: " << "overflow" << std::endl;
	else if (std::isprint(field.c))
		std::cout << "char: " << field.c << std::endl;
	else if (field.c < 0)
		std::cout << "char: " << "no character for negative value" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;
	if (field.f < std::numeric_limits<int>::lowest())
		std::cout << "int: " << "underflow" << std::endl;
	else if (field.f > std::numeric_limits<int>::max())
		std::cout << "int: " << "overflow" << std::endl;
	else
		std::cout << "int: " << field.i << std::endl;
	std::cout << "float: " << field.f << std::endl;
	std::cout << "double: " << field.d << std::endl;
}

void	convert_double(const std::string &input, t_scalar_field &field)
{
	double	value;

	errno = 0;
	value = std::strtod(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		if (value > std::numeric_limits<double>::max())
		{
			std::cout << "char: " << "value dependent on double" << std::endl;
			std::cout << "int: " << "value dependent on double" << std::endl;
			std::cout << "float: " << "value dependent on double" << std::endl;
			std::cout << "double: " << "overflow" << std::endl;
		}
		else if (value < std::numeric_limits<double>::lowest())
		{
			std::cout << "char: " << "value dependent on double" << std::endl;
			std::cout << "int: " << "value dependent on double" << std::endl;
			std::cout << "float: " << "value dependent on double" << std::endl;
			std::cout << "double: " << "underflow" << std::endl;
		}
		return ;
	}
	field.d = value;

	field.i = static_cast<int>(field.d);
	field.c = static_cast<char>(field.d);
	field.f = static_cast<float>(field.d);

	if (field.d < std::numeric_limits<char>::lowest())
		std::cout << "char: " << "underflow" << std::endl;
	else if (std::numeric_limits<char>::max() < field.d)
		std::cout << "char: " << "overflow" << std::endl;
	else if (std::isprint(field.c))
		std::cout << "char: " << field.c << std::endl;
	else if (field.c < 0)
		std::cout << "char: " << "no character for negative value" << std::endl;
	else
		std::cout << "char: " << "Non displayable" << std::endl;
	if (field.d < std::numeric_limits<int>::lowest())
		std::cout << "int: " << "underflow" << std::endl;
	else if (field.d > std::numeric_limits<int>::max())
		std::cout << "int: " << "overflow" << std::endl;
	else
		std::cout << "int: " << field.i << std::endl;
	if (field.d < std::numeric_limits<float>::lowest())
		std::cout << "float: " << "underflow" << std::endl;
	else if (field.d > std::numeric_limits<float>::max())
		std::cout << "float: " << "overflow" << std::endl;
	else
		std::cout << "float: " << field.f << std::endl;
	std::cout << "double: " << field.d << std::endl;
}

void	ScalarConverter::convert(const std::string& input)
{
	t_scalar_field	field;

	std::memset(&field, 0, sizeof(field));
	switch (identify_type(input))
	{
		case TYPE_CHAR:
			convert_char(input, field);
			break ;
		case TYPE_INT:
			convert_int(input, field);
			break ;
		case TYPE_FLOAT:
			convert_float(input, field);
			break ;
		case TYPE_DOUBLE:
			convert_double(input, field);
			break ;
		case TYPE_INVALID:
			std::cout << "Error: Scalar's type not recognized" << std::endl;
			return;
	}
}
