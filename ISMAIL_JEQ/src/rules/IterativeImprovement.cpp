#include <iostream>

#include "IterativeImprovement.hpp"
#include "initial_solution.hpp"
#include "neighbourhood.hpp"
#include "../solution.hpp"
#include "choice.hpp"

IterativeImprovement::IterativeImprovement(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule)
{
    this->initial_solution_rule = initial_solution_rule;
    this->neighbourhood_rule = neighbourhood_rule;
    this->choice_rule = choice_rule;
}


void
IterativeImprovement::run(Instance& instance)
{
    Solution solution = initial_solution(initial_solution_rule, instance);
    Solution last_solution = Solution(instance.get_size());
    int iteration = 1;
    
    while (instance.local_optimum_criterion_is_not_satisfied(last_solution, solution))
    {
        last_solution = solution;
        solution = improvement(choice_rule, neighbourhood_rule, instance, solution);
        std::cerr << "Iteration: " << iteration << " Score: " << solution.score() << std::endl;
        iteration++;
    }
    std::cerr << "Final score: " << solution.score() << std::endl;
    
    instance.set_solution(solution);
}