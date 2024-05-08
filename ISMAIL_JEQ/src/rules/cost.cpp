#include <cassert>
#include <iostream>

#include "cost.hpp"

int evaluate(Instance& instance, Solution& solution) {
    auto matrix = instance.get_matrix();
    auto permutation = solution.permutation();
    int size = instance.get_size();
    int cost = 0;
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = i + 1; j < size; j++) {
            cost += matrix[permutation[i]][permutation[j]];
        }
    }
    return cost;
}

int transpose_delta(Instance& instance, Solution& solution, unsigned i, unsigned j) {
    auto matrix = instance.get_matrix();
    auto permutation = solution.permutation();
    unsigned k = permutation[i];
    unsigned l = permutation[j];
    int delta = matrix[l][k] - matrix[k][l];
    return delta;
}

int exchange_delta(Instance& instance, Solution& solution, unsigned i, unsigned j) {
    auto matrix = instance.get_matrix();
    auto permutation = solution.permutation();
    unsigned k = permutation[i];
    unsigned l = permutation[j];
    int delta = matrix[l][k] - matrix[k][l];

    for (unsigned m = i + 1; m < j; m++) {
        unsigned n = permutation[m];
        delta += matrix[l][n] - matrix[k][n];
        delta += matrix[n][k] - matrix[n][l];
    }

    return delta;
}

int insert_delta(Instance& instance, Solution& solution, unsigned i, unsigned j) {
    auto matrix = instance.get_matrix();
    auto permutation = solution.permutation();
    unsigned k = permutation[i];
    int delta = 0;
    
    if (i < j) {
        for (unsigned l = i + 1; l < j + 1 ; l++) {
            unsigned m = permutation[l];
            delta += matrix[m][k] - matrix[k][m];
        }
    }
    
    if (i > j) {
        for (unsigned l = j; l < i; l++) {
            unsigned m = permutation[l];
            delta += matrix[k][m] - matrix[m][k];
        }
    }
    
    return delta;
}

int delta(Strategy neighbourhood_rule, Instance& instance, Solution& solution, unsigned i, unsigned j)
{
    switch (neighbourhood_rule)
    {
        case Strategy::TRANSPOSE:
            return transpose_delta(instance, solution, i, j);
        case Strategy::EXCHANGE:
            return exchange_delta(instance, solution, i, j);
        case Strategy::INSERT:
            return insert_delta(instance, solution, i, j);
        default:
            assert(false);
    }
}
