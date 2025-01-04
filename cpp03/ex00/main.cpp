#include <iostream>
#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap a;
    a.setName("Alex");

    ClapTrap b("Bob");

    ClapTrap c = a;
    
    ClapTrap d;
    d = a;

    std::cout << std::endl;

    std::cout << "Battle Start!" << std::endl
              << "********" << std::endl;
    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    a.beRepaired(42);
    std::cout << "********" << std::endl;

    std::cout << std::endl;

    std::cout << "Result" << std::endl
              << "********" << std::endl
              << a << std::endl
              << b << std::endl
              << "********" << std::endl;
              
    std::cout << std::endl;

    std::cout << "ClapTrap " << a.getName() << " wants to fight until he is exhausted. Let's go!" << std::endl
              << "********" << std::endl;
    for (int i = 0; i < 9; i++)
        a.attack(b.getName());
    a.beRepaired(42);
    std::cout << "********" << std::endl;

    std::cout << std::endl;

    std::cout << "Result" << std::endl
              << "********" << std::endl
              << a << std::endl
              << b << std::endl
              << "********" << std::endl;

    std::cout << std::endl;

    return (0);
}
