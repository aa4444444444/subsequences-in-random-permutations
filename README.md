# subsequences-in-random-permutations
Estimate the expected length of the longest increasing subsequence, as a function of n, and also the length of the longest monotone (i.e. increasing or decreasing) subsequence.

Please follow these steps to run the program:
1) Clone the repository
2) Get the necessary third-party libraries and place them in a tplibs/ directory (this directory should be at the same level as the source, output, and header directories)
    - https://github.com/InductiveComputerScience/pbPlots/tree/master/Cpp (The four files you need are pbPlots.cpp, pbPlots.hpp, supportLib.cpp, and supportLib.hpp)
    - If you decide to name the directory something other than tplibs, you will have to make changes to main.cpp and the Makefile
3) Make an changes you deem necessary to main.cpp e.g. increasing number of trials 
4) Run make -- this will generate an executable
    - You will likely get some warnings for the pbPlots files since the Makefile uses the -Wall flag. This is fine, you can ignore it.
5) Run the executable
6) Plots will be generated in the 'output' directory
