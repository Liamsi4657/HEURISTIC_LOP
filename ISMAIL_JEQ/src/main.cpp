#include <iostream>
#include <chrono>

#include "config.hpp"
#include "./rules/IterativeImprovement.hpp"
#include "./rules/Vnd.hpp"
#include "./rules/SimulatedAnnealing.hpp"
#include "./rules/IterativeLocalSearch.hpp"


void solve_lop(Config& config)
{
    auto start = std::chrono::high_resolution_clock::now();

    if (VERBOSE) 
    {
        std::cerr << "- Solving LOP -" << std::endl;
        std::cerr.flush();
    }

    auto algorithm_method = config.method();
    auto initial_solution_start = config.start_solution();
    auto neighbourhood_strategy = config.strategy();
    auto pivoting_choice = config.choice();
    auto instance = config.instance();

    switch(config.method()) {
        case ITERATIVE_IMPROVEMENT:
            IterativeImprovement(initial_solution_start, neighbourhood_strategy,pivoting_choice).run(instance);
            break;
        case VARIABLE_NEIGHBOURHOOD_DESCENT:
            Vnd(initial_solution_start, neighbourhood_strategy, pivoting_choice).run(instance);
            break;
        case SIMULATED_ANNEALING:
            SimulatedAnnealing(initial_solution_start, neighbourhood_strategy, pivoting_choice).run(instance);
            break;
        case ITERATIVE_LOCAL_SEARCH:
            IterativeLocalSearch(initial_solution_start, neighbourhood_strategy, pivoting_choice).run(instance);
            break;
        default:
            break;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
    instance.update_computation_time(duration.count());


    if (VERBOSE) 
    {
        std::cerr << std::endl << "- Results -" << std::endl;
        std::cerr << "Solution: " << instance.get_solution().score() << std::endl;
        std::cerr << "Execution time: " << duration.count() << "s" << std::endl;
        std::cerr.flush();
    } else {
        std::cout 	<< instance.get_name() << " "
                    << instance.get_solution().score() << " "
                    << instance.get_best_known_solution() << " "
                    << instance.get_relative_percentage_deviation() << " "
                    << instance.get_computation_time()
                    << std::endl;
        std::cout.flush();
    }
}

int
main(int argc, char *argv[])
{
    auto config = Config(argc, argv);
    solve_lop(config);
    return EXIT_SUCCESS;
}