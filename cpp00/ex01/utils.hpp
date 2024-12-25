#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>

void log_error(std::string message);

std::string ft_strtrim(std::string str, std::string set);

std::string shorten(std::string s);
void        display_row(std::string a, std::string b, std::string c, std::string d);

#endif
