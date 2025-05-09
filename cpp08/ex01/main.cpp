#include <iostream>
#include <sys/time.h>

#include "Span.hpp"

void put_time(struct timeval& start)
{
	struct timeval now;
	gettimeofday(&now, NULL);

	long seconds = now.tv_sec - start.tv_sec;
	long microseconds = now.tv_usec - start.tv_usec;

	if (microseconds < 0) {
		seconds--;
		microseconds += 1000000;
	}

	std::cout << "(" << seconds << "." << microseconds / 1000 << "s)";
}

void benchmark(unsigned int n)
{
	Span sp = Span(n);
	std::vector<int> v;
	v.reserve(n);
	struct timeval start;

	std::cout << "- Init Vector of 1.." << n << ", and copy to Span ";
	gettimeofday(&start, NULL);
	for (unsigned int i = 1; i <= n; i++)
		v.push_back(static_cast<int>(i));
	sp.addNumbers(v.begin(), v.end());
	put_time(start);
	std::cout << std::endl;

	std::cout << "- Find shortest span ";
	gettimeofday(&start, NULL);
	unsigned int shortest = sp.shortestSpan();
	put_time(start);
	std::cout << std::endl;

	std::cout << "- Find longest span ";
	gettimeofday(&start, NULL);
	unsigned int longest = sp.longestSpan();
	put_time(start);
	std::cout << std::endl;

	std::cout << "sp.shortestSpan() = " << shortest << std::endl;
	std::cout << "sp.longestSpan() = " << longest << std::endl;

	std::cout << std::endl;
}

int	main(void)
{
	std::cout << "---------- Subject's Test ----------" << std::endl;
	Span sp = Span(5);
	
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "sp.shortestSpan() = " << sp.shortestSpan() << std::endl;
	std::cout << "sp.longestSpan() = " << sp.longestSpan() << std::endl;

	std::cout << std::endl;

	std::cout << "---------- My Test ----------" << std::endl;
	std::cout << "[ Add to potentially full Span Test ]" << std::endl;
	try {
		sp.addNumber(42);
		std::cout << "OK! Added!" << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << "'" << e.what() << "'" << std::endl;
	}

	std::cout << std::endl;

	std::cout << "[ Empty Span Test ]" << std::endl;
	Span sp2 = Span(2);
	std::cout << "sp2.shortestSpan() = ";
	try {
		std::cout << sp2.shortestSpan() << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << "'" << e.what() << "'" << std::endl;
	}
	std::cout << "sp2.longestSpan() = ";
	try {
		std::cout << sp2.longestSpan() << std::endl;
	} catch (const std::runtime_error& e) {
		std::cout << "'" << e.what() << "'" << std::endl;
	}

	std::cout << std::endl;

	std::cout << "[ INT_MIN and INT_MAX Span Test ]" << std::endl;
	sp2.addNumber(INT_MIN);
	sp2.addNumber(INT_MAX);
	std::cout << "sp2.shortestSpan() = " << sp2.shortestSpan() << std::endl;
	std::cout << "sp2.longestSpan() = " << sp2.longestSpan() << std::endl;

	std::cout << std::endl;

	std::cout << "[ Stress tests ]" << std::endl;

	benchmark(10000);
	benchmark(100000);
	benchmark(1000000);  // may start fire on the computer... just kidding!
	// benchmark(10000000);  // may start an extinction event... just kidding!
	// benchmark(100000000);  // may erase our galaxy... just kidding!

	return (0);
}
