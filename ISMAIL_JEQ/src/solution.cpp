#include "solution.hpp"
#include <iostream>

Solution::Solution() {}

Solution::Solution(int size)
{
    this->size_ = size;
    this->permutation_ = std::vector<int>(size);
    this->score_ = 0;
    this->last_neighbour_ = {0, 0};
}

Solution::Solution(int size, const std::vector<int>& permutation)
{
    this->size_ = size;
    this->permutation_ = permutation;
    this->score_ = 0;
    this->last_neighbour_ = {0, 0};
}
int
Solution::size() const
{
    return this->size_;
}

const std::vector<int>&
Solution::permutation() const
{
    return this->permutation_;
}

int
Solution::score() const
{
    return this->score_;
}
std::pair<unsigned, unsigned>
Solution::last_neighbour() const
{
    return this->last_neighbour_;
}

void
Solution::swap_permutation(int i, int j)
{
    std::swap(this->permutation_[i], this->permutation_[j]);
}

void
Solution::transpose_permutation(int i, int j)
{
    swap_permutation(i, j);
}

void
Solution::exchange_permutation(int i, int j)
{
    swap_permutation(i, j);
}
void
Solution::insert_permutation(int i, int j)
{
    int value = this->permutation_[i];
    this->permutation_.erase(this->permutation_.begin() + i);
    this->permutation_.insert(this->permutation_.begin() + j, value);
}

void
Solution::set_permutation(const std::vector<int>& permutation)
{
    this->permutation_ = permutation;
}

void
Solution::set_score(int score)
{
    this->score_ = score;
}
void
Solution::set_last_neighbour(std::pair<unsigned, unsigned> last_neighbour)
{
    this->last_neighbour_ = last_neighbour;
}

bool
Solution::operator==(const Solution& other) const
{
    return this->score_ == other.score();
}

bool
Solution::operator!=(const Solution& other) const
{
    return this->score_ != other.score();
}
void
Solution::print() const
{
    std::cout << "Permutation: " << std::endl;
    for (int i = 0; i < this->size(); i++) {
        std::cout << this->permutation_[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Score: " << this->score() << std::endl;
}

const std::vector<int>&
Solution::get_permutation() const
{
    return this->permutation_;
}