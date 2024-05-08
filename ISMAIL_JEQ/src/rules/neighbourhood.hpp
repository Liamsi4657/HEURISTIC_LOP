#ifndef NEIGHBOURHOOD_HPP
#define NEIGHBOURHOOD_HPP

#include "../config.hpp"
#include "../solution.hpp"

bool transpose_is_valid(unsigned i, unsigned j);
bool exchange_is_valid(unsigned i, unsigned j);
bool insert_is_valid(unsigned i, unsigned j);
bool neighbourhood_is_valid(Strategy neighbourhood_rule, unsigned i, unsigned j);
Solution& transpose(Solution& solution, unsigned i, unsigned j);
Solution& exchange(Solution& solution, unsigned i, unsigned j);
Solution& insert(Solution& solution, unsigned i, unsigned j);
Solution& apply_permutation(Strategy neighbourhood_rule, Solution& solution, unsigned i, unsigned j);

#endif
