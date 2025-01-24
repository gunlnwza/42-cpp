#include "ClapTrap.hpp"

#define HIT_POINT 10
#define ENERGY_POINT 10
#define ATTACK_DAMAGE 0

ClapTrap::ClapTrap(void)
  : name(""),
    hit_point(HIT_POINT),
    energy_point(ENERGY_POINT),
    attack_damage(ATTACK_DAMAGE)
{
    std::cerr << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
    std::cerr << "Copy constructor called" << std::endl;

    *this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cerr << "Copy assignment operator called" << std::endl;

    this->name = other.name;
    this->hit_point = other.hit_point;
    this->energy_point = other.energy_point;
    this->attack_damage = other.attack_damage;
    return (*this);
}

ClapTrap::~ClapTrap(void)
{
    std::cerr << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
  : name(name),
    hit_point(HIT_POINT),
    energy_point(ENERGY_POINT),
    attack_damage(ATTACK_DAMAGE)
{
    std::cerr << "Constructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->energy_point <= 0)
    {
        std::cout << "ClapTrap " << this->name << " tried to attack " << target << ", but is too tired!" << std::endl;
        return ;
    }

    std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->attack_damage << " points of damage!" << std::endl;
    this->energy_point -= 1;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << "ClapTrap " << this->name << " got attacked" << ", taking " << amount << " points of damage!" << std::endl;
    this->hit_point -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->energy_point <= 0)
    {
        std::cout << "ClapTrap " << this->name << " tried to repair itself, but is too tired!" << std::endl;
        return ;
    }

    std::cout << "ClapTrap " << this->name << " repaired itself, restoring " << amount << " HP!" << std::endl;
    this->hit_point += amount;
    this->energy_point -= 1;
}

std::string ClapTrap::getName(void) const
{
    return (this->name);
}

void ClapTrap::setName(std::string name)
{
    this->name = name;
}

int ClapTrap::getHitPoint(void) const
{
    return (this->hit_point);
}

int ClapTrap::getEnergyPoint(void) const
{
    return (this->energy_point);
}

int ClapTrap::getAttackDamage(void) const
{
    return (this->attack_damage);
}

std::ostream& operator<<(std::ostream &os, ClapTrap &clap_trap)
{
    os << "ClapTrap("
       << "name=" << clap_trap.getName() << ", "
       << "hit_point=" << clap_trap.getHitPoint() << ", "
       << "energy_point=" << clap_trap.getEnergyPoint() << ", "
       << "attack_damage=" << clap_trap.getAttackDamage() << ")";
    return (os);
}
