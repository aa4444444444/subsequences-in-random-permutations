#pragma once
#ifndef SCHENSTED_H
#define SCHENSTED_H

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

struct TableauxRow {
    std::vector<size_t> rowValues;
    size_t maxElement;

    TableauxRow() { }
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
    std::vector<TableauxRow*> m_youngTableaux;

    /** Adds a value to the increasing young tableaux */
    void addToTableaux(size_t value, size_t rowIndex);
};

#endif