#include <iostream>
#include "ClapTrap.hpp"

void battle_start(ClapTrap& a, ClapTrap& b)
{
    std::cout << std::endl;
    std::cout << "Battle Start!" << std::endl
              << "********" << std::endl;
    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    a.beRepaired(42);
    std::cout << "********" << std::endl;
    std::cout << std::endl;
}

void fight_until_exhaust(ClapTrap& a, ClapTrap& b)
{
    std::cout << std::endl;
    std::cout << "ClapTrap " << a.getName() << " wants to fight until he is exhausted. Let's go!" << std::endl
              << "********" << std::endl;
    for (int i = 0; i < 9; i++)
        a.attack(b.getName());
    a.beRepaired(42);
    std::cout << "********" << std::endl;
    std::cout << std::endl;
}

void print_result(ClapTrap& a, ClapTrap& b)
{
    std::cout << std::endl;
    std::cout << "Result" << std::endl
              << "********" << std::endl
              << a << std::endl
              << b << std::endl
              << "********" << std::endl;
    std::cout << std::endl;
}

int main(void)
{
    ClapTrap a;
    a.setName("Alex");

    ClapTrap b("Bob");

    ClapTrap c = a;
    
    ClapTrap d;
    d = a;

    battle_start(a, b);
    print_result(a, b);
    fight_until_exhaust(a, b);
    print_result(a, b);

    return (0);
}
