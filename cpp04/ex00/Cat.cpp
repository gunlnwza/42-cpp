#include "Cat.hpp"


Cat::Cat(void)
{
    this->type = CAT_TYPE_STRING;
}

Cat::Cat(const Cat& other)
{
    *this = other;
}

Cat& Cat::operator=(const Cat& other)
{
    this->type = other.type;

    return (*this);
}

Cat::~Cat(void)
{
}


void Cat::makeSound(void) const
{
    std::cout << "Meow" << std::endl;
}
