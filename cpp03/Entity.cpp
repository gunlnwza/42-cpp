#include "Entity.hpp"
#include <iostream>

Entity::Entity(void)
    : x(0), y(0)
{
    std::cerr << "Entity's Constructor called" << std::endl;
}

Entity::Entity(const Entity& other)
    : x(other.x), y(other.y)
{
    std::cerr << "Entity's Copy Constructor called" << std::endl;
}
    
Entity& Entity::operator=(const Entity& other)
{
    this->x = other.x;
    this->y = other.y;
    std::cerr << "Entity's Copy Assignment called" << std::endl;
    return (*this);
}

Entity::~Entity(void)
{
    std::cerr << "Entity's Destructor called" << std::endl;
}

void Entity::moveX(int dx)
{
    this->x += dx;
}

void Entity::moveY(int dy)
{
    this->y += dy;
}

void Entity::move(int dx, int dy)
{
    this->moveX(dx);
    this->moveY(dy);
    std::cerr << "Entity's move called, now at (" << this->x << ", " << this->y << ")" << std::endl;
}

int Entity::getX(void)
{
    return (this->x);
}

int Entity::getY(void)
{
    return (this->y);
}