#pragma once
#ifndef SCHENSTED_H
#define SCHENSTED_H

#include <cstddef>
#include <utility>
#include <vector>

class Schensted {
public:
    Schensted();
    std::pair<size_t, size_t> longestSubsequences(std::vector<int>& sequence);

private:
};

#endif