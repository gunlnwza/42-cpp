#include <vector>
#include <iostream>
# include <sys/time.h>

#include "vector_merge_insertion/VectorMergeInsertion.hpp"
#include "deque_merge_insertion/DequeMergeInsertion.hpp"

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

/*
int main()
{
    // VectorChunk chunk;
    std::cout << "TESTING" << std::endl;

    std::vector<int> a;
    a.push_back(5);
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);

    std::vector<int> b;
    b.push_back(10);
    b.push_back(9);
    b.push_back(8);
    b.push_back(7);
    b.push_back(6);

    VectorChunk chunk(a, b);

    VectorChunk lesser, greater;

    chunk.divide_into(lesser, greater);

    print_vector(lesser.get_data());
    print_vector(greater.get_data());

    // std::cout << "key: " << chunk.get_key() << std::endl;
    // std::cout << "data: " << chunk.get_data() << std::endl;
    // std::cout << "size: " << chunk.get_size() << std::endl;
}
*/

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
int	main(int argc, char** argv)
{
    try
    {
        const std::vector<int> inputs = parse_inputs(argc, argv);

        // int arr[8] = {6, 1, 5, 3, 8, 7, 4, 2};
        // const std::vector<int> inputs(arr, arr + sizeof(arr) / sizeof(arr[0]));

        ISortStrategy*         strategy;

        std::cout << "size: " << inputs.size() << std::endl;

        strategy = new VectorMergeInsertion();
        sort_and_report(inputs, *strategy);
        delete strategy;

        std::cout << std::endl;

        // strategy = new DequeMergeInsertion();
        // sort_and_report(inputs, *strategy);
        // delete strategy;

        return (EXIT_SUCCESS);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
}
