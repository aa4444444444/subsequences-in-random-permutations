#include "../header/schensted.h"

Schensted::Schensted() { }

Schensted::~Schensted()
{
    for (size_t i = 0; i < m_youngTableau.size(); i++) {
        if (m_youngTableau[i] != nullptr) {
            delete m_youngTableau[i];
        }
    }
}

/**
 * @brief Runs the Schensted algorithm on a vector of ints (sequence)
 *
 * @param sequence vector of ints
 * @return std::pair<size_t, size_t> pair of size_t -- first is the length of the longest
 * increasing subsequence and second is the length of longest decreasing subsequence
 */
std::pair<size_t, size_t> Schensted::longestSubsequences(std::vector<size_t>& sequence)
{
    for (size_t i = 0; i < sequence.size(); i++) {
        addToTableau(sequence[i], 0);
    }

    return std::pair<size_t, size_t> { m_youngTableau[0]->rowValues.size(), m_youngTableau.size() };
}

/**
 * @brief Adds a value to the young tableaux
 *
 * @param value Value to add to the tableaux
 * @param rowIndex Index of row in the tableaux to add the value to
 */
void Schensted::addToTableau(size_t value, size_t rowIndex)
{
    if (m_youngTableau.size() == rowIndex) {
        // No row in the young tableaux for the row index
        TableauRow* tableauRow = new TableauRow();
        m_youngTableau.push_back(tableauRow);
    }

    TableauRow* currentRow = m_youngTableau[rowIndex];

    auto it = std::lower_bound(currentRow->rowValues.begin(), currentRow->rowValues.end(), value);

    if (it == currentRow->rowValues.end()) {
        // If value is larger than all existing values, append
        currentRow->rowValues.push_back(value);
        currentRow->maxElement = value;
    } else {
        // Replace the found element and recurse
        size_t replacedValue = *it;
        *it = value;

        addToTableau(replacedValue, rowIndex + 1);
    }
}