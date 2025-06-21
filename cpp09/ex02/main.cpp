#include <climits>
#include <cerrno>

#include "vector_merge_insertion/VectorMergeInsertion.hpp"
#include "deque_merge_insertion/DequeMergeInsertion.hpp"
#include "Timer.hpp"

// Containers used: std::vector, std::deque

void print_result_details(const std::vector<int>& inputs, ISortStrategy* strategy);

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
            throw (std::runtime_error("input have not-a-number"));
        if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
            throw (std::runtime_error("input have out-of-range number"));
        if (value <= 0)
            throw (std::runtime_error("input have non-positive number"));
        num = static_cast<int>(value);
        inputs.push_back(num);
    }
    return (inputs);
}

static std::ostream& operator<<(std::ostream& os, const std::vector<int> v)
{
    const int max_head_length = 5;

    if (v.size() > max_head_length * 2)
    {
        for (size_t i = 0; i < max_head_length; ++i)
            std::cout << v[i] << " ";
        std::cout << "[...]";
        for (size_t i = v.size() - 5; i < v.size(); ++i)
            std::cout << " " << v[i];
    }
    else
    {
        for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        {
            if (it != v.begin())
                std::cout << " ";
            std::cout << *it;
        }
    }
    return (os);
}

/*
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
*/
int	main(int argc, char** argv)
{
    std::vector<int> inputs;

    try {
        inputs = parse_inputs(argc, argv);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }

    Timer                timer;
    VectorMergeInsertion vector_mi;
    DequeMergeInsertion  deque_mi;
    
    timer.start();
    vector_mi.copy_numbers(inputs);
    vector_mi.sort();
    timer.stop();
    std::cout << "Before : " << inputs << std::endl;
    std::cout << "After  : " << vector_mi.get_numbers() << std::endl;
    std::cout << "Time to process a range of " << inputs.size() << " elements with " << vector_mi.get_name() << " : "
        << timer.get_microseconds() << " microseconds" << std::endl;
    print_result_details(inputs, &vector_mi);

    timer.reset();

    timer.start();
    deque_mi.copy_numbers(inputs);
    deque_mi.sort();
    timer.stop();
    std::cout << "Time to process a range of " << inputs.size() << " elements with " << deque_mi.get_name() << " : "
        << timer.get_microseconds() << " microseconds" << std::endl;
    print_result_details(inputs, &deque_mi);

    return (EXIT_SUCCESS);
}
