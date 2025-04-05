#include "../header/permutation.h"
#include "../header/schensted.h"
#include "../tplibs/pbPlots.hpp"
#include "../tplibs/supportLib.hpp"
#include <cstddef>
#include <iostream>

#define NUM_REPEATED_TRIALS 100 // Number of trials to use to calculate average
#define NUM_POWERS_OF_TWO 12 // Number of powers of two [1, NUM_POWERS_OF_TWO]

int main()
{
    // Initialize plotted image refs
    RGBABitmapImageReference* longestIncreasingImageRef = CreateRGBABitmapImageReference();
    RGBABitmapImageReference* longestDecreasingImageRef = CreateRGBABitmapImageReference();
    RGBABitmapImageReference* longestMonotonicImageRef = CreateRGBABitmapImageReference();

    // These vectors need to be of type double for the plotting to work
    std::vector<double> nValues; // x-axis
    std::vector<double> averageLongestIncreasingSubsequence; // y-axis
    std::vector<double> averageLongestDecreasingSubsequence; // y-axis
    std::vector<double> averageLongestMonotonicSubsequence; // y-axis

    // We are choosing different powers of 2, i.e. n = 2, 4, 8, 16,...
    for (size_t i = 1; i <= NUM_POWERS_OF_TWO; i++) {

        size_t sumOfIncreasingSubsequenceLengths = 0;
        size_t sumOfDecreasingSubsequenceLengths = 0;
        size_t sumOfMonotonicSubsequenceLengths = 0;

        double twoToTheI = pow(2, i);

        // Repeated trials
        for (size_t rt = 0; rt < NUM_REPEATED_TRIALS; rt++) {
            // Calculate length of longest increasing/decreasing subsequence using Schensted
            Schensted schensted;

            std::vector<size_t> permutedSequence = getPermutation(twoToTheI); // Random Permutation
            std::pair<size_t, size_t> longestSubsequences = schensted.longestSubsequences(permutedSequence);

            // Add to total sum
            sumOfIncreasingSubsequenceLengths += longestSubsequences.first;
            sumOfDecreasingSubsequenceLengths += longestSubsequences.second;
            sumOfMonotonicSubsequenceLengths += std::max(longestSubsequences.first, longestSubsequences.second);
        }

        nValues.push_back(twoToTheI);

        // Averaged trials
        averageLongestIncreasingSubsequence.push_back(sumOfIncreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0));
        averageLongestDecreasingSubsequence.push_back(sumOfDecreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0));
        averageLongestMonotonicSubsequence.push_back(sumOfMonotonicSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0));
    }

    // Drawing scatter plot
    StringReference* errorMessage1 = CreateStringReference(toVector(L""));
    DrawScatterPlot(longestIncreasingImageRef, 600, 400, &nValues, &averageLongestIncreasingSubsequence, errorMessage1);
    StringReference* errorMessage2 = CreateStringReference(toVector(L""));
    DrawScatterPlot(longestDecreasingImageRef, 600, 400, &nValues, &averageLongestDecreasingSubsequence, errorMessage2);
    StringReference* errorMessage3 = CreateStringReference(toVector(L""));
    DrawScatterPlot(longestMonotonicImageRef, 600, 400, &nValues, &averageLongestMonotonicSubsequence, errorMessage3);

    // Print out the values for more detail
    std::cout << "Longest Increasing Subsequence Values: " << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "(" << nValues[i] << ", " << averageLongestIncreasingSubsequence[i] << ")";
    }
    std::cout << std::endl;

    std::cout << "Longest Decreasing Subsequence Values: " << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "(" << nValues[i] << ", " << averageLongestDecreasingSubsequence[i] << ")";
    }
    std::cout << std::endl;

    std::cout << "Longest Monotonic Subsequence Values: " << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "(" << nValues[i] << ", " << averageLongestMonotonicSubsequence[i] << ")";
    }
    std::cout << std::endl;

    // Outputting scatterplots
    std::vector<double>* increasingPngData = ConvertToPNG(longestIncreasingImageRef->image);
    WriteToFile(increasingPngData, "output/increasingPlot.png");
    DeleteImage(longestIncreasingImageRef->image);

    std::vector<double>* decreasingPngData = ConvertToPNG(longestDecreasingImageRef->image);
    WriteToFile(decreasingPngData, "output/decreasingPlot.png");
    DeleteImage(longestDecreasingImageRef->image);

    std::vector<double>* monotonicPngData = ConvertToPNG(longestMonotonicImageRef->image);
    WriteToFile(monotonicPngData, "output/monotonicPlot.png");
    DeleteImage(longestMonotonicImageRef->image);

    std::cout << "Finished Generating Image" << std::endl;

    return 0;
}