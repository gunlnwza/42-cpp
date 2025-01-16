#include <iostream>
#include "Harl.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./harl_filter: <level>" << std::endl;
        return (1);
    }

    Harl        harl;
    std::string level_string;
    int         level;

    level_string = argv[1];
    if (level_string == "DEBUG")
        level = DEBUG;
    else if (level_string == "INFO")
        level = INFO;
    else if (level_string == "WARNING")
        level = WARNING;
    else if (level_string == "ERROR")
        level = ERROR;
    else
        level = DEFAULT;

    harl.complain(level);

    return (0);
}
