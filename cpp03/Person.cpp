#include "Person.hpp"
#include <iostream>

Person::Person(void)
    : Entity::Entity()
{
    std::cerr << "Person's Constructor called" << std::endl;
}

Person::Person(const Entity& other)
    : Entity::Entity(other)
{
    std::cerr << "Person's Copy Constructor called" << std::endl;
}

Person& Person::operator=(const Entity& other)
{
    Entity::operator=(other);
    std::cerr << "Person's Copy Assignment called" << std::endl;
    return (*this);
}

Person::~Person(void)
{
    std::cerr << "Person's Destructor called" << std::endl;
}

void Person::move(int dx, int dy)
{
    // Entity::move(dx, dy);
    Entity::moveX(dx);
    Entity::moveY(dy);
    std::cerr << "Person's move called, now at (" << this->getX() << ", " << this->getY() << ")" << std::endl;
}
