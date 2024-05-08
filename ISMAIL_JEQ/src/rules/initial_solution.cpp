#include <cassert>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>

#include "initial_solution.hpp"
#include "cost.hpp"

void
print_initial_solution(Instance& instance)
{
    std::cout << "Initial solution: ";
    for (auto i : instance.get_permutation()) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

Solution
random_solution(Instance& instance) 
{
    auto random_permutation = std::vector<int>(instance.get_size());
    std::iota(random_permutation.begin(), random_permutation.end(), 0);
    std::shuffle(random_permutation.begin(), random_permutation.end(), std::default_random_engine(instance.get_seed()));
    instance.update_permutation(random_permutation);
    Solution solution = instance.get_solution();
    solution.set_permutation(random_permutation);
    solution.set_score(evaluate(instance, solution));
    return solution;
}
Solution
cw_solution(Instance& instance) 
{
    auto matrix = instance.get_matrix();
    auto cw_permutation = std::vector<int>(instance.get_size());
    std::iota(cw_permutation.begin(), cw_permutation.end(), 0);
    auto default_permutation = cw_permutation;
    
    for (unsigned step = 0 ; step < instance.get_size(); step++) {
        unsigned best_row = step;
        long int best_row_score = -1;
        for (unsigned row = step ; row < instance.get_size() ; row++) {
                long int current_row_score = 0;
                for (unsigned col = 1 + step ; col < instance.get_size(); col++) {
                    current_row_score += matrix[cw_permutation[row]][col];
                }
            if (best_row_score < current_row_score) {
                best_row = row;
                best_row_score = current_row_score;
            }
    }
        std::swap(cw_permutation[step], cw_permutation[best_row]);
    }
    
    instance.update_permutation(cw_permutation);
    Solution solution = instance.get_solution();
    solution.set_permutation(cw_permutation);
    solution.set_score(evaluate(instance, solution));
    return solution;
}


Solution
initial_solution(StartSolution initial_solution_rule, Instance& instance)
{

    Solution sol;
    switch (initial_solution_rule)
    {
    case RANDOM:
        sol = random_solution(instance);
        break;
    case CHENERY_WATANABE:
        sol = cw_solution(instance);
        break;
    default:
        break;
    }
    if (VERBOSE) {
        print_initial_solution(instance);
    }

    return sol;
}
