#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "config.hpp"

Config::Config(int argc, char *argv[]) 
{
    parse_arguments(argc, argv);
    if (VERBOSE) {
        display();
    }
}

void Config::helper(int status) 
{
  std::cerr << "Usage: ./lop [methods or help] [start_solutions] [strategies] [choices] [-i <instance_file>]" << std::endl
            << std::endl
            << "Methods or help:" << std::endl
            << "  --ii" << std::endl
            << "  --vnd" << std::endl
            << "  --sa" << std::endl
            << "  --help" << std::endl
            << std::endl
            << "Start solutions:" << std::endl
            << "  --random (only with --ii)" << std::endl
            << "  --cw" << std::endl
            << std::endl
            << "Strategies:" << std::endl
            << "  --transpose (only with --ii)" << std::endl
            << "  --exchange (only with --ii)" << std::endl
            << "  --insert (only with --ii)" << std::endl
            << "  --transpose-exchange-insert (only with --vnd)" << std::endl
            << "  --transpose-insert-exchange (only with --vnd)" << std::endl
            << "Choices:" << std::endl
            << "  --first " << std::endl
            << "  --best (only with --ii)" << std::endl
            << std::endl
            << std::endl;
  exit(status);
}

void Config::parse_arguments(int argc, char* argv[])
{
    if (argc < 7 || std::string(argv[1]) == "--help") {
        helper(0);
    }

    if (std::string(argv[1]) == "--ii") {
        this->m = ITERATIVE_IMPROVEMENT;
    } else if (std::string(argv[1]) == "--vnd") {
        this->m = VARIABLE_NEIGHBOURHOOD_DESCENT;
    } else if (std::string(argv[1]) == "--sa") {
        this->m = SIMULATED_ANNEALING;
    } else if (std::string(argv[1]) == "--ils") {
        this->m = ITERATIVE_LOCAL_SEARCH;
    } else {
        helper(1);
    }

    if (std::string(argv[2]) == "--random" && (this->m == ITERATIVE_IMPROVEMENT || this->m == SIMULATED_ANNEALING || this->m == ITERATIVE_LOCAL_SEARCH)) {
        this->s = RANDOM;
    } else if (std::string(argv[2]) == "--cw") {
        this->s = CHENERY_WATANABE;
    } else {
        helper(1);
    }


    if (std::string(argv[3]) == "--transpose" && (this->m == ITERATIVE_IMPROVEMENT || this->m ==  SIMULATED_ANNEALING || this->m == ITERATIVE_LOCAL_SEARCH)) {
        this->st = TRANSPOSE;
    } else if (std::string(argv[3]) == "--exchange" && (this->m == ITERATIVE_IMPROVEMENT || this->m == SIMULATED_ANNEALING || this->m == ITERATIVE_LOCAL_SEARCH)) {
        this->st = EXCHANGE;
    } else if (std::string(argv[3]) == "--insert" && (this->m == ITERATIVE_IMPROVEMENT || this->m ==  SIMULATED_ANNEALING || this->m == ITERATIVE_LOCAL_SEARCH)) {
        this->st = INSERT;
    } else if (std::string(argv[3]) == "--transpose-exchange-insert" && (this->m == VARIABLE_NEIGHBOURHOOD_DESCENT || this->m == SIMULATED_ANNEALING)) {
        this->st = TRANSPOSE_EXCHANGE_INSERT;
    } else if (std::string(argv[3]) == "--transpose-insert-exchange" && this->m == VARIABLE_NEIGHBOURHOOD_DESCENT) {
        this->st = TRANSPOSE_INSERT_EXCHANGE;
    } else {
        helper(1);
    }

    if (std::string(argv[4]) == "--first") {
        this->c = FIRST;
    }
    else if (std::string(argv[4]) == "--best" && (this->m == ITERATIVE_IMPROVEMENT || this->m == SIMULATED_ANNEALING || this->m == ITERATIVE_LOCAL_SEARCH)) {
        this->c = BEST;
    } else {
        helper(1);
    }

    if (std::string(argv[5]) == "-i") {
        this->inst = Instance(std::string(argv[6]));
    } else {
        helper(1);
    }
}

Method 
Config::method() const 
{
    return this->m;
}

StartSolution 
Config::start_solution() const 
{
    return this->s;
}

Strategy 
Config::strategy() const 
{
    return this->st;
}

Choice 
Config::choice() const 
{
    return this->c;
}

Instance 
Config::instance() 
{
    return this->inst;
}

void Config::display() const 
{
    std::cout << "Method: " << method_map[this->m] << std::endl;
    std::cout << "Start solution: " << start_solution_map[this->s] << std::endl;
    std::cout << "Strategy: " << strategy_map[this->st] << std::endl;
    std::cout << "Choice: " << choice_map[this->c] << std::endl;
    std::cout << "Instance: " << this->inst.get_name() << std::endl;
}