#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

#include "instance.hpp"

#define VERBOSE false

enum Method {
    ITERATIVE_IMPROVEMENT,
    VARIABLE_NEIGHBOURHOOD_DESCENT,
    SIMULATED_ANNEALING,
    ITERATIVE_LOCAL_SEARCH
};

enum StartSolution {
    RANDOM,
    CHENERY_WATANABE
};

enum Strategy {
    TRANSPOSE,
    EXCHANGE,
    INSERT,
    TRANSPOSE_EXCHANGE_INSERT,
    TRANSPOSE_INSERT_EXCHANGE
};

enum Choice {
    FIRST,
    BEST
};

const std::string method_map[4] = {"iterative improvement", "variable neighbourhood descent","simulated annealing", "iterative local search"};
const std::string start_solution_map[2] = {"random", "chenery-watanabe"};
const std::string strategy_map[5] = {"transpose", "exchange", "insert", "transpose, exchange, insert", "transpose, insert, exchange"};
const std::string choice_map[2] = {"first", "best"};

const std::string method_map_short[4] = {"ii", "vnd", "sa", "ils"};
const std::string start_solution_map_short[2] = {"random", "cw"};
const std::string strategy_map_short[5] = {"transpose", "exchange", "insert", "transpose-exchange-insert", "transpose-insert-exchange"};
const std::string choice_map_short[2] = {"first", "best"};

class Config {
    private:
        Method m;
        StartSolution s;
        Strategy st;
        Choice c;
        Instance inst;
        void helper(int status);
        void parse_arguments(int argc, char *argv[]);
        
    public:
        Config(int argc, char *argv[]);
        Method method() const;
        StartSolution start_solution() const;
        Strategy strategy() const;
        Choice choice() const;
        Instance instance();
        void display() const;
};

#endif