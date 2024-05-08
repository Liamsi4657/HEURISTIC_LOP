#ifndef VND_HPP
#define VND_HPP

#include "../config.hpp"

class Vnd
{
    private:
        StartSolution initial_solution_rule;
        Strategy neighbourhood_rules[3];
        Choice choice_rule;
    public:
        Vnd(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule);
        void run(Instance& instance);
        void get_neighbourhoods(Strategy neighbourhood_rule);
};

#endif