#include <iostream>
#include <iomanip>
#include <sys/time.h>

#include <vector>
#include <deque>

#define NUM_TO_SHOW 10

// Containers used: std::vector, std::deque

void put_vector(std::vector<int>& v)
{
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
}

void put_vector(std::vector<int>& v, size_t n)
{
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if (n == 0)
        {
            std::cout << "[...]";
            break ;
        }
        std::cout << *it << " ";
        n--;
    }
}

void put_deque(const std::deque<int>& d) {
    for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
        std::cout << *it << " " << std::endl;
}

void put_time(struct timeval& start, struct timeval& end)
{
    int seconds = end.tv_sec - start.tv_sec;
    int microseconds = end.tv_usec - start.tv_usec;

    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }

    std::cout << seconds << "." << microseconds << "s";
}

void selection_sort(std::vector<int>& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < v.size(); j++)
        {
            if (v[j] < v[min_index])
                min_index = j;
        }
        if (min_index != i)
            std::swap(v[i], v[min_index]);
    }
}

void selection_sort(std::deque<int>& d) {
    for (size_t i = 0; i < d.size(); i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < d.size(); j++) {
            if (d[j] < d[min_index])
                min_index = j;
        }
        if (min_index != i)
            std::swap(d[i], d[min_index]);
    }
}

int	main(int argc, char **argv)
{
    struct timeval time_start, time_end;
    
    std::vector<int> vector;
    for (int i = 1; i < argc; i++)
    {
        int num = std::atoi(argv[i]);  // TODO: add range validation
        vector.push_back(num);
    }

    std::deque<int> deque;
    for (int i = 1; i < argc; i++)
    {
        int num = std::atoi(argv[i]);  // TODO: add range validation
        deque.push_back(num);
    }

    std::cout << "Before: "; put_vector(vector, NUM_TO_SHOW); std::cout << std::endl;

    gettimeofday(&time_start, NULL);
    selection_sort(vector);  // TODO: make init more fair
    gettimeofday(&time_end, NULL);

    std::cout << "After:  "; put_vector(vector, NUM_TO_SHOW); std::cout << std::endl;

    std::cout << "Time to process a range of 3000 elements with std::vector : "; put_time(time_start, time_end); std::cout << std::endl;

    gettimeofday(&time_start, NULL);
    selection_sort(deque);
    gettimeofday(&time_end, NULL);

    std::cout << "Time to process a range of 3000 elements with std::deque : "; put_time(time_start, time_end); std::cout << std::endl;

    return (EXIT_SUCCESS);
}
