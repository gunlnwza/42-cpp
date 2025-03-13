#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <cstdlib>
# include <cmath>
# include <cerrno>
# include <cstring>
# include <limits>
# include <string>
# include <iostream>

enum ScalarType
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
};

enum ScalarState
{
	OK,
	NON_DISPLAYABLE,
	IMPOSSIBLE,
	OVERFLOW,
	UNDERFLOW
};

struct ScalarFields
{
	char				c;
	int					i;
	float				f;
	double				d;

	enum ScalarState	c_state;
	enum ScalarState	i_state;
	enum ScalarState	f_state;
	enum ScalarState	d_state;
};


class ScalarConverter
{
	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter(void);

	public:
		static void	convert(const std::string& literal);
};

#endif
