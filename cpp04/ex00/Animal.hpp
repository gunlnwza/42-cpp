#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>
# include <iostream>

# define DOG_TYPE_STRING "Dog"
# define CAT_TYPE_STRING "Cat"

class Animal
{
    public:
        Animal(void);
        Animal(const Animal& other);
        Animal& operator=(const Animal& other);
        ~Animal(void);

        std::string getType(void) const;
        void        setType(std::string type);

        virtual void    makeSound(void) const;

    protected:
        std::string type;
};

#endif
