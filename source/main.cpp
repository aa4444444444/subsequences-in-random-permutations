#include "../header/schensted.h"
#include <cstddef>
#include <iostream>

int main()
{
    std::vector<size_t> sequence { 2, 4, 7, 3, 6, 9, 8, 1, 5 };

    Schensted schensted;
    std::pair<size_t, size_t> longestSubsequences = schensted.longestSubsequences(sequence);
    std::cout << "Longest Increasing Subsequence Length: " << longestSubsequences.first
              << "\nLongest Decreasing Subsequence Length: " << longestSubsequences.second << std::endl;
}