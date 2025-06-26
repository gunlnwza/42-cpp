#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

#include <string>
#include <climits>
#include <cfloat>
#include <cerrno>
#include <cstdlib>
#include <stdexcept>

int     parse_int(const std::string& i_str);
double  parse_double(const std::string& d_str);

#endif
