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


template<typename T> const char* get_type_name() {}
template<> const char* get_type_name<char>() { return "char"; }
template<> const char* get_type_name<int>() { return "int"; }
template<> const char* get_type_name<float>() { return "float"; }
template<> const char* get_type_name<double>() { return "double"; }

template <typename T>
void	print_limit_depend_on(int overflow)
{
	const std::string	types[] = {"char", "int", "float", "double"};
	const std::string	depend_on_type = get_type_name<T>();
	const std::string	limit = (overflow == OVERFLOW) ? "overflow" : "underflow";

	for (unsigned long i = 0; i < sizeof(types) / sizeof(types[0]); i++)
	{
		std::cout << types[i] << ": ";
		if (types[i] == depend_on_type)
			std::cout << limit;
		else
			std::cout << "value dependent on " << depend_on_type;
		std::cout << std::endl;
	}
}


template <typename T>
std::string get_string(T value)
{
	std::ostringstream oss;

	oss << value;
	return oss.str();
}

template <>
std::string	get_string<char>(char c)
{
	std::ostringstream	oss;

	if (std::isprint(c))
		oss << c;
	else if (static_cast<int>(c) < 0)
		oss << "no character for negative value";
	else
		oss << "Non displayable";
	return (oss.str());
}

template <>
std::string get_string<double>(double d)
{
	std::ostringstream oss;

	if (std::isnan(d) || std::isinf(d))
		oss << d;
	else
		oss << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << d;
	return oss.str();
}

template <>
std::string	get_string<float>(float f)
{
	std::ostringstream	oss;

	oss << get_string<double>(f) << "f";
	return (oss.str());
}


template <typename T, typename T_limit>
void	print_type(T value, T_limit limit)
{
	std::cout << get_type_name<T>() << ": ";
	if (std::isnan(value) || std::isinf(value))
		std::cout << get_string<T>(value);
	else if (std::isnan(limit) || std::isinf(limit))
		std::cout << "impossible";
	else if (limit < std::numeric_limits<T>::lowest())
		std::cout << "underflow";
	else if (limit > std::numeric_limits<T>::max())
		std::cout << "overflow";
	else
		std::cout << get_string<T>(value);
	std::cout << std::endl;
}

template <typename T_limit>
void	print_all(t_scalar_field &field, T_limit limit)
{
	print_type(field.c, limit);
	print_type(field.i, limit);
	print_type(field.f, limit);
	print_type(field.d, limit);
}


void	convert_char(const std::string &input, t_scalar_field &field)
{
	field.c = input[0];
	field.i = static_cast<int>(field.c);
	field.f = static_cast<float>(field.c);
	field.d = static_cast<double>(field.c);

	print_all(field, field.c);
}

void	convert_int(const std::string &input, t_scalar_field &field)
{
	long	value;

	errno = 0;
	value = std::strtol(input.c_str(), NULL, 10);
	if (value < std::numeric_limits<int>::lowest() || value > std::numeric_limits<int>::max())
	{
		if (value < std::numeric_limits<int>::lowest())
			print_limit_depend_on<int>(UNDERFLOW);
		else
			print_limit_depend_on<int>(OVERFLOW);
		return ;
	}

	field.i = static_cast<int>(value);
	field.c = static_cast<char>(field.i);
	field.f = static_cast<float>(field.i);
	field.d = static_cast<double>(field.i);

	print_all(field, field.i);
}

void	convert_float(const std::string &input, t_scalar_field &field)
{
	float	value;

	errno = 0;
	value = std::strtof(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		std::cout << "float out of range!!!" << std::endl;
		if (value < std::numeric_limits<float>::lowest())
			print_limit_depend_on<float>(UNDERFLOW);
		else if (value > std::numeric_limits<float>::max())
			print_limit_depend_on<float>(OVERFLOW);
		return ;
	}

	field.f = value;
	field.c = static_cast<char>(field.f);
	field.i = static_cast<int>(field.f);
	field.d = static_cast<double>(field.f);

	print_all(field, field.f);
}

void	convert_double(const std::string &input, t_scalar_field &field)
{
	double	value;

	errno = 0;
	value = std::strtod(input.c_str(), NULL);
	if (errno == ERANGE)
	{
		if (value < std::numeric_limits<double>::lowest())
			print_limit_depend_on<double>(UNDERFLOW);
		else if (value > std::numeric_limits<double>::max())
			print_limit_depend_on<double>(OVERFLOW);
		return ;
	}

	field.d = value;
	field.c = static_cast<char>(field.d);
	field.i = static_cast<int>(field.d);
	field.f = static_cast<float>(field.d);

	print_all(field, field.d);
}


void	ScalarConverter::convert(const std::string& input)
{
	t_scalar_field	field;

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
