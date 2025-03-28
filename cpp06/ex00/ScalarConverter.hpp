#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <cstdlib>
# include <cmath>
# include <cerrno>
# include <cstring>
# include <limits>
# include <string>
# include <iostream>

typedef enum e_scalar_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
}	t_scalar_type;

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
