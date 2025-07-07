#include "sparse_matrix.hpp"
#include <cassert>
#include "sparse_vector.hpp"

const SparseVector SparseMatrix::s_emptySparseVector;

SparseMatrix::SparseMatrix(double defaultValue, size_t numRows, size_t numColumns)
{
    m_defaultValue = defaultValue;
    m_numRows = numRows;
    m_numColumns = numColumns;
}

size_t SparseMatrix::getNumRows() const
{
    return m_numRows;
}

size_t SparseMatrix::getNumColumns() const
{
    return m_numColumns;
}

const SparseVector& SparseMatrix::operator[](size_t i) const
{
    assert(i < m_numRows);
    return (m_data.count(i) > 0) ? m_data.at(i) : s_emptySparseVector;
}

SparseVector& SparseMatrix::operator[](size_t i)
{
    m_numRows = (i < m_numRows) ? m_numRows : (i + 1);
    return m_data[i];
}