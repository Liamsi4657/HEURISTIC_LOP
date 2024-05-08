#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include <string>
#include <array>
#include <vector>
#include "solution.hpp"

#define BEST_KNOWN_FILE_PATH "./best_known/best_known.txt"
#define MAX_RUN_TIME_FILE_PATH "./max_run_time/max_runtime.txt"


class Instance 
{
    private:
        std::string instance_name_;
        double max_run_time_;
        std::vector<std::vector<int>> instance_matrix_;
        std::vector<int> instance_permutation_;
        int instance_size_ = 0;
        int instance_seed_ = 12345;
        Solution instance_solution_;
        int best_known_instance_solution_ = 0;
        double relative_deviation_percentage_ = 0.0;
        double instance_computation_time_ = 0.0;
        void verify_file(std::string filepath);
        void store_matrix(std::string filepath);
        void store_best_known_solution(std::string filepath);
        void store_run_time(std::string filepath);
    public:
        Instance();
        Instance(std::string filepath);
        std::string get_name() const;
        std::vector<std::vector<int>> get_matrix() const;
        std::vector<int> get_permutation() const;
        int get_size() const;
        int get_seed() const;
        Solution get_solution();
        int get_best_known_solution() const;
        double get_max_run_time() const;
        double get_relative_percentage_deviation();
        double get_computation_time() const;
        void update_permutation(std::vector<int> permutation);
        void update_solution(int solution);
        void update_computation_time(double computation_time);
        void permute_instance();
        bool local_optimum_criterion_is_not_satisfied(Solution& last_solution,Solution& solution);
        void set_solution(Solution& solution);
        void display();
};

#endif