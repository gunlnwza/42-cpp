#include <iostream>
#include <iomanip>

void log_error(std::string message)
{
    std::cerr << "phonebook: " << message << std::endl;
}

std::string ft_strtrim(std::string str, std::string set)
{
    size_t start = str.find_first_not_of(set);
    if (start == std::string::npos)
        return ("");
    size_t end = str.find_last_not_of(set);
    return (str.substr(start, end - start + 1));
}

std::string shorten(std::string s)
{
    if (s.size() <= 10)
        return (s);
    else
        return (s.substr(0, 9) + ".");
}

void display_row(std::string a, std::string b, std::string c, std::string d)
{
    std::cout << std::setw(10) << shorten(a) << "|" 
              << std::setw(10) << shorten(b) << "|"
              << std::setw(10) << shorten(c) << "|"
              << std::setw(10) << shorten(d) << std::endl;
}
