#include <iostream>
#include <chrono>

#include "IterativeLocalSearch.hpp"
#include "initial_solution.hpp"
#include "neighbourhood.hpp"
#include "../solution.hpp"
#include "choice.hpp"

IterativeLocalSearch::IterativeLocalSearch(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule)
{
    this->initial_solution_rule = initial_solution_rule;
    this->neighbourhood_rule = neighbourhood_rule;
    this->choice_rule = choice_rule;
}


void
IterativeLocalSearch::run(Instance& instance)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);

    Solution solution = initial_solution(initial_solution_rule, instance);
    int iteration = 1;

    solution = improvement(choice_rule, neighbourhood_rule, instance, solution);
    while (duration.count() < instance.get_max_run_time())
    {
        Solution last_solution = solution;
        solution = perturbation(instance, solution);
        solution = improvement(choice_rule, neighbourhood_rule, instance, solution);
        if (!instance.local_optimum_criterion_is_not_satisfied(last_solution, solution))
        {
            solution = last_solution;
        }
        iteration++;
        duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
    }
    std::cerr << "Iteration: " << iteration << " Final Score: " << solution.score() << std::endl;
    
    instance.set_solution(solution);
}