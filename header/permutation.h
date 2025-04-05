#pragma once
#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <cstddef>
#include <vector>

/** Returns a random permutation of ints from 1 to n (inclusive) */
std::vector<size_t> getPermutation(size_t n);

#endif