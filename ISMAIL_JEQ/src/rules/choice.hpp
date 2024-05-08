#ifndef CHOICE_HPP
#define CHOICE_HPP

#include "../config.hpp"

Solution& first_improvement(Strategy neighbourhood_rule, Instance& instance, Solution& solution);
Solution& best_improvement(Strategy neighbourhood_rule, Instance& instance, Solution& solution);
Solution& improvement(Choice pivoting_rule, Strategy neighbourhood_rule, Instance& instance, Solution& solution);
Solution& perturbation(Instance& instance, Solution& solution);

#endif