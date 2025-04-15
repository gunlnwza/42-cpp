#include <iostream>
#include <iomanip>
#include <cerrno>
#include <cfloat>
#include <sstream>

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
	if (input == "" || input == ".f")
		return (TYPE_INVALID);
	if (input == "inff" || input == "+inff" || input == "-inff" || input == "nanf")
		return (TYPE_FLOAT);
	else if (input == "inf" || input == "+inf" || input == "-inf" || input == "nan")
		return (TYPE_DOUBLE);

	if (input.length() == 1)
		return (TYPE_CHAR);

	char	*ptr;
	long	value;

	value = std::strtol(input.c_str(), &ptr, 10);
	if (*ptr == '\0')
		return (TYPE_INT);
	if (*ptr != '.')
		return (TYPE_INVALID);
	ptr++;

	value = std::strtol(ptr, &ptr, 10);
	(void) value;
	if (*ptr == '\0')
		return (TYPE_DOUBLE);
	else if (*ptr == 'f' && ptr[1] == '\0')
		return (TYPE_FLOAT);
	return (TYPE_INVALID);
}


std::string	get_char_string(char c)
{
	std::stringstream	ss;

	if (std::isprint(c))
		ss << "'" << static_cast<char>(c) << "'";
	else if (0 <= c && c <= CHAR_MAX)
		ss << "Non displayable";
	else
		ss << "Undefined";
	return (ss.str());
}

std::string	get_int_string(int i)
{
	std::stringstream	ss;

	ss << i;
	return (ss.str());
}

std::string	get_float_string(float f)
{
	std::stringstream	ss;

	ss << std::fixed << std::setprecision(10) << f << "f";
	return (ss.str());
}

std::string	get_double_string(double d)
{
	std::stringstream	ss;

	ss << std::fixed << std::setprecision(10) << d;
	return (ss.str());
}

void	set_result(t_result& res, std::string c_msg, std::string i_msg, std::string f_msg, std::string d_msg)
{
	res.char_message = c_msg;
	res.int_message = i_msg;
	res.float_message = f_msg;
	res.double_message = d_msg;
}

void	print_result(t_result& res)
{
	std::cout << "char   : " << res.char_message << std::endl
			  << "int    : " << res.int_message << std::endl
			  << "float  : " << res.float_message << std::endl
			  << "double : " << res.double_message << std::endl;
}


void	convert_char(const std::string &input, t_result& res)
{
	char	c = input[0];
	int		i = static_cast<int>(c);
	float	f = static_cast<float>(c);
	double	d = static_cast<double>(c);
	set_result(res, get_char_string(c), get_int_string(i), get_float_string(f), get_double_string(d));
}

void	convert_int(const std::string &input, t_result& res)
{
	errno = 0;
	char	*ptr;
	long	value = std::strtol(input.c_str(), &ptr, 10);
	if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
	{
		set_result(res, "Value dependent on int", (value < 0) ? "Underflow" : "Overflow", "Value dependent on int", "Value dependent on int");
		return ;
	}

	int		i = static_cast<int>(value);
	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);
	set_result(res, get_char_string(c), get_int_string(i), get_float_string(f), get_double_string(d));

	if (i < CHAR_MIN)
		res.char_message = "Underflow";
	else if (i > CHAR_MAX)
		res.char_message = "Overflow";
}

void	convert_float(const std::string &input, t_result& res)
{
	if (input == "inff" || input == "+inff" || input == "-inff" || input == "nanf")
	{
		if (input == "inff" || input == "+inff")
			set_result(res, "Impossible", "Impossible", "inff", "inf");
		else if (input == "-inff")
			set_result(res, "Impossible", "Impossible", "-inff", "-inf");
		else if (input == "nanf")
			set_result(res, "Impossible", "Impossible", "nanf", "nan");
		return ;
	}

	errno = 0;
	char	*ptr;
	double	value = std::strtod(input.c_str(), &ptr);
	if (errno == ERANGE || value < -FLT_MAX || value > FLT_MAX)
	{
		set_result(res, "Value dependent on float", "Value dependent on float", (value < 0) ? "Underflow" : "Overflow", "Value dependent on float");
		return ;
	}

	float	f = static_cast<float>(value);
	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);
	set_result(res, get_char_string(c), get_int_string(i), get_float_string(f), get_double_string(d));

	if (value < CHAR_MIN)
		res.char_message = "Underflow";
	else if (value > CHAR_MAX)
		res.char_message = "Overflow";
	if (value < INT_MIN)
		res.int_message = "Underflow";
	else if (value > INT_MAX)
		res.int_message = "Overflow";
}

void	convert_double(const std::string &input, t_result& res)
{
	if (input == "inf" || input == "+inf" || input == "-inf" || input == "nan")
	{
		if (input == "inf" || input == "+inf")
			set_result(res, "Impossible", "Impossible", "inff", "inf");
		else if (input == "-inf")
			set_result(res, "Impossible", "Impossible", "-inff", "-inf");
		else if (input == "nan")
			set_result(res, "Impossible", "Impossible", "nanf", "nan");
		return ;
	}

	errno = 0;
	char	*ptr;
	double	value = std::strtod(input.c_str(), &ptr);
	if (errno == ERANGE || value < -DBL_MAX || value > DBL_MAX)
	{
		set_result(res, "Value dependent on double", "Value dependent on double", "Value dependent on double", (value < 0) ? "Underflow" : "Overflow");
		return ;
	}

	double	d = value;
	char	c = static_cast<char>(d);
	int		i = static_cast<int>(d);
	float	f = static_cast<float>(d);
	set_result(res, get_char_string(c), get_int_string(i), get_float_string(f), get_double_string(d));

	if (value < CHAR_MIN)
		res.char_message = "Underflow";
	else if (value > CHAR_MAX)
		res.char_message = "Overflow";
	if (value < INT_MIN)
		res.int_message = "Underflow";
	else if (value > INT_MAX)
		res.int_message = "Overflow";
	if (value < -FLT_MAX)
		res.float_message = "Underflow";
	else if (value > FLT_MAX)
		res.float_message = "Overflow";
}


void	ScalarConverter::convert(const std::string& input)
{
	t_scalar_type	type;
	t_result		res;

	type = identify_type(input);
	if (type == TYPE_CHAR)
		convert_char(input, res);
	else if (type == TYPE_INT)
		convert_int(input, res);
	else if (type == TYPE_FLOAT)
		convert_float(input, res);
	else if (type == TYPE_DOUBLE)
		convert_double(input, res);
	else
	{
		std::cout << "Error: scalar's type not recognized" << std::endl;
		return ;
	}
	print_result(res);
}
