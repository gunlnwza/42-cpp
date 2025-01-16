#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
    : ClapTrap()
{
    std::cerr << "ScavTrap's Default constructor called" << std::endl;

    this->setHitPoint(100);
    this->setEnergyPoint(50);
    this->setAttackDamage(20);
    this->setType("ScavTrap");
}

ScavTrap::ScavTrap(const ScavTrap& other)
    : ClapTrap(other.getName())
{
    std::cerr << "ScavTrap's Copy constructor called" << std::endl;

    this->setHitPoint(other.getHitPoint());
    this->setEnergyPoint(other.getEnergyPoint());
    this->setAttackDamage(other.getAttackDamage());
    this->setType(other.getType());
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    std::cerr << "ScavTrap's Copy assignment operator called" << std::endl;

    this->setHitPoint(other.getHitPoint());
    this->setEnergyPoint(other.getEnergyPoint());
    this->setAttackDamage(other.getAttackDamage());
    this->setType(other.getType());
    return (*this);
}

ScavTrap::~ScavTrap(void)
{
    std::cerr << "ScavTrap's Destructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name)
    : ClapTrap(name)
{
    std::cerr << "ScavTrap's constructor called" << std::endl;

    this->setHitPoint(100);
    this->setEnergyPoint(50);
    this->setAttackDamage(20);
    this->setType("ScavTrap");
}

void ScavTrap::guardGate(void)
{
    std::cout << "ScavTrap " << this->getName() << " is now in Gate Keeper mode!" << std::endl;
}
