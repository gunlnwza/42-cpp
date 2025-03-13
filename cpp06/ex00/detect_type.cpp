#include "ScalarConverter.hpp"

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
