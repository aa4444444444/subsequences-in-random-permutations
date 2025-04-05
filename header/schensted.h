#pragma once
#ifndef SCHENSTED_H
#define SCHENSTED_H

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Represents a row in the young tableaux
 *
 */
struct TableauRow {
    std::vector<size_t> rowValues;
    size_t maxElement;

    TableauRow() { }
    void print()
    {
        for (size_t i = 0; i < rowValues.size(); i++) {
            std::cout << rowValues[i] << " ";
        }
        std::cout << std::endl;
    }
};

/**
 * @brief Class implements the Schensted algorithm (Schensted 1961)
 *
 * Constructs a Young tableau by successively inserting the values of the permutation according to a
 * specific rule, while the other tableau records the evolution of the shape during construction.
 *
 * The Schensted algorithm can tell us the length of the longest increasing/decreasing subsequences,
 * BUT IT CANNOT tell us what those subsequences are. Only the length.
 *
 */
class Schensted {
public:
    /** Constructor */
    Schensted();

    /** Destructor */
    ~Schensted();

    /** Runs the Schensted algorithm on a vector of ints  */
    std::pair<size_t, size_t> longestSubsequences(std::vector<size_t>& sequence);

private:
    /** The resulting Young Tableau */
    std::vector<TableauRow*> m_youngTableau;

    /** Adds a value to the increasing young tableau */
    void addToTableau(size_t value, size_t rowIndex);
};

#endif