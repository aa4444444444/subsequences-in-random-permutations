#include "../header/schensted.h"
#include <cstddef>
#include <iostream>

int main()
{
    std::vector<int> sequence { 0 };

    Schensted schensted;
    std::pair<size_t, size_t> longestSubsequences = schensted.longestSubsequences(sequence);
    std::cout << longestSubsequences.first << " " << longestSubsequences.second << std::endl;
}