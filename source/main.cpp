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

    // Calculating variances
    std::vector<double> longestIncreasingSubsequenceVariance;
    std::vector<double> longestDecreasingSubsequenceVariance;
    std::vector<double> longestMonotonicSubsequenceVariance;

    // Keeping track of individual longest subsequences to calculate variance
    std::vector<size_t> longestIncreasingSubsequenceList;
    std::vector<size_t> longestDecreasingSubsequenceList;
    std::vector<size_t> longestMonotonicSubsequenceList;

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

            // Add to list
            longestIncreasingSubsequenceList.push_back(longestSubsequences.first);
            longestDecreasingSubsequenceList.push_back(longestSubsequences.second);
            longestMonotonicSubsequenceList.push_back(std::max(longestSubsequences.first, longestSubsequences.second));
        }

        nValues.push_back(twoToTheI);

        // Averaged trials
        double increasingAverage = sumOfIncreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0);
        double decreasingAverage = sumOfDecreasingSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0);
        double monotonicAverage = sumOfMonotonicSubsequenceLengths / (NUM_REPEATED_TRIALS * 1.0);
        averageLongestIncreasingSubsequence.push_back(increasingAverage);
        averageLongestDecreasingSubsequence.push_back(decreasingAverage);
        averageLongestMonotonicSubsequence.push_back(monotonicAverage);

        // Variance
        double increasingVariance;
        double decreasingVariance;
        double monotonicVariance;
        // Since all lists have the same size, we can just use the size of one
        for (size_t i = 0; i < longestIncreasingSubsequenceList.size(); i++) {
            double differenceFromMeanSquaredIncreasing = (longestIncreasingSubsequenceList[i] - increasingAverage)
                * (longestIncreasingSubsequenceList[i] - increasingAverage);

            double differenceFromMeanSquaredDecreasing = (longestDecreasingSubsequenceList[i] - decreasingAverage)
                * (longestDecreasingSubsequenceList[i] - decreasingAverage);

            double differenceFromMeanSquaredMonotonic = (longestMonotonicSubsequenceList[i] - monotonicAverage)
                * (longestMonotonicSubsequenceList[i] - monotonicAverage);

            increasingVariance += differenceFromMeanSquaredIncreasing;
            decreasingVariance += differenceFromMeanSquaredDecreasing;
            monotonicVariance += differenceFromMeanSquaredMonotonic;
        }

        // Divide by n-1 since this is the sample variance not population variance
        increasingVariance /= (NUM_REPEATED_TRIALS - 1);
        decreasingVariance /= (NUM_REPEATED_TRIALS - 1);
        monotonicVariance /= (NUM_REPEATED_TRIALS - 1);

        longestIncreasingSubsequenceVariance.push_back(increasingVariance);
        longestDecreasingSubsequenceVariance.push_back(decreasingVariance);
        longestMonotonicSubsequenceVariance.push_back(monotonicVariance);

        // Clear subsequence lists for next loop
        longestIncreasingSubsequenceList.clear();
        longestDecreasingSubsequenceList.clear();
        longestMonotonicSubsequenceList.clear();
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
    std::cout << "=============================================" << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "n = " << nValues[i] << ", mean = " << averageLongestIncreasingSubsequence[i]
                  << ", variance = " << longestIncreasingSubsequenceVariance[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Longest Decreasing Subsequence Values: " << std::endl;
    std::cout << "=============================================" << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "n = " << nValues[i] << ", mean = " << averageLongestDecreasingSubsequence[i]
                  << ", variance = " << longestDecreasingSubsequenceVariance[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Longest Monotonic Subsequence Values: " << std::endl;
    std::cout << "=============================================" << std::endl;
    for (size_t i = 0; i < nValues.size(); i++) {
        std::cout << "n = " << nValues[i] << ", mean = " << averageLongestMonotonicSubsequence[i]
                  << ", variance = " << longestMonotonicSubsequenceVariance[i] << std::endl;
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