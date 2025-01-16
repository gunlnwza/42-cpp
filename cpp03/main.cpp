#include "Person.hpp"
#include <iostream>

void test_entity()
{
    std::cerr << std::endl << "test_entity" << std::endl;

    Entity entity_1;

    entity_1.move(10, 10);
}

void test_person()
{
    std::cout << std::endl << "test_person" << std::endl;

    Person person_1;

    person_1.move(42, 0);
}

void test_copy_constructor()
{
    std::cout << std::endl << "test_copy_constructor" << std::endl;

    std::cout << "entity_1" << std::endl;
    Entity entity_1;

    std::cout << "entity_2" << std::endl;
    Entity entity_2 = entity_1;

    std::cout << "person_1" << std::endl;
    Person person_1 = entity_1;
    // Person person_1;

    std::cout << "person_2" << std::endl;
    Person person_2 = person_1;
}

void test_copy_assignment()
{
    std::cout << std::endl << "test_copy_assignment" << std::endl;
}

int main(void)
{
    test_entity();
    test_person();
    test_copy_constructor();
    test_copy_assignment();
}
