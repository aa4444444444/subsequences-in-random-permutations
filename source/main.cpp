#include "../header/permutation.h"
#include "../header/schensted.h"
#include <cstddef>
#include <iostream>

int main()
{
    std::vector<size_t> sequence = getPermutation(50);
    for (size_t val : sequence) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Once we get a monotone subsequence, we need to perform THREE checks:
    // 1. Check if the length is equivalent to the length calculated by the Schensted algorithm.
    // 2. Check to make sure the subsequence is actually a subsequence (order didn't change)
    // 3. Check to see if the subsequence is actually monotone (increasing/decreasing)

    // Calculate length of longest increasing/decreasing subsequence using Schensted
    Schensted schensted;
    std::pair<size_t, size_t> longestSubsequences = schensted.longestSubsequences(sequence);
    std::cout << "Longest Increasing Subsequence Length: " << longestSubsequences.first
              << "\nLongest Decreasing Subsequence Length: " << longestSubsequences.second << std::endl;
}