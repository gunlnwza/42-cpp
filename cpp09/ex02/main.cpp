#include <cmath>

#include "VectorSorter.hpp"
#include "DequeSorter.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

// Containers used: std::vector, std::deque

static void parse_inputs(std::vector<int>& inputs, int argc, char **argv)
{
    char    *ptr;
    long    value;
    int     num;

    for (int i = 1; i < argc; i++)
    {
        errno = 0;
        value = std::strtol(argv[i], &ptr, 10);
        if (*ptr != '\0')
            throw (std::runtime_error("not a number"));
        if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
            throw (std::runtime_error("out of range"));
        if (value <= 0)
            throw (std::runtime_error("not a positive number"));
        num = static_cast<int>(value);
        inputs.push_back(num);
    }
}

// https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91
int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
int	main(int argc, char **argv)
{
    std::vector<int>    inputs;
    VectorSorter        vector_sorter;
    DequeSorter         deque_sorter;

    try {
        parse_inputs(inputs, argc, argv);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    const size_t N = inputs.size();

    vector_sorter.time_start();
    vector_sorter.read_inputs(inputs);
    // vector_sorter.merge_insertion_sort();
    vector_sorter.selection_sort();
    vector_sorter.time_stop();

    // deque_sorter.time_start();
    // deque_sorter.read_inputs(inputs);
    // deque_sorter.merge_insertion_sort();
    // deque_sorter.selection_sort();
    // deque_sorter.time_stop();

    std::cout << "Before: " << inputs << std::endl;
    std::cout << "After:  " << vector_sorter.get_vector() << std::endl;
    std::cout << "Time to process a range of " << N << " elements with std::vector : " << vector_sorter.get_microseconds() << " microseconds" << std::endl;
    // std::cout << "Time to process a range of " << N << " elements with std::deque : " << deque_sorter.get_microseconds() << " microseconds" << std::endl;

    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "Vector's compare count: " << vector_sorter.get_compare_count() << std::endl;
    // std::cout << "deque's compare count: " << deque_sorter.get_compare_count() << std::endl;
    std::cout << "Theoretical bound: " << (vector_sorter.get_compare_count() <= F(N) ? GREEN : RED) << F(N) << RESET << std::endl;

    return (EXIT_SUCCESS);
}
