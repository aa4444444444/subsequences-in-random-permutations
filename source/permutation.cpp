#include "../header/permutation.h"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

std::vector<size_t> getPermutation(size_t n)
{
    // Create a vector containing integers from 1 to n
    std::vector<size_t> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 1);

    // Seed the random number generator
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937_64 mt(seed);

    // Shuffle the vector randomly
    std::shuffle(permutation.begin(), permutation.end(), mt);

    return permutation;
}
