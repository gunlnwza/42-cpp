#include "ft_utils.hpp"

int parse_int(const std::string& i_str)
{
    char *ptr;
    long val;

    val = std::strtol(i_str.c_str(), &ptr, 10);
    if (*ptr != '\0')
        throw (std::runtime_error("not an int string '" + i_str + "'"));
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX)
        throw (std::runtime_error("int string out-of-range '" + i_str + "'"));
    return (val);
}

double parse_double(const std::string& d_str)
{
    char   *ptr;
    double val;

    errno = 0;
    val = std::strtod(d_str.c_str(), &ptr);
    if (*ptr != '\0')
        throw (std::runtime_error("not a double string '" + d_str + "'"));
    if (errno == ERANGE || val < -DBL_MAX || val > DBL_MAX)
        throw (std::runtime_error("double string out-of-range '" + d_str + "'"));
    return (val);
}
