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

    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double T = 4000.0;  // Initial temperature
    double alpha = 0.99;  // Cooling rate
    int iteration = 1;

    int reheating_iteration = 100;
    double reheating = 1.2; //Reheating rate

    while (duration.count()<instance.get_max_run_time())
    {
        last_solution = solution;
        solution = improvement(choice_rule, neighbourhood_rule, instance, solution);

        if (solution.score() > last_solution.score())
        {
            last_solution = solution;
        }
        else
        {
            double p = distribution(generator);
            double delta_score = solution.score() - last_solution.score();
            if (p < 1 / (1 + exp(delta_score / T)))
            {
                last_solution = solution;
            }
        }
        T = T * alpha;
        iteration++;
        if(iteration % reheating_iteration==0){
            T=T*reheating;
        }
        duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
    }
    std::cerr << "Iterations: " << iteration << std::endl;
    std::cerr << "Final score: " << solution.score() << std::endl;
    instance.set_solution(solution);
}
