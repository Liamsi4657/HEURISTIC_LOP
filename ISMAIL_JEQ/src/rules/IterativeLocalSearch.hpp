#ifndef ITERATIVELOCALSEARCH_HPP
#define ITERATIVELOCALSEARCH_HPP

#include "../config.hpp"

class IterativeLocalSearch
{
    private:
        StartSolution initial_solution_rule;
        Strategy neighbourhood_rule;
        Choice choice_rule;
    public:
        IterativeLocalSearch(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule);
        void run(Instance& instance);
};

#endif