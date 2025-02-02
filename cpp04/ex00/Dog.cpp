#include "Dog.hpp"


Dog::Dog(void)
{
    this->type = DOG_TYPE_STRING;
}

Dog::Dog(const Dog& other)
{
    *this = other;
}

Dog& Dog::operator=(const Dog& other)
{
    this->type = other.type;

    return (*this);
}

Dog::~Dog(void)
{
}


void Dog::makeSound(void) const
{
    std::cout << "Woof" << std::endl;
}
