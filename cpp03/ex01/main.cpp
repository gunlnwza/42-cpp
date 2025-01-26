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
    d.setName("Doraemon");

    std::cout << std::endl;

    ClapTrap clap_clap("ClapClap");

    std::cout << std::endl;

    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << std::endl;

    b.beRepaired(42);
    b.guardGate();
    a.attack(b.getName());
    b.takeDamage(a.getAttackDamage());
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << std::endl;

    std::cout << a << std::endl;

    std::cout << std::endl;

    b.attack(clap_clap.getName());
    clap_clap.takeDamage(b.getAttackDamage());
    std::cout << b << std::endl;
    std::cout << clap_clap << std::endl;

    std::cout << std::endl;

    return (0);
}
