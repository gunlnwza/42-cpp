#include <vector>
#include <iostream>
# include <sys/time.h>

#include "VectorMergeInsertion.hpp"
#include "DequeMergeInsertion.hpp"

// Containers used: std::vector, std::deque

static const std::vector<int> parse_inputs(int argc, char **argv)
{
    std::vector<int> inputs;
    char             *ptr;
    long             value;
    int              num;

    for (int i = 1; i < argc; i++)
    {
        errno = 0;
        value = std::strtol(argv[i], &ptr, 10);
        if (*ptr != '\0')
            throw (std::runtime_error("not a number"));
        if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
            throw (std::runtime_error("not an int"));
        if (value <= 0)
            throw (std::runtime_error("not a positive int"));
        num = static_cast<int>(value);
        inputs.push_back(num);
    }
    return (inputs);
}

static void print_vector(const std::vector<int>& vector)
{
    const int max_head_length = 5;

    if (vector.size() > max_head_length * 2)
    {
        for (size_t i = 0; i < max_head_length; ++i)
            std::cout << vector[i] << " ";
        std::cout << "... ";
        for (size_t i = vector.size() - 5; i < vector.size(); ++i)
            std::cout << vector[i] << " ";
    }
    else
    {
        for (std::vector<int>::const_iterator it = vector.begin(); it != vector.end(); ++it)
            std::cout << *it << " ";
    }
}

static long get_microseconds(struct timeval t_start, struct timeval t_stop)
{
    int seconds;
    int microseconds;

    seconds = t_stop.tv_sec - t_start.tv_sec;
    microseconds = t_stop.tv_usec - t_start.tv_usec;
    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }
    return (1000000 * seconds + microseconds);
}

static void sort_and_report(const std::vector<int>& inputs, ISortStrategy& strategy)
{
    const size_t    N = inputs.size();
    struct timeval  t_start;
    struct timeval  t_stop;
    long            microseconds;

    gettimeofday(&t_start, NULL);
    strategy.copy_numbers(inputs);
    strategy.sort();
    gettimeofday(&t_stop, NULL);
    microseconds = get_microseconds(t_start, t_stop);

    std::cout << "Before : " ;
    print_vector(inputs);
    std::cout << std::endl;

    std::cout << "After  : " ;
    print_vector(strategy.get_numbers());
    std::cout << std::endl;

    std::cout << "Time to process a range of " << N << " elements with "
              << strategy.get_name() << " : " << microseconds << " microseconds" << std::endl;
}

int	main(int argc, char** argv)
{
    try
    {
        const std::vector<int> inputs = parse_inputs(argc, argv);
        ISortStrategy*         strategy;

        strategy = new VectorMergeInsertion();
        sort_and_report(inputs, *strategy);
        delete strategy;

        std::cout << std::endl;

        strategy = new DequeMergeInsertion();
        sort_and_report(inputs, *strategy);
        delete strategy;

        return (EXIT_SUCCESS);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
}
