#include "ScavTrap.hpp"
#include "FlagTrap.hpp"

int main(void)
{
    FlagTrap a("Alex");
    FlagTrap b("Bob");

    std::cout << std::endl;

    a.highFiveGuys();
    b.highFiveGuys();

    std::cout << std::endl;

    return (0);
}
