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


enum ScalarType	detect_type(const std::string& input);

void	process_char(const std::string& input, struct ScalarFields& fields);
void	process_int(const std::string& input, struct ScalarFields& fields);
void	process_float(const std::string& input, struct ScalarFields& fields);
void	process_double(const std::string& input, struct ScalarFields& fields);

void	print_fields(const struct ScalarFields& fields);


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
