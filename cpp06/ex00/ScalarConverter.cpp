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

void	convert_char(const std::string &input, t_scalar_field &field)
{
	field.c = input[0];
	
	field.i = static_cast<int>(field.c);
	field.f = static_cast<float>(field.c);
	field.d = static_cast<double>(field.c);
}

void	convert_int(const std::string &input, t_scalar_field &field)
{
	field.i = std::atoi(input.c_str());

	field.c = static_cast<char>(field.i);
	field.f = static_cast<float>(field.i);
	field.d = static_cast<double>(field.i);
}

void	convert_float(const std::string &input, t_scalar_field &field)
{
	field.f = std::atof(input.c_str());

	field.c = static_cast<char>(field.f);
	field.i = static_cast<int>(field.f);
	field.d = static_cast<double>(field.f);
}

void	convert_double(const std::string &input, t_scalar_field &field)
{
	field.d = std::atof(input.c_str());
	
	field.c = static_cast<char>(field.d);
	field.i = static_cast<int>(field.d);
	field.f = static_cast<float>(field.d);
}

void	print_result(t_scalar_field &field)
{
	std::cout	<< "char: " << field.c << std::endl
				<< "int: " << field.i << std::endl
				<< "float: " << field.f << std::endl
				<< "double: " << field.d << std::endl;
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
	print_result(field);
}
