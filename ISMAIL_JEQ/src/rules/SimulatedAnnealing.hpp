#ifndef SIMULATEDANNEALING_HPP
#define SIMULATEDANNEALING_HPP

#include "../config.hpp"

class SimulatedAnnealing
{
    private:
        StartSolution initial_solution_rule;
        Strategy neighbourhood_rule;
        Choice choice_rule;
    public:
        SimulatedAnnealing(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule);
        void run(Instance& instance);
};
#endif