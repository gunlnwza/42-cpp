#include <iostream>
#include "Array.hpp"

// this was included in the project page
#define MAX_VAL 750

int subject_main()
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    // SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }

    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;

	return 0;
}

// this is my test
int	main()
{
	Array<int> A;
	std::cout << "A.size() = " << A.size() << std::endl;
	std::cout << "A = " << A << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	Array<int> B(8);
	std::cout << "B.size() = " << B.size() << std::endl;
	std::cout << "B = " << B << std::endl;
	B[0] = 42;
	B[1] = 24;
	B[2] = 100;
	std::cout << "B = " << B << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	Array<int> C = B;
	std::cout << "C.size() = " << C.size() << std::endl;
	std::cout << "C = " << C << std::endl;
	C[5] = -42;
	std::cout << "C = " << C << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	Array<int> D;
	D = B;
	std::cout << "D.size() = " << D.size() << std::endl;
	std::cout << "D = " << D << std::endl;
	D[5] = 100;
	std::cout << "D = " << D << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	Array<Array<int> > two_dimensions(4);
	std::cout << "two_dimensions.size() = " << two_dimensions.size() << std::endl;
	std::cout << "two_dimensions = " << two_dimensions << std::endl;
	two_dimensions[0] = A;
	two_dimensions[1] = B;
	two_dimensions[2] = C;
	two_dimensions[3] = D;
	std::cout << "two_dimensions = " << two_dimensions << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	Array<std::string> ideas(8);
	std::cout << "ideas.size() = " << ideas.size() << std::endl;
	std::cout << "ideas = " << ideas << std::endl;
	ideas[0] = "I am dog";
	ideas[1] = "I am cat";
	ideas[2] = "We are not in cpp04 anymore";
	ideas[-1] = "I love Mixue's soft serve";
	ideas[-2] = "I implemented negative indexing";
	std::cout << "ideas = " << ideas << std::endl;
	std::cout << std::endl;

	for (int i = -12; i < 12; i++)
	{
		if (i == 0)
			std::cout << std::endl;

		std::cout << "ideas[" << i << "] = ";
		try
		{
			std::cout << ideas[i] << std::endl;
		}
		catch (std::out_of_range& e)
		{
			std::cout << "CANNOT BE ACCESSED (exception caught)" << std::endl;
		}	
	}
	std::cout << "------------------------------------------" << std::endl;

	return (0);
}
