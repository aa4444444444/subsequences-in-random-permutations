#include "../header/permutation.h"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

/**
 * @brief Gets a random permutation of the numbers from 1 to n (inclusive)
 * This function uses a seed based on the current time for the Mersenne Twister
 * pseudo-random generator of 64-bit numbers. It then shuffles a vector of numbers
 * from 1 to n based on this Mersenne Twister
 * @param n Number of values in the sequence to be permuted
 * @return std::vector<size_t> Vector containing a permutation of numbers from 1 to n
 */
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
