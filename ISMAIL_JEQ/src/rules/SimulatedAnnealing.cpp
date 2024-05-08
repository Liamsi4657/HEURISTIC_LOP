#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include "SimulatedAnnealing.hpp"
#include "initial_solution.hpp"
#include "neighbourhood.hpp"
#include "../solution.hpp"
#include "choice.hpp"

std::default_random_engine generator(12345);  // Global variable

SimulatedAnnealing::SimulatedAnnealing(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule)
{
    this->initial_solution_rule = initial_solution_rule;
    this->neighbourhood_rule = neighbourhood_rule;
    this->choice_rule = choice_rule;
}

void SimulatedAnnealing::run(Instance& instance)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
    Solution solution = initial_solution(initial_solution_rule, instance);
    Solution last_solution = Solution(instance.get_size());

    double T = 1000.0;  // Initial temperature
    double alpha = 0.8;  // Cooling rate
    int iteration = 1;

    std::uniform_real_distribution<double> distribution(0.0,1.0);

    double time = instance.get_max_run_time()/50;
    while (duration.count()<time)
    {
        last_solution = solution;
        solution= improvement(choice_rule, neighbourhood_rule, instance, solution);

        if (solution.score() > last_solution.score())
        {
            last_solution = solution;
        }
        else
        {
            double p = distribution(generator);
            if (p < exp((solution.score() - last_solution.score()) / T))
            {
                last_solution = solution;
            }
        }
        T = T * alpha;
        iteration++;
        duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
    }
    std::cerr << "Iterations: " << iteration << std::endl;
    std::cerr << "Final score: " << solution.score() << std::endl;
    instance.set_solution(solution);
}
