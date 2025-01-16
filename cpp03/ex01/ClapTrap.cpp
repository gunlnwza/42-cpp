#include <iostream>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
    : name(""), hit_point(10), energy_point(10), attack_damage(0), type("ClapTrap")
{
    std::cerr << "ClapTrap's Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
    : name(other.name), hit_point(other.hit_point),
      energy_point(other.energy_point), attack_damage(other.attack_damage),
      type(other.type)
{
    std::cerr << "ClapTrap's Copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cerr << "ClapTrap's Copy assignment operator called" << std::endl;

    this->name = other.name;
    this->hit_point = other.hit_point;
    this->energy_point = other.energy_point;
    this->attack_damage = other.attack_damage;
    this->type = other.type;
    return (*this);
}

ClapTrap::~ClapTrap(void)
{
    std::cerr << "ClapTrap's Destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
    : name(name), hit_point(10), energy_point(10), attack_damage(0), type("ClapTrap")
{
    std::cerr << "ClapTrap's Constructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->energy_point <= 0 || this->hit_point <= 0)
    {
        std::string word;
        if (this->energy_point <= 0)
            word = "tired";
        else
            word = "injured";

        std::cout << this->type << " " << this->name << " tried to attack " << target
                  << ", but is too " << word << "!" << std::endl;
        return ;
    }

    std::cout << this->type << " " << this->name << " attacks " << target
              << ", causing " << this->attack_damage << " points of damage!" << std::endl;

    this->energy_point -= 1;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << this->type << " " << this->name << " got attacked"
              << ", taking " << amount << " points of damage!" << std::endl;

    this->hit_point -= amount;
    if (this->hit_point < 0)
        this->hit_point = 0;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->energy_point <= 0 || this->hit_point <= 0)
    {
        std::string word;
        if (this->energy_point <= 0)
            word = "tired";
        else
            word = "injured";

        std::cout << this->type << " " << this->name << " tried to repair itself"
                  << ", but is too " << word << "!" << std::endl;
        return ;
    }

    std::cout << this->type << " " << this->name << " repaired itself"
              << ", restoring " << amount << " HP!" << std::endl;

    this->energy_point -= 1;
    this->hit_point += amount;
}

void ClapTrap::setName(std::string name) {
    this->name = name;
}

void ClapTrap::setHitPoint(int hit_point) {
    this->hit_point = hit_point;
}

void ClapTrap::setEnergyPoint(int energy_point) {
    this->energy_point = energy_point;
}

void ClapTrap::setAttackDamage(int attack_damage) {
    this->attack_damage = attack_damage;
}

void ClapTrap::setType(std::string type) {
    this->type = type;
}

std::string ClapTrap::getName(void) const {
    return (this->name);
}

int ClapTrap::getHitPoint(void) const {
    return (this->hit_point);
}

int ClapTrap::getEnergyPoint(void) const {
    return (this->energy_point);
}

int ClapTrap::getAttackDamage(void) const {
    return (this->attack_damage);
}

std::string ClapTrap::getType(void) const {
    return (this->type);
}

std::ostream& operator<<(std::ostream &os, ClapTrap &trap)
{
    os << trap.getType() << "("
       << "name=" << trap.getName() << ", "
       << "hit_point=" << trap.getHitPoint() << ", "
       << "energy_point=" << trap.getEnergyPoint() << ", "
       << "attack_damage=" << trap.getAttackDamage() << ")";
    return (os);
}
