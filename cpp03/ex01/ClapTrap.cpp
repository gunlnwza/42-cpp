#include "ClapTrap.hpp"

#define CLAPTRAP_HIT_POINT 10
#define CLAPTRAP_ENERGY_POINT 10
#define CLAPTRAP_ATTACK_DAMAGE 0
#define CLAPTRAP_TYPE_NAME "ClapTrap"


ClapTrap::ClapTrap(void)
  : name(""),
    hit_point(CLAPTRAP_HIT_POINT),
    energy_point(CLAPTRAP_ENERGY_POINT),
    attack_damage(CLAPTRAP_ATTACK_DAMAGE),
    type_name(CLAPTRAP_TYPE_NAME)
{
    std::cerr << "ClapTrap's Default Constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
    std::cerr << "ClapTrap's Copy Constructor called" << std::endl;
    
    *this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cerr << "ClapTrap's Copy Assignment Operator called" << std::endl;

    this->name = other.name;
    this->hit_point = other.hit_point;
    this->energy_point = other.energy_point;
    this->attack_damage = other.attack_damage;
    this->type_name = other.type_name;
    return (*this);
}

ClapTrap::~ClapTrap(void)
{
    std::cerr << "ClapTrap's Destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
  : name(name),
    hit_point(CLAPTRAP_HIT_POINT),
    energy_point(CLAPTRAP_ENERGY_POINT),
    attack_damage(CLAPTRAP_ATTACK_DAMAGE),
    type_name(CLAPTRAP_TYPE_NAME)
{
    std::cerr << "ClapTrap's Constructor called" << std::endl;
}


void ClapTrap::attack(const std::string& target)
{
    if (this->hit_point <= 0)
    {
        this->putNoHitPointMessage(" Cannot attack " + target + "!");
        return ;
    }

    if (this->energy_point <= 0)
    {
        this->putNoEnergyPointMessage(" Cannot attack " + target + "!");
        return ;
    }

    std::cout << this->getFullName() << " attacks " << target << ", causing " << this->attack_damage << " points of damage!" << std::endl;
    this->energy_point -= 1;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (amount >= (unsigned int) this->hit_point)
    {
        std::cout << this->getFullName() << " got attacked" << ", taking " << this->hit_point << " points of damage! It is now broken!" << std::endl;
        this->hit_point = 0;
        return ;
    }

    std::cout << this->getFullName() << " got attacked" << ", taking " << amount << " points of damage!" << std::endl;
    this->hit_point -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hit_point <= 0)
    {
        this->putNoHitPointMessage(" Cannot repair self!");
        return ;
    }

    if (this->energy_point <= 0)
    {
        this->putNoEnergyPointMessage(" Cannot repair self!");
        return ;
    }

    std::cout << this->getFullName() << " repaired itself, restoring " << amount << " HP!" << std::endl;
    this->hit_point += amount;
    this->energy_point -= 1;
}


void ClapTrap::putNoHitPointMessage(std::string additional_message)
{
    std::cout << this->getFullName() << " is too broken!" << additional_message << std::endl;
}

void ClapTrap::putNoEnergyPointMessage(std::string additional_message)
{
    std::cout << this->getFullName() << " has no more energy left!" << additional_message << std::endl;
}


std::string ClapTrap::getName(void) const
{
    return (this->name);
}

void ClapTrap::setName(std::string name)
{
    this->name = name;
}

std::string ClapTrap::getFullName(void) const
{
    return (this->type_name + " " + this->name);
}

int ClapTrap::getHitPoint(void) const
{
    return (this->hit_point);
}

void ClapTrap::setHitPoint(int hit_point)
{
    this->hit_point = hit_point;
}

int ClapTrap::getEnergyPoint(void) const
{
    return (this->energy_point);
}

void ClapTrap::setEnergyPoint(int energy_point)
{
    this->energy_point = energy_point;
}

int ClapTrap::getAttackDamage(void) const
{
    return (this->attack_damage);
}

void ClapTrap::setAttackDamage(int attack_damage)
{
    this->attack_damage = attack_damage;
}

std::string ClapTrap::getTypeName(void) const
{
    return (this->type_name);
}

void ClapTrap::setTypeName(std::string type_name)
{
    this->type_name = type_name;
}


std::ostream& operator<<(std::ostream &os, ClapTrap &clap_trap)
{
    os << clap_trap.getTypeName() << "(name=" << clap_trap.getName() 
                            << ", hit_point=" << clap_trap.getHitPoint()
                         << ", energy_point=" << clap_trap.getEnergyPoint()
                        << ", attack_damage=" << clap_trap.getAttackDamage() << ")";
    return (os);
}
