#include <iostream>
#include <cstdlib>
#include <ctime>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int	generate_random_int(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}

Base* generate(void)
{
	int roll;

	roll = generate_random_int(0, 2);
	switch (roll)
	{
		case 0:
			std::cout << "Generate A" << std::endl;
			return (new A);
		case 1:
			std::cout << "Generate A" << std::endl;
			return (new B);
		case 2:
			std::cout << "Generate C" << std::endl;
			return (new C);
		default:
			std::cout << "Generate A" << std::endl;
			return (new A);
	}
}

void identify(Base* p)
{
	std::string	type_name;

	type_name = "?";
	if (p == dynamic_cast<A*>(p))
		type_name = "A";
	else if (p == dynamic_cast<B*>(p))
		type_name = "B";
	else if (p == dynamic_cast<C*>(p))
		type_name = "C";

	std::cout << "identify(Base* p): " << type_name << std::endl;
}

void identify(Base& p)
{
	std::string type_name;

	type_name = "?";
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void) a;
		type_name = "A";
	}
	catch (const std::exception& e) {}

	try
	{
		B& b = dynamic_cast<B&>(p);
		(void) b;
		type_name = "B";
	}
	catch (const std::exception& e) {}

	try
	{
		C& c = dynamic_cast<C&>(p);
		(void) c;
		type_name = "C";
	}
	catch (const std::exception& e) {}

	std::cout << "identify(Base& p): " << type_name << std::endl;
}

int	main(int argc, char **argv)
{
	Base*		ptr;
	std::string	input;

	std::srand(std::time(NULL));
	if (argc == 1)
	{
		ptr = generate();
		identify(ptr);
		identify(*ptr);
		delete ptr;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			input = argv[i];
			if (input == "A")
				ptr = new A;
			else if (input == "B")
				ptr = new B;
			else if (input == "C")
				ptr = new C;
			else
				ptr = new Base;
			std::cout << "[ " << input << " ]" << std::endl;
			identify(ptr);
			identify(*ptr);
			delete ptr;
			std::cout << "----------------------------------------" << std::endl;
		}
	}
	return (0);
}
