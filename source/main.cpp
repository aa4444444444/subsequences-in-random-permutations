#include "../header/permutation.h"
#include "../header/schensted.h"
#include "../tplibs/pbPlots.hpp"
#include "../tplibs/supportLib.hpp"
#include <cstddef>
#include <iostream>

#define NUM_REPEATED_TRIALS 1000
#define NUM_POWERS_OF_TWO 15

int main()
{
    // Initialize plotted image ref
    RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();

    std::vector<double> nValues;
    std::vector<double> averageLongestIncreasingSubsequence;
    std::vector<double> averageLongestDecreasingSubsequence;

    // 1 to n
    for (size_t i = 1; i <= NUM_POWERS_OF_TWO; i++) {

        size_t sumOfIncreasingSubsequenceLengths = 0;
        size_t sumOfDecreasingSubsequenceLengths = 0;

        double twoToTheI = pow(2, i);

        // Repeated trials
        for (size_t rt = 0; rt < NUM_REPEATED_TRIALS; rt++) {
            // Calculate length of longest increasing/decreasing subsequence using Schensted
            Schensted schensted;

            std::vector<size_t> permutedSequence = getPermutation(twoToTheI);
            std::pair<size_t, size_t> longestSubsequences = schensted.longestSubsequences(permutedSequence);

            sumOfIncreasingSubsequenceLengths += longestSubsequences.first;
            sumOfDecreasingSubsequenceLengths += longestSubsequences.second;
        }

        nValues.push_back(twoToTheI);
        averageLongestIncreasingSubsequence.push_back(sumOfIncreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0));
        averageLongestDecreasingSubsequence.push_back(sumOfDecreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0));
    }

    StringReference* errorMessage = CreateStringReference(toVector(L""));
    DrawScatterPlot(imageRef, 600, 400, &nValues, &averageLongestIncreasingSubsequence, errorMessage);

    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "(" << nValues[i] << ", " << averageLongestIncreasingSubsequence[i] << ")";
    }
    std::cout << std::endl;

    std::vector<double>* pngData = ConvertToPNG(imageRef->image);

    WriteToFile(pngData, "output/plot.png");

    DeleteImage(imageRef->image);

    std::cout << "Finished Generating Image" << std::endl;

    return 0;

    // Once we get a monotone subsequence, we need to perform THREE checks:
    // 1. Check if the length is equivalent to the length calculated by the Schensted algorithm.
    // 2. Check to make sure the subsequence is actually a subsequence (order didn't change)
    // 3. Check to see if the subsequence is actually monotone (increasing/decreasing)
}