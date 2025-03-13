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


enum ScalarType	detect_type(const std::string& input)
{
	const char	*s;
	char		*endptr;
	long		l;
	double		d;

	s = input.c_str();

	l = std::strtol(s, &endptr, 10);
	if (*endptr == '\0')
		return (TYPE_INT);

	d = std::strtod(s, &endptr);
	if (*endptr == '\0')
		return (TYPE_DOUBLE);
	if (*endptr == 'f' && *(endptr + 1) == '\0')
		return (TYPE_FLOAT);

	if (input.length() == 1)
		return (TYPE_CHAR);

	(void) l;
	(void) d;
	return (TYPE_INVALID);
}


void	process_char(const std::string& input, struct ScalarFields& fields)
{
	fields.c = input[0];

	fields.i = static_cast<int>(fields.c);
	fields.f = static_cast<float>(fields.c);
	fields.d = static_cast<double>(fields.c);
}

void	process_int(const std::string& input, struct ScalarFields& fields)
{
	long long	temp;

	temp = std::atoll(input.c_str());

	if (temp < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < temp)
		fields.i_state = IMPOSSIBLE;
	if (!(0 <= temp && temp <= 255))
		fields.c_state = IMPOSSIBLE;

	fields.i = static_cast<int>(temp);
	fields.c = static_cast<char>(fields.i);
	fields.f = static_cast<float>(fields.i);
	fields.d = static_cast<double>(fields.i);

}

void	process_float(const std::string& input, struct ScalarFields& fields)
{
	fields.f = std::strtof(input.c_str(), NULL);

	if (input == "inff" || input == "-inff" || input == "nanf")
	{
		fields.c_state = IMPOSSIBLE;
		fields.i_state = IMPOSSIBLE;
	}

	fields.c = static_cast<char>(fields.f);
	fields.i = static_cast<int>(fields.f);
	fields.d = static_cast<double>(fields.f);
}

void	process_double(const std::string& input, struct ScalarFields& fields)
{
	errno = 0;

	fields.d = std::strtod(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		if (fields.f == std::numeric_limits<float>::infinity())
			std::cout << "float: overflow" << std::endl;
        else if (fields.f == 0.0f)
            std::cout << "float: underflow" << std::endl;
	}

	if (input == "inf" || input == "-inf" || input == "nan")
	{
		fields.c_state = IMPOSSIBLE;
		fields.i_state = IMPOSSIBLE;
	}
	
	fields.c = static_cast<char>(fields.d);
	fields.i = static_cast<int>(fields.d);
	fields.f = static_cast<float>(fields.d);
}


void	put_char(const struct ScalarFields& fields)
{
	if (fields.c_state == IMPOSSIBLE)
	{
		std::cout << "impossible";
		return ;
	}
	if (std::isprint(fields.c))
		std::cout << "'" << fields.c << "'";
	else
		std::cout << "Non displayable";
}

void	put_int(const struct ScalarFields& fields)
{
	if (fields.i_state == IMPOSSIBLE)
	{
		std::cout << "impossible";
		return ;
	}
	std::cout << fields.i;
}

void	put_float(const struct ScalarFields& fields)
{
	float	int_part;

	if (std::modf(fields.f, &int_part) == 0.0f)
		std::cout << fields.f << ".0f";
	else
		std::cout << fields.f << "f";
}

void	put_double(const struct ScalarFields& fields)
{
	double	int_part;

	if (std::modf(fields.d, &int_part) == 0.0f)
		std::cout << fields.d << ".0";
	else
		std::cout << fields.d;
}

void	print_fields(const struct ScalarFields& fields)
{
	std::cout << "char: ";
	put_char(fields);
	std::cout << std::endl;

	std::cout << "int: ";
	put_int(fields);
	std::cout << std::endl;

	std::cout << "float: ";
	put_float(fields);
	std::cout << std::endl;

	std::cout << "double: ";
	put_double(fields);
	std::cout << std::endl;
}


void	ScalarConverter::convert(const std::string& input)
{
	struct ScalarFields	fields;

	std::memset(&fields, 0, sizeof(fields));
	switch (detect_type(input))
	{
		case TYPE_CHAR:
			process_char(input, fields);
			break ;
		case TYPE_INT:
			process_int(input, fields);
			break ;
		case TYPE_FLOAT:
			process_float(input, fields);
			break ;
		case TYPE_DOUBLE:
			process_double(input, fields);
			break ;
		default:
			std::cout << "Error: literal's type cannot be recognized" << std::endl;
			return ;
	}
	print_fields(fields);
}
