#include "ScalarConverter.hpp"

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
