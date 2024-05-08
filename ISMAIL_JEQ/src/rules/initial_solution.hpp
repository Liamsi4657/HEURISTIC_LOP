#ifndef INITIAL_SOLUTION_HPP
#define INITIAL_SOLUTION_HPP

#include "../config.hpp"
#include "../solution.hpp"

void print_initial_solution(Instance& instance);
Solution random_solution(Instance& instance);
Solution cw_solution(Instance& instance);
Solution initial_solution(StartSolution initial_solution_rule, Instance& instance);

#endif