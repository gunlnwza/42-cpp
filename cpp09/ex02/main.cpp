#include "VectorSorter.hpp"
#include "DequeSorter.hpp"

// Containers used: std::vector, std::deque

bool parse_inputs(std::vector<int>& inputs, int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        int num = std::atoi(argv[i]);  // TODO: add range and number validations
        inputs.push_back(num);
    }
}

int	main(int argc, char **argv)
{
    std::vector<int>    inputs;
    VectorSorter        vector_sorter;
    DequeSorter         deque_sorter;

    if (!parse_inputs(inputs, argc, argv))
        return (EXIT_FAILURE);

    vector_sorter.read_inputs(inputs);
    vector_sorter.time_start();
    vector_sorter.sort();
    vector_sorter.time_stop();

    deque_sorter.read_inputs(inputs);
    deque_sorter.time_start();
    deque_sorter.sort();
    deque_sorter.time_stop();

    std::cout << "Before: " << inputs << std::endl;
    std::cout << "After:  " << vector_sorter.get_vector() << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << " elements with std::vector : " << vector_sorter.get_microseconds() << "ms" << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << " elements with std::deque : " << deque_sorter.get_microseconds() << "ms" << std::endl;

    return (EXIT_SUCCESS);
}
