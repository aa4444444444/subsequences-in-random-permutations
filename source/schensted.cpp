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

void Schensted::addToTableaux(size_t value, size_t rowIndex)
{
    if (m_youngTableaux.size() == rowIndex) {
        // No row in the young tableaux for the row index
        TableauxRow* tableauxRow = new TableauxRow();
        m_youngTableaux.push_back(tableauxRow);
    }

    TableauxRow* currentRow = m_youngTableaux[rowIndex];

    if (currentRow->rowValues.size() == 0) {
        // Row exists, but is empty -- we can simply add
        currentRow->rowValues.push_back(value);
        currentRow->maxElement = value;
    } else {
        // Guaranteed to not be equal since it's permutation of numbers from 1 to n
        if (value > currentRow->maxElement) {
            // If larger than all other values we can simply add
            currentRow->rowValues.push_back(value);
            currentRow->maxElement = value;
        } else {
            if (currentRow->rowValues.size() == 1) {
                size_t replacedValue = currentRow->rowValues[0];
                currentRow->rowValues[0] = value;
                addToTableaux(replacedValue, rowIndex + 1);
            } else {
                for (size_t i = 0; i < currentRow->rowValues.size(); i++) {
                    if (i == (currentRow->rowValues.size() - 1)) {
                        size_t replacedValue = currentRow->rowValues[i];
                        currentRow->rowValues[i] = value;
                        addToTableaux(replacedValue, rowIndex + 1);
                    }
                    if (value < currentRow->rowValues[i]) {
                        size_t replacedValue = currentRow->rowValues[i];
                        currentRow->rowValues[i] = value;
                        addToTableaux(replacedValue, rowIndex + 1);
                        break;
                    }
                }
            }
        }
    }
}