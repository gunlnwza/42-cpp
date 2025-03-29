#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <string>
# include <sstream>
# include <iostream>
# include <iomanip>

typedef enum e_scalar_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
}	t_scalar_type;

typedef struct s_scalar_field
{
	char	c;
	int		i;
	float	f;
	double	d;
}	t_scalar_field;

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
