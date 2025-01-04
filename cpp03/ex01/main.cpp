#include <iostream>
#include "ScavTrap.hpp"

int main(void)
{
    ScavTrap a;
    a.setName("Alex");

    std::cout << std::endl;

    ScavTrap b("Bob");

    std::cout << std::endl;

    ScavTrap c = a;
    c.setName("Cat");

    std::cout << std::endl;

    ScavTrap d;
    d = a;
    d.setName("David");

    ClapTrap e("Elsa");

    std::cout << std::endl;

    std::cout << a << std::endl
              << b << std::endl
              << c << std::endl
              << d << std::endl
              << e << std::endl;

    std::cout << std::endl;

    std::cout << "Battle Start!" << std::endl
              << "********" << std::endl;
    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    a.beRepaired(42);

    b.attack(e.getName());
    e.takeDamage(100);
    e.beRepaired(42);

    c.guardGate();
    std::cout << "********" << std::endl;

    std::cout << std::endl;

    std::cout << "Result" << std::endl
              << "********" << std::endl
              << a << std::endl
              << b << std::endl
              << c << std::endl
              << d << std::endl
              << e << std::endl
              << "********" << std::endl;

    std::cout << std::endl;

    return (0);
}
