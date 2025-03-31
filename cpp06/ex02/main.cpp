#include <iostream>
#include <random>
#include <ctime>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void)
{
	// Courtesy of ChatGPT
	static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));  // seed once
	std::uniform_int_distribution<int> dist(0, 2);  // range: [0, 2]

	int roll = dist(rng);
	switch (roll)
	{
		case 0: return new A;
		case 1: return new B;
		default: return new C;
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
	catch (const std::bad_cast& e) {}

	try
	{
		B& b = dynamic_cast<B&>(p);
		(void) b;
		type_name = "B";
	}
	catch (const std::bad_cast& e) {}

	try
	{
		C& c = dynamic_cast<C&>(p);
		(void) c;
		type_name = "C";
	}
	catch (const std::bad_cast& e) {}

	std::cout << "identify(Base& p): " << type_name << std::endl;
}

int	main(int argc, char **argv)
{
	Base*		ptr;
	std::string	input;

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
