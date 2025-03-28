#include "../header/permutation.h"

#include <algorithm>
#include <random>

std::vector<size_t> getPermutation(size_t n)
{
    // Create a vector containing integers from 1 to n
    std::vector<size_t> permutation(n);
    for (size_t i = 0; i < n; i++) {
        permutation[i] = i + 1;
    }

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 mt(rd()); // Mersenne Twister

    // Shuffle the vector randomly
    std::shuffle(permutation.begin(), permutation.end(), mt);

    return permutation;
}
