#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <map>

class SparseVector;

class SparseMatrix
{
    std::map<size_t, SparseVector> m_data;
    double m_defaultValue;
    size_t m_numRows;
    size_t m_numColumns;
    const static SparseVector s_emptySparseVector;
public:
    SparseMatrix(double defaultValue=0, size_t numRows=0, size_t numColumns=0);
    size_t getNumRows() const;
    size_t getNumColumns() const;
    const SparseVector& operator[](size_t i) const;
    SparseVector& operator[](size_t i);
};

#endif