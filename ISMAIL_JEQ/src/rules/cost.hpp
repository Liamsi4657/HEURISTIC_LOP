#ifndef COST_HPP
#define COST_HPP

#include "../config.hpp"
#include "../solution.hpp"

int evaluate(Instance& instance, Solution& solution);
int transpose_delta(Instance& instance, Solution&  solution, unsigned i, unsigned j);
int exchange_delta(Instance& instance,  Solution& solution, unsigned i, unsigned j);
int insert_delta(Instance& instance, Solution& solution, unsigned i, unsigned j);
int delta(Strategy neighbourhood_rule, Instance& instance, Solution& solution, unsigned i, unsigned j);

#endif
