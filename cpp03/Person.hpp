#ifndef PERSON_H
# define PERSON_H

# include "Entity.hpp"

class Person : public Entity
{
    public:
        Person(void);
        Person(const Entity& other);
        Person& operator=(const Entity& other);
        ~Person(void);

        void move(int dx, int dy);
};

#endif
