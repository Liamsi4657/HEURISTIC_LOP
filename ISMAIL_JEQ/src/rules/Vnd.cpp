#include <iostream>

#include "Vnd.hpp"
#include "initial_solution.hpp"
#include "neighbourhood.hpp"
#include "../solution.hpp"
#include "choice.hpp"

Vnd::Vnd(StartSolution initial_solution_rule, Strategy neighbourhood_rule, Choice choice_rule)
{
    this->initial_solution_rule = initial_solution_rule;
    get_neighbourhoods(neighbourhood_rule);
    this->choice_rule = choice_rule;  
}
void Vnd::get_neighbourhoods(Strategy neighbourhood_rule) {
    if (neighbourhood_rule == Strategy::TRANSPOSE_EXCHANGE_INSERT) {
        this->neighbourhood_rules[0] = Strategy::TRANSPOSE;
        this->neighbourhood_rules[1] = Strategy::EXCHANGE;
        this->neighbourhood_rules[2] = Strategy::INSERT;
    } else if (neighbourhood_rule == Strategy::TRANSPOSE_INSERT_EXCHANGE) {
        this->neighbourhood_rules[0] = Strategy::TRANSPOSE;
        this->neighbourhood_rules[1] = Strategy::INSERT;
        this->neighbourhood_rules[2] = Strategy::EXCHANGE;
    }
}
void
Vnd::run(Instance& instance)
{
    Solution solution = initial_solution(initial_solution_rule, instance);
    Solution last_solution = Solution(instance.get_size());
    auto iteration = 1;
    int i = 0;
    while (i < 3) {
        improvement(choice_rule, neighbourhood_rules[i], instance, solution);
        // std::cout << "Iteration: " << iteration << " Score: " << solution.score() << std::endl;
        if (solution.score() > last_solution.score()) {
            last_solution = solution;
            i = 0;
        } else {
            i++;
        }
        iteration++;
    }
    instance.set_solution(solution);
}