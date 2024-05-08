#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "instance.hpp"
#include "config.hpp"
#include "solution.hpp"

Instance::Instance() 
{
}

Instance::Instance(std::string filepath) 
{
    verify_file(filepath);
    store_matrix(filepath);
    store_best_known_solution(BEST_KNOWN_FILE_PATH);
    store_run_time(MAX_RUN_TIME_FILE_PATH);
    if (VERBOSE) {
        display();
    }
}

void 
Instance::verify_file(std::string filepath)
{
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Error: file " << filepath << " does not exist" << std::endl;
        exit(1);
    }

    auto path = std::filesystem::path(filepath);
    this->instance_name_ = path.filename().string();
}

void 
Instance::store_matrix(std::string filepath)
{
    std::ifstream filestream(filepath.c_str());
    if (!filestream.is_open()) {
        std::cerr << "Error: could not open file " << filepath << std::endl;
        exit(1);
    }

    std::stringstream ss;
    ss << filestream.rdbuf();
    ss >> this->instance_size_;

    this->instance_permutation_ = std::vector<int>(instance_size_);
    
    this->instance_matrix_ = std::vector<std::vector<int>>(instance_size_, std::vector<int>(instance_size_));
    for (unsigned i = 0 ; i < instance_size_ ; i++) {
        for (unsigned j = 0 ; j < instance_size_; j++) {
            ss >> instance_matrix_[i][j];
            instance_seed_ += instance_matrix_[i][j];
        }
    }
}

void Instance::store_run_time(std::string filepath)
{
    std::ifstream filestream(filepath);
    if (!filestream.is_open()) {
        std::cerr << "Error: could not open file " << filepath << std::endl;
        exit(1);
    }
    
    std::string line;
    while (std::getline(filestream, line)) {
        std::stringstream ss(line);
        std::string name;
        double runtime;
        ss >> name >> runtime;
        if (name == this->instance_name_) {
            this->max_run_time_ = runtime;
            break;
        }
    }
}

void 
Instance::store_best_known_solution(std::string filepath)
{
    std::ifstream filestream(filepath);
    if (!filestream.is_open()) {
        std::cerr << "Error: could not open file " << filepath << std::endl;
        exit(1);
    }
    
    std::string line;
    while (std::getline(filestream, line)) {
        std::stringstream ss(line);
        std::string name;
        int best_known_solution;
        ss >> name >> best_known_solution;
        if (name == this->instance_name_) {
            this->best_known_instance_solution_ = best_known_solution;
            break;
        }
    }
}


std::string
Instance::get_name() const
{
    return this->instance_name_;
}

int
Instance::get_size() const
{
    return this->instance_size_;
}
double 
Instance::get_max_run_time() const
{
    return this->max_run_time_;
}

std::vector<std::vector<int>>
Instance::get_matrix() const
{
    return this->instance_matrix_;
}

std::vector<int>
Instance::get_permutation() const
{
    return this->instance_permutation_;
}

Solution
Instance::get_solution()
{
    return this->instance_solution_;
}

int
Instance::get_seed() const
{
    return this->instance_seed_;
}

double
Instance::get_computation_time() const
{
    return this->instance_computation_time_;
}

int
Instance::get_best_known_solution() const
{
    return this->best_known_instance_solution_;
}

double
Instance::get_relative_percentage_deviation()
{
    this->relative_deviation_percentage_ = 100 * (best_known_instance_solution_ - instance_solution_.score()) / best_known_instance_solution_;
    return this->relative_deviation_percentage_;
}

void
Instance::update_permutation(std::vector<int> permutation)
{
    this->instance_permutation_ = permutation;
}


void
Instance::update_computation_time(double computation_time)
{
    this->instance_computation_time_ = computation_time;
}

void
Instance::permute_instance()
{
    for (int i = 0; i < get_size(); i++) {
        std::swap(instance_matrix_[i], instance_matrix_[instance_permutation_[i]]);
    }
}

void
Instance::display()
{
    std::cerr << "- Instance - " << std::endl
              << "Name: " << this->instance_name_ << std::endl
              << "Size: " << this->instance_size_ << std::endl
              << "Seed: " << this->instance_seed_ << std::endl
              << std::endl;
    std::cerr.flush();
}
bool 
Instance::local_optimum_criterion_is_not_satisfied(Solution& last_solution,Solution& solution)
{
    return last_solution != solution;
}

void
Instance::set_solution(Solution& solution)
{
    this->instance_solution_ = solution;
}