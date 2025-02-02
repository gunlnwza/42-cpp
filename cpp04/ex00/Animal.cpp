#include "Animal.hpp"


Animal::Animal(void)
{
    this->type = "";
}

Animal::Animal(const Animal& other)
{
    *this = other;
}

Animal& Animal::operator=(const Animal& other)
{
    this->type = other.type;

    return (*this);
}

Animal::~Animal(void)
{
}


std::string Animal::getType(void) const
{
    return (this->type);
}

void    Animal::setType(std::string type)
{
    this->type = type;
}


void Animal::makeSound(void) const
{
    std::cout << "< Some animal sound >" << std::endl;
}
