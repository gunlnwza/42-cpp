#include "FlagTrap.hpp"

#define FLAGTRAP_HIT_POINT 100
#define FLAGTRAP_ENERGY_POINT 100
#define FLAGTRAP_ATTACK_DAMAGE 30
#define FLAGTRAP_TYPE_NAME "FlagTrap"


FlagTrap::FlagTrap(void)
  : ClapTrap::ClapTrap()
{
    std::cerr << "FlagTrap's Default Constructor called" << std::endl;

    this->setHitPoint(FLAGTRAP_HIT_POINT);
    this->setEnergyPoint(FLAGTRAP_ENERGY_POINT);
    this->setAttackDamage(FLAGTRAP_ATTACK_DAMAGE);
    this->setTypeName(FLAGTRAP_TYPE_NAME);
}

FlagTrap::FlagTrap(const FlagTrap& other)
{
    std::cerr << "FlagTrap's Copy Constructor called" << std::endl;

    *this = other;
}

FlagTrap& FlagTrap::operator=(const FlagTrap& other)
{
    std::cerr << "FlagTrap's Copy Assignment Operator called" << std::endl;

    this->setName(other.getName());
    this->setHitPoint(other.getHitPoint());
    this->setEnergyPoint(other.getEnergyPoint());
    this->setAttackDamage(other.getAttackDamage());
    this->setTypeName(other.getTypeName());
    return (*this);
}

FlagTrap::~FlagTrap(void)
{
    std::cerr << "FlagTrap's Destructor called" << std::endl;
}

FlagTrap::FlagTrap(std::string name)
  : ClapTrap::ClapTrap(name)
{
    std::cerr << "FlagTrap's Constructor called" << std::endl;

    this->setHitPoint(FLAGTRAP_HIT_POINT);
    this->setEnergyPoint(FLAGTRAP_ENERGY_POINT);
    this->setAttackDamage(FLAGTRAP_ATTACK_DAMAGE);
    this->setTypeName(FLAGTRAP_TYPE_NAME);
}

void FlagTrap::highFiveGuys(void)
{
    std::string temp;

    std::cout << this->getFullName() << " said 'Can I get a High-Five?!?' (Press enter to High-Five)" << std::endl;
    std::getline(std::cin, temp);
}
