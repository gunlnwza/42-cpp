#include <iostream>
#include "ScavTrap.hpp"

void init(ScavTrap& scav_trap)
{
    // scav_trap.setName("");
    scav_trap.setHitPoint(100);
    scav_trap.setEnergyPoint(50);
    scav_trap.setAttackDamage(20);
    scav_trap.setType("ScavTrap");
}

ScavTrap::ScavTrap(void)
    : ClapTrap()
{
    std::cerr << "ScavTrap's Default constructor called" << std::endl;
    init(*this);
}

ScavTrap::ScavTrap(const ScavTrap& other)
    : ClapTrap(other.name)
{
    std::cerr << "ScavTrap's Copy constructor called" << std::endl;
    init(*this);
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    std::cerr << "ScavTrap's Copy assignment operator called" << std::endl;

    this->name = other.name;
    this->hit_point = other.hit_point;
    this->energy_point = other.energy_point;
    this->attack_damage = other.attack_damage;
    this->type = other.type;
    return (*this);
}

ScavTrap::~ScavTrap(void)
{
    std::cerr << "ScavTrap's Destructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name)
    : ClapTrap(name)
{
    std::cerr << "ScavTrap's Default constructor called" << std::endl;
    init(*this);
}

void ScavTrap::guardGate(void)
{
    std::cout << "ScavTrap " << this->getName() << " is now in Gate Keeper mode!" << std::endl;
}
