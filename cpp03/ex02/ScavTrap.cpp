#include "ScavTrap.hpp"

#define SCAVTRAP_HIT_POINT 100
#define SCAVTRAP_ENERGY_POINT 50
#define SCAVTRAP_ATTACK_DAMAGE 20
#define SCAVTRAP_TYPE_NAME "ScavTrap"


ScavTrap::ScavTrap(void)
  : ClapTrap::ClapTrap()
{
    std::cerr << "ScavTrap's Default Constructor called" << std::endl;

    this->setHitPoint(SCAVTRAP_HIT_POINT);
    this->setEnergyPoint(SCAVTRAP_ENERGY_POINT);
    this->setAttackDamage(SCAVTRAP_ATTACK_DAMAGE);
    this->setTypeName(SCAVTRAP_TYPE_NAME);
}

ScavTrap::ScavTrap(const ScavTrap& other)
{
    std::cerr << "ScavTrap's Copy Constructor called" << std::endl;

    *this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    std::cerr << "ScavTrap's Copy Assignment Operator called" << std::endl;

    this->setName(other.getName());
    this->setHitPoint(other.getHitPoint());
    this->setEnergyPoint(other.getEnergyPoint());
    this->setAttackDamage(other.getAttackDamage());
    this->setTypeName(other.getTypeName());
    return (*this);
}

ScavTrap::~ScavTrap(void)
{
    std::cerr << "ScavTrap's Destructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name)
  : ClapTrap::ClapTrap(name)
{
    std::cerr << "ScavTrap's Constructor called" << std::endl;

    this->setHitPoint(SCAVTRAP_HIT_POINT);
    this->setEnergyPoint(SCAVTRAP_ENERGY_POINT);
    this->setAttackDamage(SCAVTRAP_ATTACK_DAMAGE);
    this->setTypeName(SCAVTRAP_TYPE_NAME);
}


void ScavTrap::guardGate(void)
{
    if (this->getHitPoint() <= 0)
    {
        this->putNoHitPointMessage(" Cannot activate <<< Gate Keeper >>> mode!");
        return ;
    }

    if (this->getEnergyPoint() <= 0)
    {
        this->putNoEnergyPointMessage(" Cannot activate <<< Gate Keeper >>> mode!");
        return ;
    }

    std::cout << this->getFullName() << " is now in <<< Gate Keeper >>> mode!" << std::endl;
    this->is_gate_keeper_mode = true;
}

void ScavTrap::takeDamage(unsigned int amount)
{
    if (this->getHitPoint() > 0 && this->getEnergyPoint() > 0 && this->is_gate_keeper_mode)
    {
        std::cout << this->getFullName() << " is invincible, taking no damage!" << std::endl;
        return ;
    }

    ClapTrap::takeDamage(amount);
}

std::string ScavTrap::getFullName(void) const
{
    if (is_gate_keeper_mode)
        return ("<<< Gate Keeper " + ClapTrap::getFullName() + " >>>");

    return (ClapTrap::getFullName());
}
