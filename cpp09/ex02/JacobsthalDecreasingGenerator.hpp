#ifndef JACOBSTHAL_DECREASING_GENERATOR_HPP
# define JACOBSTHAL_DECREASING_GENERATOR_HPP

class JacobsthalDecreasingGenerator
{
    private:
        int a;
        int b;
        int cur;

    public:
        JacobsthalDecreasingGenerator();
        JacobsthalDecreasingGenerator(const JacobsthalDecreasingGenerator& other);
        JacobsthalDecreasingGenerator& operator=(const JacobsthalDecreasingGenerator& other);
        ~JacobsthalDecreasingGenerator();

        int next();
};

#endif
