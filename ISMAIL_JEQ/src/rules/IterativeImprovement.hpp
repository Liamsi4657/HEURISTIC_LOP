#ifndef ITERATIVEIMPROVEMENT_HPP
#define ITERATIVEIMPROVEMENT_HPP

#include "../config.hpp"

class IterativeImprovement
{
    private:
        StartSolution initial_solution_rule;
        Strategy neighbourhood_rule;
        Choice choice_rule;
    public:
        IterativeImprovement(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule);
        void run(Instance& instance);
};

#endif