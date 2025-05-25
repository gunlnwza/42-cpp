#ifndef I_SORT_STRATEGY
# define I_SORT_STRATEGY

# include <string>
# include <vector>

class ISortStrategy
{
    private:

    protected:
        std::string name;
        int         compare_count;

    public:
        ISortStrategy();
        ISortStrategy(const ISortStrategy& other);
        ISortStrategy& operator=(const ISortStrategy& other);
        virtual ~ISortStrategy() = 0;

        std::string get_name() const;
        int         get_compare_count() const;

        virtual void             copy_numbers(const std::vector<int>& vec) = 0;
        virtual std::vector<int> get_numbers() const = 0;

        virtual void sort() = 0;
};

#endif
