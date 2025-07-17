#include "sparse_matrix.hpp"
#include <cassert>
#include "sparse_vector.hpp"
#include "matrix.hpp"
#include "vectr.hpp"
#include "templates_linalg.hpp"

SparseMatrix::SparseMatrix(double defaultValue, size_t numRows, size_t numColumns)
:m_defaultRowVector(SparseVector(defaultValue, numColumns))
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
    return (m_data.count(i) > 0) ? m_data.at(i) : m_defaultRowVector;
}

SparseVector& SparseMatrix::operator[](size_t i)
{
    m_numRows = (i < m_numRows) ? m_numRows : (i + 1);
    if(m_data.count(i) == 0)
    {
        m_data[i] = m_defaultRowVector;
    }
    return m_data[i];
}

SparseMatrix SparseMatrix::operator+(double c) const
{
    SparseMatrix r(m_defaultValue + c, m_numRows, m_numColumns);
    for(const auto& e: m_data)
    {
        r[e.first] = e.second + c;
    }
    return r;
}

SparseMatrix SparseMatrix::operator-(double c) const
{
    double negativeC = -c;
    return (*this) + negativeC;
}

Matrix SparseMatrix::operator+(const Matrix& m) const
{
    assert(m_numRows == m.getNumRows());
    assert(m_numColumns == m.getNumColumns());
    return getMatrixSum((*this), m.getData(), m_numRows, m_numColumns);
}

Matrix SparseMatrix::operator-(const Matrix& m) const
{
    assert(m_numRows == m.getNumRows());
    assert(m_numColumns == m.getNumColumns());
    return getMatrixDiff((*this), m.getData(), m_numRows, m_numColumns);
}

// Some thought may be put into optimizing the addition and subtraction between
// SparseMatrix objects, as common indices of the two matrices, where non-default
// values exist, are being accessed twice.
SparseMatrix SparseMatrix::operator+(const SparseMatrix& sm) const
{
    assert(m_numRows == sm.m_numRows);
    assert(m_numColumns == sm.m_numColumns);
    SparseMatrix r(m_defaultValue + sm.m_defaultValue, m_numRows, m_numColumns);
    for(const auto& e: m_data)
    {
        size_t i = e.first;
        for(const auto& e2: e.second.getData())
        {
            size_t j = e2.first;
            r[i][j] = e2.second + sm[i][j];
        }
    }
    for(const auto& e: sm.m_data)
    {
        size_t i = e.first;
        for(const auto& e2: e.second.getData())
        {
            size_t j = e2.first;
            r[i][j] = (*this)[i][j] + sm[i][j];
        }
    }
    return r;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix& sm) const
{
    assert(m_numRows == sm.m_numRows);
    assert(m_numColumns == sm.m_numColumns);
    SparseMatrix r(m_defaultValue + sm.m_defaultValue, m_numRows, m_numColumns);
    for(const auto& e: m_data)
    {
        size_t i = e.first;
        for(const auto& e2: e.second.getData())
        {
            size_t j = e2.first;
            r[i][j] = e2.second - sm[i][j];
        }
    }
    for(const auto& e: sm.m_data)
    {
        size_t i = e.first;
        for(const auto& e2: e.second.getData())
        {
            size_t j = e2.first;
            r[i][j] = (*this)[i][j] - sm[i][j];
        }
    }
    return r;
}

SparseMatrix SparseMatrix::operator*(double c) const
{
    SparseMatrix r(m_defaultValue * c, m_numRows, m_numColumns);
    for(const auto& e: m_data)
    {
        r[e.first] = e.second * c;
    }
    return r;
}

Matrix SparseMatrix::operator*(const std::vector<std::vector<double> >& d) const
{
    assert(m_numColumns == d.size());
    return getMatrixMatrixProduct((*this), d, m_numRows, m_numColumns, d[0].size());
}

Matrix SparseMatrix::operator*(const Matrix& m) const
{
    assert(m_numColumns == m.getNumRows());
    return getMatrixMatrixProduct((*this), m.getData(), m_numRows, m_numColumns, m.getNumColumns());
}

Matrix SparseMatrix::operator*(const SparseMatrix& sm) const
{
    assert(m_numColumns == sm.m_numRows);
    return getMatrixMatrixProduct((*this), sm, m_numRows, m_numColumns, sm.getNumColumns());
}

Vector SparseMatrix::operator*(const std::vector<double>& d) const
{
    assert(m_numColumns == d.size());
    return getMatrixVectorProduct((*this), d, m_numRows, m_numColumns);
}

Vector SparseMatrix::operator*(const Vector& v) const
{
    assert(m_numColumns == v.getData().size());
    // REPLACE ABOVE WITH: v.size()
    return getMatrixVectorProduct((*this), v.getData(), m_numRows, m_numColumns);
}

Vector SparseMatrix::operator*(const SparseVector& sv) const
{
    assert(m_numColumns == sv.size());
    return getMatrixVectorProduct((*this), sv, m_numRows, m_numColumns);
}

Matrix SparseMatrix::getFullMatrix() const
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            r[i].push_back((*this)[i][j]);
        }
    }
    return r;
}