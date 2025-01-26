#include <iostream>
#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap a;
    a.setName("Alex");

    std::cout << std::endl;

    ClapTrap b("Bob");

    std::cout << std::endl;

    ClapTrap c = a;
    c.setName("Cat");
    c.setAttackDamage(100);

    std::cout << std::endl;
    
    ClapTrap d;
    d = a;
    d.setName("Doraemon");

    std::cout << std::endl;

    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    a.beRepaired(42);
    std::cout << "> " << a << std::endl;
    std::cout << "> " << b << std::endl;

    std::cout << std::endl;

    for (int i = 0; i < 9; i++)
    {
        a.attack(b.getName());
    }
    a.beRepaired(42);
    std::cout << "> " << a << std::endl;

    std::cout << std::endl;

    c.attack(b.getName());
    b.takeDamage(c.getAttackDamage());
    b.attack(c.getName());
    std::cout << "> " << c << std::endl;
    std::cout << "> " << b << std::endl;

    std::cout << std::endl;

    return (0);
}
