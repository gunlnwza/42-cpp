#include <iostream>
#include "Harl.hpp"

int main(void)
{
    Harl        harl;
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "???"};

    for (int i = 0; i < 5; i++)
    {
        std::cout << "(" << levels[i] << ")" << std::endl;
        harl.complain(levels[i]);
        std::cout << std::endl;
    }

    return (0);
}
