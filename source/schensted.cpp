#include "../header/schensted.h"

Schensted::Schensted() { }

Schensted::~Schensted()
{
    for (size_t i = 0; i < m_youngTableaux.size(); i++) {
        if (m_youngTableaux[i] != nullptr) {
            delete m_youngTableaux[i];
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
        addToTableaux(sequence[i], 0);
    }

    return std::pair<size_t, size_t> { m_youngTableaux[0]->rowValues.size(), m_youngTableaux.size() };
}

/**
 * @brief Adds a value to the young tableaux
 *
 * @param value Value to add to the tableaux
 * @param rowIndex Index of row in the tableaux to add the value to
 */
void Schensted::addToTableaux(size_t value, size_t rowIndex)
{
    if (m_youngTableaux.size() == rowIndex) {
        // No row in the young tableaux for the row index
        TableauxRow* tableauxRow = new TableauxRow();
        m_youngTableaux.push_back(tableauxRow);
    }

    TableauxRow* currentRow = m_youngTableaux[rowIndex];

    auto it = std::lower_bound(currentRow->rowValues.begin(), currentRow->rowValues.end(), value);

    if (it == currentRow->rowValues.end()) {
        // If `value` is larger than all existing values, append
        currentRow->rowValues.push_back(value);
        currentRow->maxElement = value;
    } else {
        // Replace the found element and recurse
        size_t replacedValue = *it;
        *it = value;

        addToTableaux(replacedValue, rowIndex + 1);
    }
}