#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

class Solution
{
    private:
        int size_;
        std::vector<int> permutation_;
        int score_;
        std::pair<unsigned, unsigned> last_neighbour_;
        
    public:
        Solution();
        Solution(int size);
        Solution(int size, const std::vector<int>& permutation);
        int size() const;
        const std::vector<int>& permutation() const;
        int score() const;
        std::pair<unsigned, unsigned> last_neighbour() const;
        void swap_permutation(int i, int j);
        void transpose_permutation(int i, int j);
        void exchange_permutation(int i, int j);
        void insert_permutation(int i, int j);
        void set_permutation(const std::vector<int>& permutation);
        void set_score(int score);
        void set_last_neighbour(std::pair<unsigned, unsigned> last_neighbour);
        bool operator==(const Solution& other) const;
        bool operator!=(const Solution& other) const;
        const std::vector<int>& get_permutation() const;
        void print() const;
        
};

#endif